/*
 * Copyright (c) 1983,1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

char copyright[] =
  "@(#) Copyright (c) 1983 Regents of the University of California.\n"
  "All rights reserved.\n";

/*
 * From: @(#)inetd.c	5.30 (Berkeley) 6/3/91
 */
char rcsid[] = 
  "$Id: inetd.c,v 1.4 2007/09/24 11:26:45 rborin Exp $";
char pkg[] = "netkit-base-0.10";

/*
 * Inetd - Internet super-server
 *
 * This program invokes all internet services as needed.
 * connection-oriented services are invoked each time a
 * connection is made, by creating a process.  This process
 * is passed the connection as file descriptor 0 and is
 * expected to do a getpeername to find out the source host
 * and port.
 *
 * Datagram oriented services are invoked when a datagram
 * arrives; a process is created and passed a pending message
 * on file descriptor 0.  Datagram servers may either connect
 * to their peer, freeing up the original socket for inetd
 * to receive further messages on, or ``take over the socket'',
 * processing all arriving datagrams and, eventually, timing
 * out.	 The first type of server is said to be ``multi-threaded'';
 * the second type of server ``single-threaded''. 
 *
 * Inetd uses a configuration file which is read at startup
 * and, possibly, at some later time in response to a hangup signal.
 * The configuration file is ``free format'' with fields given in the
 * order shown below.  Continuation lines for an entry must being with
 * a space or tab.  All fields must be present in each entry.
 *
 *	service name			must be in /etc/services
 *	socket type			stream/dgram/raw/rdm/seqpacket
 *	protocol			must be in /etc/protocols
 *	wait/nowait[.max]		single-threaded/multi-threaded, max #
 *	user[.group]			user/group to run daemon as
 *	server program			full path name
 *	server program arguments	maximum of MAXARGS (20)
 *
 * For RPC services
 *      service name/version            must be in /etc/rpc
 *	socket type			stream/dgram/raw/rdm/seqpacket
 *	protocol			must be in /etc/protocols
 *	wait/nowait[.max]		single-threaded/multi-threaded
 *	user[.group]			user to run daemon as
 *	server program			full path name
 *	server program arguments	maximum of MAXARGS (20)
 *
 * Comment lines are indicated by a `#' in column 1.
 */

/*
 * Here's the scoop concerning the user.group feature:
 *
 * 1) No group listed.
 * 
 * 	a) for root:	NO setuid() or setgid() is done
 * 
 * 	b) nonroot:	setuid()
 * 			setgid(primary group as found in passwd)
 * 			initgroups(name, primary group)
 * 
 * 2) set-group-option on.
 * 
 * 	a) for root:	NO setuid()
 * 			setgid(specified group)
 * 			setgroups(1, specified group)
 * 
 * 	b) nonroot:	setuid()
 * 			setgid(specified group)
 * 			initgroups(name, specified group)
 * 
 * All supplementary groups are discarded at startup in case inetd was
 * run manually.
 */

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/resource.h>

#ifndef __linux__
#ifndef RLIMIT_NOFILE
#define RLIMIT_NOFILE	RLIMIT_OFILE
#endif
#endif

#define RPC

#include <sys/param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <syslog.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>

#ifdef RPC
/* work around a compiler warning in rpc.h */
#define __wait __wait_foo
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#undef __wait
#endif

#include "pathnames.h"
#include "inetd.h"

extern char *get_telnet_port(int, int);
extern void set_telnet_init_port(void);
extern void set_telnet_end_port(void);
extern int check_telnet_ip(struct sockaddr_storage *sa);
extern int check_telnet_ip_serial(struct sockaddr_storage *sa, char **server, char **argv);

#ifndef MIN
#define MIN(a, b)	((a) < (b) ? (a) : (b))
#endif

#define	TOOMANY		40		/* don't start more than TOOMANY */
#define	CNT_INTVL	60		/* servers in CNT_INTVL sec. */
#define	RETRYTIME	(60*10)		/* retry after bind or server fail */

struct servtab *getconfigent(void);
struct servtab *enter(struct servtab *);
static void config(int);
static void reapchild(int);
static void retry(int);
static void goaway(int);

static int check_telnet(int s, struct servtab *sep);
static void start_telnet(int s, struct servtab *sep);

/* Length of socket listen queue. Should be per-service probably. */
static int 	global_queuelen = 128;

static int	debug = 0;
static int	nsock, maxsock;
static fd_set	allsock;
static int	options;
static int	timingout;
static sigset_t blockmask, emptymask;

#ifdef MULOG
static char	*curdom;
#endif

#ifndef OPEN_MAX
#define OPEN_MAX	64
#endif

/* Reserve some descriptors, 3 stdio + at least: 1 log, 1 conf. file */
#define FD_MARGIN	(8)
int	rlim_ofile_cur = OPEN_MAX;

#ifdef RLIMIT_NOFILE
struct rlimit	rlim_ofile;
#endif

struct	servtab {
	char	*se_service;		/* name of service */
	int	se_socktype;		/* type of socket to use */
	int	se_family;		/* address family */
	char	*se_proto;		/* protocol used */
	int	se_rpcprog;		/* rpc program number */
	int	se_rpcversl;		/* rpc program lowest version */
	int	se_rpcversh;		/* rpc program highest version */
#define isrpcservice(sep)	((sep)->se_rpcversl != 0)
	short	se_wait;		/* single threaded server */
	short	se_checked;		/* looked at during merge */
	char	*se_user;		/* user name to run as */
	char	*se_group;		/* group name to run as */
	struct	biltin *se_bi;		/* if built-in, description */
	char	*se_server;		/* server program */
	int (*se_check)(int, struct servtab *); /* consistency routine */
	void (*se_start)(int, struct servtab *); /* start routine */
#define	MAXARGV 20
	char	*se_argv[MAXARGV+1];	/* program arguments */
	int	se_fd;			/* open descriptor */
	union {
		struct	sockaddr_storage se_un_ctrladdr;
		struct	sockaddr_in6 se_un_ctrladdr_in6;
		struct	sockaddr_in se_un_ctrladdr_in;
		struct	sockaddr_un se_un_ctrladdr_un;
	} se_un;			/* bound address */
#define se_ctrladdr	se_un.se_un_ctrladdr
#define se_ctrladdr_in	se_un.se_un_ctrladdr_in
#define se_ctrladdr_in6	se_un.se_un_ctrladdr_in6
#define se_ctrladdr_un	se_un.se_un_ctrladdr_un
	int	se_ctrladdr_size;
	int	se_max;			/* max # of instances of this service */
	int	se_count;		/* number started since se_time */
	struct	timeval se_time;	/* start of se_count */
#ifdef MULOG
	int	se_log;
#define MULOG_RFC931	0x40000000
#endif
	struct	servtab *se_next;
} *servtab;

static void echo_stream(int, struct servtab *);
static void discard_stream(int, struct servtab *);
static void machtime_stream(int, struct servtab *);
static void daytime_stream(int, struct servtab *);
static void chargen_stream(int, struct servtab *);
static void echo_dg(int, struct servtab *);
static void discard_dg(int, struct servtab *);
static void machtime_dg(int, struct servtab *);
static void daytime_dg(int, struct servtab *);
static void chargen_dg(int, struct servtab *);

static void logpid(void);
static int setconfig(void);
static void endconfig(void);
static void register_rpc(struct servtab *sep);
static void unregister_rpc(struct servtab *sep);
static void freeconfig(struct servtab *cp);
static void print_service(const char *action, struct servtab *sep);
static void setup(struct servtab *sep);
static int bump_nofile(void);


struct biltin {
	const char *bi_service;		/* internally provided service name */
	int bi_socktype;		/* type of socket supported */
	short bi_fork;		/* 1 if should fork before call */
	short bi_wait;		/* 1 if should wait for child */
	void (*bi_fn)(int, struct servtab *); /* fn which performs it */
} biltins[] = {
	/* Echo received data */
	{ "echo",		SOCK_STREAM,	1, 0,	echo_stream, },
	{ "echo",		SOCK_DGRAM,	0, 0,	echo_dg, },

	/* Internet /dev/null */
	{ "discard",	SOCK_STREAM,	1, 0,	discard_stream, },
	{ "discard",	SOCK_DGRAM,	0, 0,	discard_dg, },

	/* Return 32 bit time since 1900 */
	{ "time",		SOCK_STREAM,	0, 0,	machtime_stream, },
	{ "time",		SOCK_DGRAM,	0, 0,	machtime_dg,     },

	/* Return human-readable time */
	{ "daytime",	SOCK_STREAM,	0, 0,	daytime_stream,     },
	{ "daytime",	SOCK_DGRAM,	0, 0,	daytime_dg,     },

	/* Familiar character generator */
	{ "chargen",	SOCK_STREAM,	1, 0,	chargen_stream,     },
	{ "chargen",	SOCK_DGRAM,	0, 0,	chargen_dg,     },

	{ NULL, 0, 0, 0, NULL }
};

#define NUMINT	(sizeof(intab) / sizeof(struct inent))
static const char *CONFIG = _PATH_INETDCONF;
static char **Argv;
static char *LastArg;
static char *progname;

#ifdef sun
/*
 * Sun's RPC library caches the result of `dtablesize()'
 * This is incompatible with our "bumping" of file descriptors "on demand"
 */
int
_rpc_dtablesize()
{
	return rlim_ofile_cur;
}
#endif

int
main(int argc, char *argv[], char *envp[])
{
	struct servtab *sep;
	struct passwd *pwd;
	struct group *grp = NULL;
	int tmpint;
	struct sigaction sa;
	int ch, pid, dofork;
	char buf[50];
	gid_t gid;

	gid = getgid();
	setgroups(1, &gid);

	Argv = argv;
	if (envp == 0 || *envp == 0)
		envp = argv;
	while (*envp)
		envp++;
	LastArg = envp[-1] + strlen(envp[-1]);

	progname = strrchr(argv[0], '/');
	progname = progname ? progname + 1 : argv[0];

	while ((ch = getopt(argc, argv, "dq:")) != EOF)
		switch(ch) {
		case 'd':
			debug = 1;
			options |= SO_DEBUG;
			break;
		case 'q':
		        global_queuelen = atoi(optarg);
			if (global_queuelen < 8) global_queuelen=8;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: %s [-d] [-q len] [conf]", 
				progname);
			exit(1);
		}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		CONFIG = argv[0];

	if (debug == 0)
		daemon(0, 0);
	openlog(progname, LOG_PID | LOG_NOWAIT, LOG_DAEMON);
	logpid();

#ifdef RLIMIT_NOFILE
	if (getrlimit(RLIMIT_NOFILE, &rlim_ofile) < 0) {
		syslog(LOG_ERR, "getrlimit: %m");
	} else {
		rlim_ofile_cur = rlim_ofile.rlim_cur;
		if (rlim_ofile_cur == RLIM_INFINITY)	/* ! */
			rlim_ofile_cur = OPEN_MAX;
	}
#endif

	config(0);

	sigemptyset(&emptymask);
	sigemptyset(&blockmask);
	sigaddset(&blockmask, SIGCHLD);
	sigaddset(&blockmask, SIGHUP);
	sigaddset(&blockmask, SIGALRM);

	memset(&sa, 0, sizeof(sa));
	sa.sa_mask = blockmask;
	sa.sa_handler = retry;
	sigaction(SIGALRM, &sa, NULL);
	sa.sa_handler = config;
	sigaction(SIGHUP, &sa, NULL);
	sa.sa_handler = reapchild;
	sigaction(SIGCHLD, &sa, NULL);
	sa.sa_handler = goaway;
	sigaction(SIGTERM, &sa, NULL);
	sa.sa_handler = goaway;
	sigaction(SIGINT, &sa,  NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);

	{
		/* space for daemons to overwrite environment for ps */
#define	DUMMYSIZE	100
		char dummy[DUMMYSIZE];

		(void)memset(dummy, 'x', DUMMYSIZE - 1);
		dummy[DUMMYSIZE - 1] = '\0';

		(void)setenv("inetd_dummy", dummy, 1);
	}

	for (;;) {
	    int n, ctrl;
	    fd_set readable;

	    if (nsock == 0) {
		sigprocmask(SIG_BLOCK, &blockmask, NULL);
		while (nsock == 0)
		    sigsuspend(&emptymask);
		sigprocmask(SIG_SETMASK, &emptymask, NULL);
	    }
	    readable = allsock;
	    if ((n = select(maxsock + 1, &readable, (fd_set *)0,
		(fd_set *)0, (struct timeval *)0)) <= 0) {
		    if (n < 0 && errno != EINTR)
			syslog(LOG_WARNING, "select: %m\n");
		    sleep(1);
		    continue;
	    }
	    for (sep = servtab; n && sep; sep = sep->se_next)
	    if (sep->se_fd != -1 && FD_ISSET(sep->se_fd, &readable)) {
		n--;
		if (debug)
			fprintf(stderr, "someone wants %s\n", sep->se_service);
		if (!sep->se_wait && sep->se_socktype == SOCK_STREAM) {
			/* Fixed AGC */
			fcntl(sep->se_fd,F_SETFL,O_NDELAY);
			/* --------- */
			ctrl = accept(sep->se_fd, NULL, NULL);
			fcntl(sep->se_fd,F_SETFL, 0);
			if (debug)
				fprintf(stderr, "accept, ctrl %d\n", ctrl);
			if (ctrl < 0) {
				if (errno == EINTR || errno == EWOULDBLOCK)
					continue;
				syslog(LOG_WARNING, "accept (for %s): %m",
					sep->se_service);
				continue;
			}
		} else
			ctrl = sep->se_fd;

		if (sep->se_check)
			if ((*sep->se_check)(ctrl, sep)) {
				goto err_check;
			}

		sigprocmask(SIG_BLOCK, &blockmask, NULL);
		pid = 0;
		dofork = (sep->se_bi == 0 || sep->se_bi->bi_fork);
		if (dofork) {
			if (sep->se_count++ == 0)
			    (void)gettimeofday(&sep->se_time,
			        (struct timezone *)0);
			else if (sep->se_count >= sep->se_max) {
				struct timeval now;

				(void)gettimeofday(&now, (struct timezone *)0);
				if (now.tv_sec - sep->se_time.tv_sec >
				    CNT_INTVL) {
					sep->se_time = now;
					sep->se_count = 1;
				} else {
					syslog(LOG_ERR,
			"%s/%s server failing (looping), service terminated\n",
					    sep->se_service, sep->se_proto);
					FD_CLR(sep->se_fd, &allsock);
					(void) close(sep->se_fd);
					sep->se_fd = -1;
					sep->se_count = 0;
					nsock--;
					sigprocmask(SIG_SETMASK, &emptymask, 
						    NULL);
					if (!timingout) {
						timingout = 1;
						alarm(RETRYTIME);
					}
					continue;
				}
			}
			pid = fork();
		}
		if (pid < 0) {
			syslog(LOG_ERR, "fork: %m");
			if (sep->se_socktype == SOCK_STREAM)
				close(ctrl);
			sigprocmask(SIG_SETMASK, &emptymask, NULL);
			sleep(1);
			continue;
		}
		if (pid && sep->se_wait) {
			sep->se_wait = pid;
			FD_CLR(sep->se_fd, &allsock);
			nsock--;
		}
		sigprocmask(SIG_SETMASK, &emptymask, NULL);
		if (pid == 0) {
			if (debug && dofork)
				setsid();
			if (sep->se_bi)
				(*sep->se_bi->bi_fn)(ctrl, sep);
			else {
				if ((pwd = getpwnam(sep->se_user)) == NULL) {
					syslog(LOG_ERR,
						"getpwnam: %s: No such user",
						sep->se_user);
					if (sep->se_socktype != SOCK_STREAM)
						recv(0, buf, sizeof (buf), 0);
					_exit(1);
				}
				if (sep->se_group &&
				    (grp = getgrnam(sep->se_group)) == NULL) {
					syslog(LOG_ERR,
						"getgrnam: %s: No such group",
						sep->se_group);
					if (sep->se_socktype != SOCK_STREAM)
						recv(0, buf, sizeof (buf), 0);
					_exit(1);
				}
				/*
				 * Ok. There are four cases here:
				 *   1. nonroot user, no group specified
				 *   2. nonroot user, some group specified
				 *   3. root user, no group specified
				 *   4. root user, some group specified
				 * In cases 2 and 4 we setgid to the specified
				 * group. In cases 1 and 2 we run initgroups
				 * to run with the groups of the given user.
				 * In case 4 we do setgroups to run with the
				 * given group. In case 3 we do nothing.
				 */
				if (pwd->pw_uid) {
					if (sep->se_group)
						pwd->pw_gid = grp->gr_gid;
					setgid((gid_t)pwd->pw_gid);
					initgroups(pwd->pw_name, pwd->pw_gid);
					setuid((uid_t)pwd->pw_uid);
				} else if (sep->se_group) {
					setgid((gid_t)grp->gr_gid);
					setgroups(1, &grp->gr_gid);
				}
				if (debug)
					fprintf(stderr, "%d execl %s\n",
					    getpid(), sep->se_server);
#ifdef MULOG
				if (sep->se_log)
					dolog(sep, ctrl);
#endif
				dup2(ctrl, 0);
				close(ctrl);
				dup2(0, 1);
				dup2(0, 2);
#ifdef RLIMIT_NOFILE
				if (rlim_ofile.rlim_cur != rlim_ofile_cur) {
					if (setrlimit(RLIMIT_NOFILE,
							&rlim_ofile) < 0)
						syslog(LOG_ERR,"setrlimit: %m");
				}
#endif
				for (tmpint = rlim_ofile_cur-1; --tmpint > 2; )
					(void)close(tmpint);

				memset(&sa, 0, sizeof(sa));
				sa.sa_handler = SIG_DFL;
				sigaction(SIGPIPE, &sa, NULL);
				
				if (sep->se_start)
					(*sep->se_start)(0, sep);
				else
					execv(sep->se_server, sep->se_argv);

				if (sep->se_socktype != SOCK_STREAM)
					recv(0, buf, sizeof (buf), 0);
				syslog(LOG_ERR, "execv %s: %m", sep->se_server);
				_exit(1);
			}
		}

err_check:

		if (!sep->se_wait && sep->se_socktype == SOCK_STREAM)
			close(ctrl);
	    }
	}
}

void
reapchild(int signum)
{
	int status;
	int pid;
	register struct servtab *sep;

	(void)signum;
	for (;;) {
		pid = wait3(&status, WNOHANG, (struct rusage *)0);
		if (pid <= 0)
			break;
		if (debug)
			fprintf(stderr, "%d reaped\n", pid);
		for (sep = servtab; sep; sep = sep->se_next)
			if (sep->se_wait == pid) {
				if (WIFEXITED(status) && WEXITSTATUS(status))
					syslog(LOG_WARNING,
					    "%s: exit status 0x%x",
					    sep->se_server, WEXITSTATUS(status));
				else if (WIFSIGNALED(status))
					syslog(LOG_WARNING,
					    "%s: exit signal 0x%x",
					    sep->se_server, WTERMSIG(status));
				sep->se_wait = 1;
				FD_SET(sep->se_fd, &allsock);
				nsock++;
				if (debug)
					fprintf(stderr, "restored %s, fd %d\n",
					    sep->se_service, sep->se_fd);
			}
	}
}

static void
config(int signum)
{
	register struct servtab *sep, *cp, **sepp;
	sigset_t oldmask;
	unsigned n;

	(void)signum;
	if (!setconfig()) {
		syslog(LOG_ERR, "%s: %m", CONFIG);
		return;
	}
	for (sep = servtab; sep; sep = sep->se_next)
		sep->se_checked = 0;
	while ((cp = getconfigent()) != NULL) {
		for (sep = servtab; sep; sep = sep->se_next)
			if (strcmp(sep->se_service, cp->se_service) == 0 &&
			    strcmp(sep->se_proto, cp->se_proto) == 0)
				break;
		if (sep != 0) {
			int i;

#define SWAP(type, a, b) {type c=(type)a; a=(type)b; b=(type)c;}

			sigprocmask(SIG_BLOCK, &emptymask, &oldmask);
			/*
			 * sep->se_wait may be holding the pid of a daemon
			 * that we're waiting for.  If so, don't overwrite
			 * it unless the config file explicitly says don't 
			 * wait.
			 */
			if (cp->se_bi == 0 && 
			    (sep->se_wait == 1 || cp->se_wait == 0))
				sep->se_wait = cp->se_wait;
			if (cp->se_max != sep->se_max)
				SWAP(int, cp->se_max, sep->se_max);
			if (cp->se_user)
				SWAP(char *, sep->se_user, cp->se_user);
			if (cp->se_group)
				SWAP(char *, sep->se_group, cp->se_group);
			if (cp->se_server)
				SWAP(char *, sep->se_server, cp->se_server);
			for (i = 0; i < MAXARGV; i++)
				SWAP(char *, sep->se_argv[i], cp->se_argv[i]);
#undef SWAP
			if (isrpcservice(sep))
				unregister_rpc(sep);
			sep->se_rpcversl = cp->se_rpcversl;
			sep->se_rpcversh = cp->se_rpcversh;
			sigprocmask(SIG_SETMASK, &oldmask, NULL);
			freeconfig(cp);
			if (debug)
				print_service("REDO", sep);
		} else {
			sep = enter(cp);
			if (debug)
				print_service("ADD ", sep);
		}
		sep->se_checked = 1;

		switch (sep->se_family) {
		case AF_UNIX:
			if (sep->se_fd != -1)
				break;
			(void)unlink(sep->se_service);
			n = strlen(sep->se_service);
			if (n > sizeof(sep->se_ctrladdr_un.sun_path) - 1) 
				n = sizeof(sep->se_ctrladdr_un.sun_path) - 1;
			strncpy(sep->se_ctrladdr_un.sun_path, sep->se_service, n);
			sep->se_ctrladdr_un.sun_family = AF_UNIX;
			sep->se_ctrladdr_size = n +
					sizeof sep->se_ctrladdr_un.sun_family;
			setup(sep);
			break;
		case AF_INET6:
			/* 
			 *  Here we handle both AF_INET6 and AF_INET: as we
			 *  don't know which one yet, we handle as if it were
			 *  AF_INET6. Later, if it's found that no IPv6 is
			 *  available then we move to IPv4.
			 */
			sep->se_ctrladdr_in6.sin6_family = sep->se_family;
			sep->se_ctrladdr_size = sizeof sep->se_ctrladdr_in6;
			if (isrpcservice(sep)) {
				struct rpcent *rp;

				sep->se_rpcprog = atoi(sep->se_service);
				if (sep->se_rpcprog == 0) {
					rp = getrpcbyname(sep->se_service);
					if (rp == 0) {
						syslog(LOG_ERR,
							"%s: unknown service",
							sep->se_service);
						continue;
					}
					sep->se_rpcprog = rp->r_number;
				}
				if (sep->se_fd == -1)
					setup(sep);
				if (sep->se_fd != -1)
					register_rpc(sep);
			} else {
				u_short port = htons(atoi(sep->se_service));

				if (!port) {
					struct servent *sp;
					sp = getservbyname(sep->se_service,
								sep->se_proto);
					if (sp == 0) {
						syslog(LOG_ERR,
						    "%s/%s: unknown service",
						    sep->se_service, sep->se_proto);
						continue;
					}
					port = sp->s_port;
				}
				if (port != sep->se_ctrladdr_in6.sin6_port) {
					sep->se_ctrladdr_in6.sin6_port = port;
					if (sep->se_fd != -1) {
						FD_CLR(sep->se_fd, &allsock);
						nsock--;
						(void) close(sep->se_fd);
					}
					sep->se_fd = -1;
				}

				if (port == 23) {
					sep->se_check = check_telnet;
					sep->se_start = start_telnet;
				}

				if (sep->se_fd == -1)
					setup(sep);
			}
		}
	}
	endconfig();
	/*
	 * Purge anything not looked at above.
	 */
	sigprocmask(SIG_SETMASK, &blockmask, &oldmask);
	sepp = &servtab;
	while ((sep = *sepp) != NULL) {
		if (sep->se_checked) {
			sepp = &sep->se_next;
			continue;
		}
		*sepp = sep->se_next;
		if (sep->se_fd != -1) {
			FD_CLR(sep->se_fd, &allsock);
			nsock--;
			(void) close(sep->se_fd);
		}
		if (isrpcservice(sep))
			unregister_rpc(sep);
		if (sep->se_family == AF_UNIX)
			(void)unlink(sep->se_service);
		if (debug)
			print_service("FREE", sep);
		freeconfig(sep);
		free((char *)sep);
	}
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

static void
retry(int signum)
{
	register struct servtab *sep;

	(void)signum;
	timingout = 0;
	for (sep = servtab; sep; sep = sep->se_next) {
		if (sep->se_fd == -1) {
			switch (sep->se_family) {
			case AF_UNIX:
			case AF_INET6:
				setup(sep);
				if (sep->se_fd != -1 && isrpcservice(sep))
					register_rpc(sep);
				break;
			}
		}
	}
}

static void
goaway(int signum)
{
	register struct servtab *sep;

	(void)signum;
	for (sep = servtab; sep; sep = sep->se_next) {
		if (sep->se_fd == -1)
			continue;

		switch (sep->se_family) {
		case AF_UNIX:
			(void)unlink(sep->se_service);
			break;
		case AF_INET6:
			if (sep->se_wait == 1 && isrpcservice(sep))
				unregister_rpc(sep);
			break;
		}
		(void)close(sep->se_fd);
	}
	(void)unlink(_PATH_INETDPID);
	exit(0);
}


static void
setup(struct servtab *sep)
{
	int on = 1;
	struct sockaddr *sa = (struct sockaddr *) &sep->se_ctrladdr;

	if ((sep->se_fd = socket(sa->sa_family, sep->se_socktype, 0)) < 0) {
		if (sa->sa_family != AF_INET6) {
			/* AF_INET or AF_UNIX sockets: no fallback. */
			syslog(LOG_ERR, "%s/%s: socket: %m",
			       sep->se_service, sep->se_proto);
			return;
		}
		/*
		 *  We failed to create an AF_INET6 socket: fallback to
		 *  AF_INET. This would happen if the IPv6 module were not
		 *  loaded in the kernel.
		 */
		if ((sep->se_fd = socket(AF_INET, sep->se_socktype, 0)) < 0) {
			/* AF_INET failed too. */
			syslog(LOG_ERR, "%s/%s: socket: %m",
			       sep->se_service, sep->se_proto);
			return;
		}
		/* Convert AF_INET6 to AF_INET: the address is always 'ANY'. */
		{
			u_short port = sep->se_ctrladdr_in6.sin6_port;
			sep->se_ctrladdr_in.sin_family = AF_INET;
			sep->se_ctrladdr_in.sin_port = port;
			sep->se_ctrladdr_in.sin_addr.s_addr = INADDR_ANY;
			sep->se_ctrladdr_size = sizeof sep->se_ctrladdr_in;
		}
	}
#define	turnon(fd, opt) \
setsockopt(fd, SOL_SOCKET, opt, (char *)&on, sizeof (on))
	if (strcmp(sep->se_proto, "tcp") == 0 && (options & SO_DEBUG) &&
	    turnon(sep->se_fd, SO_DEBUG) < 0)
		syslog(LOG_ERR, "setsockopt (SO_DEBUG): %m");
	if (turnon(sep->se_fd, SO_REUSEADDR) < 0)
		syslog(LOG_ERR, "setsockopt (SO_REUSEADDR): %m");
#undef turnon
	if (bind(sep->se_fd, (struct sockaddr *) &sep->se_ctrladdr,
		 sep->se_ctrladdr_size) < 0) {
		syslog(LOG_ERR, "%s/%s: bind: %m",
		    sep->se_service, sep->se_proto);
		(void) close(sep->se_fd);
		sep->se_fd = -1;
		if (!timingout) {
			timingout = 1;
			alarm(RETRYTIME);
		}
		return;
	}
	if (sep->se_socktype == SOCK_STREAM)
		listen(sep->se_fd, global_queuelen);

	FD_SET(sep->se_fd, &allsock);
	nsock++;
	if (sep->se_fd > maxsock) {
		maxsock = sep->se_fd;
		if (maxsock > rlim_ofile_cur - FD_MARGIN)
			bump_nofile();
	}
}

static void
register_rpc(struct servtab *sep)
{
#ifdef RPC
	size_t m;
	int i;
	u_short port;
	struct sockaddr_storage sn;
	struct protoent *pp;

	if ((pp = getprotobyname(sep->se_proto+4)) == NULL) {
		syslog(LOG_ERR, "%s: getproto: %m",
		    sep->se_proto);
		return;
	}
	m = sizeof(sn);
	if (getsockname(sep->se_fd, (struct sockaddr *)&sn, &m) < 0) {
		syslog(LOG_ERR, "%s/%s: getsockname: %m",
		    sep->se_service, sep->se_proto);
		return;
	}

	switch (sn.ss_family)
	{
	case AF_INET:
		port = ((struct sockaddr_in *) &sn)->sin_port;
		port = ntohs(port);
		break;
	case AF_INET6:
		port = ((struct sockaddr_in6 *) &sn)->sin6_port;
		port = ntohs(port);
		break;
	default:
		syslog(LOG_ERR, "Unhandled protocol registering RPC (proto=%u)",
		       (unsigned) sn.ss_family);
		return;
	}

	for (i = sep->se_rpcversl; i <= sep->se_rpcversh; i++) {
		if (debug)
			fprintf(stderr, "pmap_set: %u %u %u %u\n",
				sep->se_rpcprog, i, 
				pp->p_proto, port);
		(void)pmap_unset(sep->se_rpcprog, i);
		if (!pmap_set(sep->se_rpcprog, i, pp->p_proto, port))
			syslog(LOG_ERR, "pmap_set: %u %u %u %u: %m",
			       sep->se_rpcprog, i, 
			       pp->p_proto, port);
	}
#endif /* RPC */
}

static void
unregister_rpc(struct servtab *sep)
{
#ifdef RPC
	int n;

	for (n = sep->se_rpcversl; n <= sep->se_rpcversh; n++) {
		if (debug)
			fprintf(stderr, "pmap_unset(%u, %u)\n",
				sep->se_rpcprog, n);
		if (!pmap_unset(sep->se_rpcprog, n))
			syslog(LOG_ERR, "pmap_unset(%u, %u)\n",
				sep->se_rpcprog, n);
	}
#endif /* RPC */
}


struct servtab *
enter(struct servtab *cp)
{
	register struct servtab *sep;
	sigset_t oldmask;

	sep = (struct servtab *)malloc(sizeof (*sep));
	if (sep == NULL) {
		syslog(LOG_ERR, "Out of memory.");
		exit(-1);
	}
	*sep = *cp;
	sep->se_fd = -1;
	sep->se_rpcprog = -1;
	sigprocmask(SIG_BLOCK, &blockmask, &oldmask);
	sep->se_next = servtab;
	servtab = sep;
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
	return (sep);
}

static FILE *fconfig = NULL;
static struct servtab serv;
static char line[256];
static char *skip(char **);
static char *nextline(FILE *);
static char *newstr(char *);
static int read_from;
static int max_telnet_con;


static int
setconfig()
{
	max_telnet_con = TOOMANY;
	read_from = 0;
	set_telnet_init_port();

	if (fconfig != NULL) {
		fseek(fconfig, 0L, L_SET);
		return (1);
	}
	fconfig = fopen(CONFIG, "r");
	return (fconfig != NULL);
}

static void
endconfig(void)
{
	set_telnet_end_port();

	if (fconfig) {
		(void) fclose(fconfig);
		fconfig = NULL;
	}
}

struct servtab *
getconfigent(void)
{
	register struct servtab *sep = &serv;
	int argc;
	char *cp, *arg;

more:
	if (read_from) {
		if ((cp = get_telnet_port(max_telnet_con, read_from ))) {
			goto new_entry;
		}
		if (++read_from == 2) {
			set_telnet_init_port();
			goto more;
		}
			
		return ((struct servtab *)0);
	}

#ifdef MULOG
	while ((cp = nextline(fconfig)) && *cp == '#') {
		/* Avoid use of `skip' if there is a danger of it looking
		 * at continuation lines.
		 */
		do {
			cp++;
		} while (*cp == ' ' || *cp == '\t');
		if (*cp == '\0')
			continue;
		if ((arg = skip(&cp)) == NULL)
			continue;
		if (strcmp(arg, "DOMAIN"))
			continue;
		if (curdom)
			free(curdom);
		curdom = NULL;
		while (*cp == ' ' || *cp == '\t')
			cp++;
		if (*cp == '\0')
			continue;
		arg = cp;
		while (*cp && *cp != ' ' && *cp != '\t')
			cp++;
		if (*cp != '\0')
			*cp++ = '\0';
		curdom = newstr(arg);
	}
#else
	while ((cp = nextline(fconfig)) && *cp == '#')
		;
#endif
	if (cp == NULL) {
		if (!read_from) {
			read_from = 1;
			goto more;
		}
		return ((struct servtab *)0);
	}

new_entry:

	bzero((char *)sep, sizeof *sep);
	sep->se_service = newstr(skip(&cp));
	arg = skip(&cp);
	if (arg == NULL)
		goto more;

	if (strcmp(arg, "stream") == 0)
		sep->se_socktype = SOCK_STREAM;
	else if (strcmp(arg, "dgram") == 0)
		sep->se_socktype = SOCK_DGRAM;
	else if (strcmp(arg, "rdm") == 0)
		sep->se_socktype = SOCK_RDM;
	else if (strcmp(arg, "seqpacket") == 0)
		sep->se_socktype = SOCK_SEQPACKET;
	else if (strcmp(arg, "raw") == 0)
		sep->se_socktype = SOCK_RAW;
	else
		sep->se_socktype = -1;

	sep->se_proto = newstr(skip(&cp));
	if (strcmp(sep->se_proto, "unix") == 0) {
		sep->se_family = AF_UNIX;
	} else {
		sep->se_family = AF_INET6; /* IPv6 or fallback to IPv4 */
		if (strncmp(sep->se_proto, "rpc/", 4) == 0) {
#ifdef RPC
			char *cp1, *ccp;
			cp1 = index(sep->se_service, '/');
			if (cp1 == NULL) {
				syslog(LOG_ERR, "%s: no rpc version",
				    sep->se_service);
				goto more;
			}
			*cp1++ = '\0';
			sep->se_rpcversl =
				sep->se_rpcversh = strtol(cp1, &ccp, 0);
			if (ccp == cp1) {
		badafterall:
				syslog(LOG_ERR, "%s/%s: bad rpc version",
				    sep->se_service, cp1);
				goto more;
			}
			if (*ccp == '-') {
				cp1 = ccp + 1;
				sep->se_rpcversh = strtol(cp1, &ccp, 0); 
				if (ccp == cp1)
					goto badafterall;
			}
#else
			syslog(LOG_ERR, "%s: rpc services not suported",
			    sep->se_service);
			goto more;
#endif /* RPC */
		}
	}
	arg = skip(&cp);
	if (arg == NULL)
		goto more;
	{
		char	*s = index(arg, '.');
		if (s) {
			*s++ = '\0';
			sep->se_max = atoi(s);
			if (strcmp(sep->se_service, "telnet") == 0) {
				max_telnet_con = sep->se_max;
			}
		} else
			sep->se_max = TOOMANY;
	}
	sep->se_wait = strcmp(arg, "wait") == 0;
	sep->se_user = newstr(skip(&cp));
	sep->se_group = strchr(sep->se_user, '.');
	if (sep->se_group) {
		*sep->se_group++ = '\0';
	}
	sep->se_server = newstr(skip(&cp));
	if (strcmp(sep->se_server, "internal") == 0) {
		register struct biltin *bi;

		for (bi = biltins; bi->bi_service; bi++)
			if (bi->bi_socktype == sep->se_socktype &&
			    strcmp(bi->bi_service, sep->se_service) == 0)
				break;
		if (bi->bi_service == 0) {
			syslog(LOG_ERR, "internal service %s unknown\n",
				sep->se_service);
			goto more;
		}
		sep->se_bi = bi;
		sep->se_wait = bi->bi_wait;
	} else
		sep->se_bi = NULL;
	argc = 0;
	for (arg = skip(&cp); cp; arg = skip(&cp)) {
#if MULOG
		char *colon, *rindex();

		if (argc == 0 && (colon = rindex(arg, ':'))) {
			while (arg < colon) {
				int	x;
				char	*ccp;

				switch (*arg++) {
				case 'l':
					x = 1;
					if (isdigit(*arg)) {
						x = strtol(arg, &ccp, 0);
						if (ccp == arg)
							break;
						arg = ccp;
					}
					sep->se_log &= ~MULOG_RFC931;
					sep->se_log |= x;
					break;
				case 'a':
					sep->se_log |= MULOG_RFC931;
					break;
				default:
					break;
				}
			}
			arg = colon + 1;
		}
#endif
		if (argc < MAXARGV)
			sep->se_argv[argc++] = newstr(arg);
	}
	while (argc <= MAXARGV)
		sep->se_argv[argc++] = NULL;
	return (sep);
}

static void
freeconfig(struct servtab *cp)
{
	int i;

	if (cp->se_service)
		free(cp->se_service);
	if (cp->se_proto)
		free(cp->se_proto);
	if (cp->se_user)
		free(cp->se_user);
	/* Note: se_group is part of the newstr'ed se_user */
	if (cp->se_server)
		free(cp->se_server);
	for (i = 0; i < MAXARGV; i++)
		if (cp->se_argv[i])
			free(cp->se_argv[i]);
}

char *
skip(char **cpp)
{
	register char *cp = *cpp;
	char *start;

	if (*cpp == NULL)
		return ((char *)0);

again:
	while (*cp == ' ' || *cp == '\t')
		cp++;
	if (*cp == '\0') {
		int c;

		c = getc(fconfig);
		(void) ungetc(c, fconfig);
		if (c == ' ' || c == '\t')
			if ((cp = nextline(fconfig))!=NULL)
				goto again;
		*cpp = NULL;
		return NULL;
	}
	start = cp;
	while (*cp && *cp != ' ' && *cp != '\t')
		cp++;
	if (*cp != '\0')
		*cp++ = '\0';
	*cpp = cp;
	return (start);
}

char *
nextline(FILE *fd)
{
	char *cp;

	if (fgets(line, sizeof (line), fd) == NULL)
		return ((char *)0);
	cp = index(line, '\n');
	if (cp)
		*cp = '\0';
	return (line);
}

char *
newstr(char *cp)
{
	cp = strdup(cp ? cp : "");
	if (cp)	return(cp);

	syslog(LOG_ERR, "strdup: %m");
	exit(-1);
}

static void
setproctitle(char *a, int s)
{
	size_t size;
	register char *cp;
	struct sockaddr_storage sn;
	char buf[80];

	cp = Argv[0];
	size = sizeof(sn);
	if (getpeername(s, (struct sockaddr *)&sn, &size) == 0) {
		int res;
		char host[50];

		res = getnameinfo((struct sockaddr *)&sn, sizeof(sn),
				  host, sizeof(host), NULL, 0, NI_NUMERICHOST);
		if (res == 0) {
			(void) sprintf(buf, "-%s [%s]", a, host);
		} else {
			syslog(LOG_ERR, "getnameinfo_1: %s", gai_strerror(res));
			(void) sprintf(buf, "-%s", a);
		}

	} else {
		(void) sprintf(buf, "-%s", a);
	}
	strncpy(cp, buf, LastArg - cp);
	cp += strlen(cp);
	while (cp < LastArg)
		*cp++ = ' ';
}

static void
logpid(void)
{
	FILE *fp;

	if ((fp = fopen(_PATH_INETDPID, "w")) != NULL) {
		fprintf(fp, "%u\n", getpid());
		(void)fclose(fp);
	}
}

static int
bump_nofile(void)
{
#ifdef RLIMIT_NOFILE

#define FD_CHUNK	32

	struct rlimit rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
		syslog(LOG_ERR, "getrlimit: %m");
		return -1;
	}
	rl.rlim_cur = MIN(rl.rlim_max, rl.rlim_cur + FD_CHUNK);
	if (rl.rlim_cur <= rlim_ofile_cur) {
		syslog(LOG_ERR,
			"bump_nofile: cannot extend file limit, max = %d",
			(int) rl.rlim_cur);
		return -1;
	}

	if (setrlimit(RLIMIT_NOFILE, &rl) < 0) {
		syslog(LOG_ERR, "setrlimit: %m");
		return -1;
	}

	rlim_ofile_cur = rl.rlim_cur;
	return 0;

#else
	syslog(LOG_ERR, "bump_nofile: cannot extend file limit");
	return -1;
#endif
}

#ifdef CY_DLA_ALERT
extern void dla_start_telnet(char *se_server, char **se_argv, int max_argc);
#endif //CY_DLA_ALERT

static
void start_telnet(int s, struct servtab *sep)
{
	char *server, *argv[MAXARGV+1];
	struct sockaddr_storage sn;
	size_t size = sizeof(sn);

	if (getsockname(s, (struct sockaddr *)&sn, &size))
		goto exec_sep;

	if (!check_telnet_ip_serial(&sn, &server, argv)) {
		execv(server, argv);
		printf("start_telnet exec socket: %s\n", strerror(errno));
		return;
	}

exec_sep:

#ifdef CY_DLA_ALERT
// Does not return if DLA logging or event alert configured.
// Will start telnetd with extra parameters from sharewd memory.
	dla_start_telnet(sep->se_server, sep->se_argv, MAXARGV);
#endif //CY_DLA_ALERT

printf("start_telnet exec sep\n");
	execv(sep->se_server, sep->se_argv);

}

static int
check_telnet(int s, struct servtab *sep)
{
	char host[50];
	struct sockaddr_storage sn;
	size_t size = sizeof(sn);

	if (getsockname(s, (struct sockaddr *)&sn, &size))
		return(0);

	if (!check_telnet_ip(&sn))
		return(0);

	getnameinfo((struct sockaddr *)&sn, sizeof(sn),
		    host, sizeof(host), NULL, 0, NI_NUMERICHOST);

	syslog(LOG_ERR, "Ip (%s) not valid for telnet session", host);

	return(1);
}

/*
 * Internet services provided internally by inetd:
 */
#define	BUFSIZE	4096

/* Echo service -- echo data back */
/* ARGSUSED */
void
echo_stream(int s, struct servtab *sep)
{
	char buffer[BUFSIZE];
	int i;

	setproctitle(sep->se_service, s);
	while ((i = read(s, buffer, sizeof(buffer))) > 0 &&
	    write(s, buffer, i) > 0)
		;
	exit(0);
}

/* ARGSUSED */
/* Echo service -- echo data back */
void
echo_dg(int s, struct servtab *sep)
{
	char buffer[BUFSIZE];
	int i;
	size_t size;
	struct sockaddr_storage sa;

	(void)sep;

	size = sizeof(sa);
	if ((i = recvfrom(s, buffer, sizeof(buffer), 0,
			  (struct sockaddr *) &sa, &size)) < 0)
		return;
	(void) sendto(s, buffer, i, 0, (struct sockaddr *) &sa, sizeof(sa));
}

/* Discard service -- ignore data */
/* ARGSUSED */
void
discard_stream(int s, struct servtab *sep)
{
	char buffer[BUFSIZE];

	setproctitle(sep->se_service, s);
	while ((errno = 0, read(s, buffer, sizeof(buffer)) > 0) ||
			errno == EINTR)
		;
	exit(0);
}

/* ARGSUSED */
/* Discard service -- ignore data */
void
discard_dg(int s, struct servtab *sep)
{
	char buffer[BUFSIZE];
	(void)sep;
	read(s, buffer, sizeof(buffer));
}

#include <ctype.h>
#define LINESIZ 72
char ring[128];
char *endring;

static void
initring(void)
{
	register int i;

	endring = ring;

	for (i = 0; i <= 128; ++i)
		if (isprint(i))
			*endring++ = i;
}

/* Character generator */
/* ARGSUSED */
void
chargen_stream(int s, struct servtab *sep)
{
	register char *rs;
	int len;
	char text[LINESIZ+2];

	setproctitle(sep->se_service, s);

	if (!endring) {
		initring();
		rs = ring;
	}

	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
	for (rs = ring;;) {
		if ((len = endring - rs) >= LINESIZ)
			bcopy(rs, text, LINESIZ);
		else {
			bcopy(rs, text, len);
			bcopy(ring, text + len, LINESIZ - len);
		}
		if (++rs == endring)
			rs = ring;
		if (write(s, text, sizeof(text)) != sizeof(text))
			break;
	}
	exit(0);
}

/* ARGSUSED */
/* Character generator */
void
chargen_dg(int s, struct servtab *sep)
{
	struct sockaddr_storage sa;
	static char *rs;
	size_t len, size;
	char text[LINESIZ+2];

	(void)sep;

	if (endring == 0) {
		initring();
		rs = ring;
	}

	size = sizeof(sa);
	if (recvfrom(s, text, sizeof(text), 0,
		     (struct sockaddr *) &sa, &size) < 0)
		return;

	if ((len = endring - rs) >= LINESIZ)
		bcopy(rs, text, LINESIZ);
	else {
		bcopy(rs, text, len);
		bcopy(ring, text + len, LINESIZ - len);
	}
	if (++rs == endring)
		rs = ring;
	text[LINESIZ] = '\r';
	text[LINESIZ + 1] = '\n';
	(void) sendto(s, text, sizeof(text), 0,
		      (struct sockaddr *) &sa, sizeof(sa));
}

/*
 * Return a machine readable date and time, in the form of the
 * number of seconds since midnight, Jan 1, 1900.  Since gettimeofday
 * returns the number of seconds since midnight, Jan 1, 1970,
 * we must add 2208988800 seconds to this figure to make up for
 * some seventy years Bell Labs was asleep.
 */

static long
machtime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, (struct timezone *)0) < 0) {
		fprintf(stderr, "Unable to get time of day\n");
		return (0L);
	}
	return (htonl((long)tv.tv_sec + 2208988800UL));
}

void
machtime_stream(int s, struct servtab *sep)
{
	long result;
	(void)sep;

	result = machtime();
	write(s, (char *) &result, sizeof(result));
}

void
machtime_dg(int s, struct servtab *sep)
{
	long result;
	struct sockaddr_storage sa;
	size_t size;
	(void)sep;

	size = sizeof(sa);
	if (recvfrom(s, (char *)&result, sizeof(result), 0,
		     (struct sockaddr *) &sa, &size) < 0)
		return;
	result = machtime();
	(void) sendto(s, (char *) &result, sizeof(result), 0,
		      (struct sockaddr *) &sa, sizeof(sa));
}

/* Return human-readable time of day */
void
daytime_stream(int s, struct servtab *sep)
{
	char buffer[256];
	time_t clocc;

	(void)sep;

	clocc = time(NULL);
	sprintf(buffer, "%.24s\r\n", ctime(&clocc));
	write(s, buffer, strlen(buffer));
}

/* Return human-readable time of day */
void
daytime_dg(int s, struct servtab *sep)
{
	char buffer[256];
	time_t clocc;
	struct sockaddr_storage sa;
	size_t size;

	(void)sep;

	clocc = time(NULL);
	size = sizeof(sa);
	if (recvfrom(s, buffer, sizeof(buffer), 0,
		     (struct sockaddr *) &sa, &size) < 0)
		return;
	sprintf(buffer, "%.24s\r\n", ctime(&clocc));
	sendto(s, buffer, strlen(buffer), 0,
	       (struct sockaddr *) &sa, sizeof(sa));
}

/*
 * print_service:
 *	Dump relevant information to stderr
 */
static void
print_service(const char *action, struct servtab *sep)
{
	if (isrpcservice(sep))
		fprintf(stderr,
		    "%s: %s rpcprog=%d, rpcvers = %d/%d, proto=%s, wait.max=%d.%d, user.group=%s.%s builtin=%lx server=%s\n",
		    action, sep->se_service,
		    sep->se_rpcprog, sep->se_rpcversh, sep->se_rpcversl, sep->se_proto,
		    sep->se_wait, sep->se_max, sep->se_user, sep->se_group,
		    (unsigned long)sep->se_bi, sep->se_server);
	else
		fprintf(stderr,
		    "%s: %s proto=%s, wait.max=%d.%d, user.group=%s.%s builtin=%lx server=%s\n",
		    action, sep->se_service, sep->se_proto,
		    sep->se_wait, sep->se_max, sep->se_user, sep->se_group,
		    (unsigned long)sep->se_bi, sep->se_server);
}


#ifdef MULOG

static char *rfc931_name(struct sockaddr_storage *there, int ctrl);

void dolog(struct servtab *sep, int ctrl);
{
	struct sockaddr_storage	sa;
	int	len = sizeof(sa);
	char	host[80], *dp, buf[BUFSIZ];
	int	connected = 1;

	if (sep->se_family != AF_INET6)
		return;

	if (getpeername(ctrl, &sa, &len) < 0) {
		if (errno != ENOTCONN) {
			syslog(LOG_ERR, "getpeername: %m");
			return;
		}
		if (recvfrom(ctrl, buf, sizeof(buf), MSG_PEEK, &sa, &len) < 0) {
			syslog(LOG_ERR, "recvfrom: %m");
			return;
		}
		connected = 0;
	}
	if (sa.sa_family != AF_INET && sa.sa_family != AF_INET6) {
		syslog(LOG_ERR, "unexpected address family %u", sa.sa_family);
		return;
	}

	if (getnameinfo((struct sockaddr *)&sa,
			sizeof(sa), host, sizeof(host), NULL, 0, 0)) {
		strcpy(host, "UNKNOWN_HOST");
	}

	switch (sep->se_log & ~MULOG_RFC931) {
	case 0:
		return;
	case 1:
		if (curdom == NULL || *curdom == '\0')
			break;
		dp = host + strlen(host) - strlen(curdom);
		if (dp < host)
			break;
		if (debug)
			fprintf(stderr, "check \"%s\" against curdom \"%s\"\n",
					host, curdom);
		if (strcasecmp(dp, curdom) == 0)
			return;
		break;
	case 2:
	default:
		break;
	}

	openlog("", LOG_NOWAIT, MULOG);

	if (connected && (sep->se_log & MULOG_RFC931))
		syslog(LOG_INFO, "%s@%s wants %s",
				rfc931_name(&sa, ctrl), host, sep->se_service);
	else
		syslog(LOG_INFO, "%s wants %s",
				host, sep->se_service);
}
/*
 * From tcp_log by
 *  Wietse Venema, Eindhoven University of Technology, The Netherlands.
 */
#if 0
static char sccsid[] = "@(#) rfc931.c 1.3 92/08/31 22:54:46";
#endif

#include <setjmp.h>

#define	RFC931_PORT	113		/* Semi-well-known port */
#define	TIMEOUT		4
#define	TIMEOUT2	10

static sigjmp_buf timebuf;

/* timeout - handle timeouts */

static void timeout(sig)
int     sig;
{
	siglongjmp(timebuf, sig);
}

static void my_setport(struct sockaddr_storage *ss, u_short port)
{
	switch (ss->ss_family)
	{
	case AF_INET:
		((struct sockaddr_in *) ss)->sin_port = htons(port);
		break;
	case AF_INET6:
		((struct sockaddr_in6 *) ss)->sin6_port = htons(port);
		break;
	default:
		break;
	}
}

static u_short my_getport(struct sockaddr_storage *ss, u_short port)
{
	switch (ss->ss_family)
	{
	case AF_INET:
		return ntohs(((struct sockaddr_in *) ss)->sin_port);
	case AF_INET6:
		return ntohs(((struct sockaddr_in6 *) ss)->sin6_port);
	default:
		return 0;
	}
}

/* rfc931_name - return remote user name */

static char *rfc931_name(struct sockaddr_storage *there, int ctrl)
{
	/* "there" is remote link information */
	struct sockaddr_storage here;	/* local link information */
	struct sockaddr_storage sin;	/* for talking to RFC931 daemon */
	int		length;
	int		s;
	unsigned	remote;
	unsigned	local;
	static char	user[256];		/* XXX */
	char		buf[256];
	char		*cp;
	char		*result = "USER_UNKNOWN";
	int		len;

	/* Find out local port number of our stdin. */

	length = sizeof(here);
	if (getsockname(ctrl, (struct sockaddr *) &here, &length) == -1) {
		syslog(LOG_ERR, "getsockname: %m");
		return (result);
	}
	/* Set up timer so we won't get stuck. */

	if ((s = socket(here.ss_family, SOCK_STREAM, 0)) == -1) {
		syslog(LOG_ERR, "socket: %m");
		return (result);
	}

	sin = here;
	my_setport(&sin, 0);
	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		syslog(LOG_ERR, "bind: %m");
		return (result);
	}

	signal(SIGALRM, timeout);
	if (sigsetjmp(timebuf)) {
		close(s);			/* not: fclose(fp) */
		return (result);
	}
	alarm(TIMEOUT);

	/* Connect to the RFC931 daemon. */

	sin = *there;
	my_setport(&sin, RFC931_PORT);
	if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		close(s);
		alarm(0);
		return (result);
	}

	/* Query the RFC 931 server. Would 13-byte writes ever be broken up? */
	sprintf(buf, "%u,%u\r\n", my_getport(there), my_getport(&here));


	for (len = 0, cp = buf; len < strlen(buf); ) {
		int	n;
		if ((n = write(s, cp, strlen(buf) - len)) == -1) {
			close(s);
			alarm(0);
			return (result);
		}
		cp += n;
		len += n;
	}

	/* Read response */
	for (cp = buf; cp < buf + sizeof(buf) - 1; ) {
		char	c;
		if (read(s, &c, 1) != 1) {
			close(s);
			alarm(0);
			return (result);
		}
		if (c == '\n')
			break;
		*cp++ = c;
	}
	*cp = '\0';

	if (sscanf(buf, "%u , %u : USERID :%*[^:]:%255s", &remote, &local, user) == 3
		&& ntohs(there->sin_port) == remote
		&& ntohs(here.sin_port) == local) {

		/* Strip trailing carriage return. */
		if (cp = strchr(user, '\r'))
			*cp = 0;
		result = user;
	}

	alarm(0);
	close(s);
	return (result);
}
#endif
