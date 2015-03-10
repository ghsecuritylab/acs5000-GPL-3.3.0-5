/* Copyright (c) 2002 Art & Logic, Inc. All Rights Reserved.         */
/* $Id: Param.c,v 1.45 2010/07/19 23:59:11 regina Exp $ */

#include "GetFuncs.h"
#include "SetFuncs.h"
#include "Param.h"
#include "UserFunc.h"

// already included via UserFunc.h...
#if defined(KVM) || defined(ONS)
#include "KVMFunc.h"
extern KVMReqData gKVMReq;
#endif

int kZeroIndex = 0;
int kDoisIndex = 2;
#ifdef ONS
int kMaxAuxIndex = 3;
#elif defined KVMNETP
int kMaxAuxIndex = 2;
#endif
int kMaxFanIndex = 3;


/* uC and microcode related errors */
char *uCRelatedErrors[] = {
"",
""
};

/*
 * each entry in the parameter table needs to have the following fields:
 */

#if 0
   {
      T(""),               /* key */
      kNoType,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif

/* initialized and declared `extern' 
extern Param parameterList[] = */
Param parameterList[] = 
{
   {
      T("system"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef KVM
   {
      T("temp"),            /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numOutlets"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      KVMPMGetNumPorts,    /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.temp.numOutlets), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("temp"),            /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif //KVM
 
   /*--------------------------------------------------------------------------
   Request - this is for exchanging request-level (ultra-transient) information
   A page may set req.foo, which corresponds to a var on ths server which any
   'commitFunc' can inspect.  There is no good way to guarantee that these are
   always reset for the next request; by convention: any page that sets these
   should have a corresponding 'commitFunc' that can clear them when finished.
   This mechanism should be replaced with a more integrated one that doesn't
   require the param-tree and always re-sets values after a request is
   processed.
   --------------------------------------------------------------------------*/
   {
      T("req"),            /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.action),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sid"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.sid),         /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bogus"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.bogus),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      31,                  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("logout"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      Logout,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.logout),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      31,                  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("req"),            /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   {
      T("tablePage"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,           /* queryFunc */
      0,                   /* last query */
      tablePageCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bogus"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.bogus),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      31,                  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tablePage"),            /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
   Device
   --------------------------------------------------------------------------*/
   {
      T("device"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetDevice,           /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("class"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt8,         /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.klass), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("model"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.model), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kModelLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(KVM) || defined(ONS)
   {
      T("kvmanalog"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.kvmanalog), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numkvmports"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.numkvmports), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("picture"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.picture), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPictureLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("number"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.number), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef ONS
   {
      T("number2"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.number2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("swVersion"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.swVersion), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSwVersionLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("olhVersion"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.olhVersion), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSwVersionLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostName"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.hostName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ip"),             /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.ip), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef IPv6enable
   {
      T("ip6"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.ip6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIp6Length,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("prefix6"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.device.prefix6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("device"),         /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   Login
   --------------------------------------------------------------------------*/
   {
      T("login"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      Login,               /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("username"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gLogin.userName),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(KVM) || defined(ONS)
   {
      T("kvmport"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gLogin.KVMPort),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      MAX_PORT_FIELD_LEN,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   }, 
   {
      T("directacc"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetLoginDirectAccConf, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gLogin.directacc), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("userlogin"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      fakeCommit,          /* commitFunc */
      0,                   /* last commit */
      &(gLogin.userLogin),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("password"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gLogin.password),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("confirm"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt8,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      LoginConfirm,        /* commitFunc */
      0,                   /* last commit */
      &(gLogin.confirm),   /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("login"),          /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   WIZARD -- Net Settings   &   EXPERT -- Network | Host Settings
   --------------------------------------------------------------------------*/
   {
      T("netSettings"),    /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetNetSettings,      /* queryFunc */
      0,                   /* last query */
      netSettingsCommit,   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"), 	       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dhcp"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.dhcp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostName"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.hostName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipAddress1"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.ipAddress1), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("netMask1"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.netMask1), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dns1"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.dnsService.dns1),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDnsLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("domain"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.dnsService.domainName),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("gateway"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.gateway), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("consBanner"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.consBanner), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kConsoleBannerLength,/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipAddress2"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.ipAddress2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("netMask2"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.netMask2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mtu"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.mtu), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dns2"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.dnsService.dns2),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDnsLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef BONDING_FEATURE
    /****** BONDING CONFIGURATION PARAMETERS **********/
   {//bond start
      T("bondenabled"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.bond.enabled), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bondmiimon"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.bond.miimon), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bondupdelay"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.bond.updelay), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
//bond end
#endif
#ifdef IPv6enable
   {
      T("enableIPv4"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.enableIPv4), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enableIPv6"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.enableIPv6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("IPv6method"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.IPv6method), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ethIp6"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.ethIp6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIp6Length,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ethPrefix6"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.ethPrefix6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DHCPv6Opts"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.DHCPv6Opts), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("gateway6"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.netSettings.gateway6), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("netSettings"),    /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   //[AP][2007-08-02] hostname discovery
   {
      T("autoDiscovery"),    /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetAutoDiscovery,    /* queryFunc */
      0,                   /* last query */
      autoDiscoveryCommit, /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADStringChange"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.autoDiscovery.ADStringChange), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADProbeString"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.autoDiscovery.ADProbeString), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      2*kADStringLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADAnswerString"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.autoDiscovery.ADAnswerString), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      2*kADStringLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("autoDiscovery"),    /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   WIZARD -- CAS Profile Settings
   --------------------------------------------------------------------------*/
   {
      T("casProSettings"), /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetCasProSettings,   /* queryFunc */
      0,                   /* last query */
      wizardCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocol"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.protocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("baudRate"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.baudRate), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataSize"),	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.dataSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stopBits"),  /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.stopBits), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("parity"),  	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.parity), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("flowControl"),    /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.flowControl), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authReq"),	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.authReq), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enableAll"),	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.casProSettings.enableAll), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("casProSettings"), /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   WIZARD -- Access
   --------------------------------------------------------------------------*/
   {
      T("access"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,	   	   /* queryFunc */
      0,                   /* last query */
      accessCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("usersHtml"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetAccessUser,       /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.usersHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		            /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("usersCs"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.usersCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupsHtml"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetAccessGroup,      /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.groupsHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupsCs"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.groupsCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selected"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.selected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
   WIZARD -- Access | AddModUser
   --------------------------------------------------------------------------*/
   {
      T("addModUser"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,     /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("userName"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.userName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("passWord"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.passWord), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("passWord2"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.passWord2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupAdminReg"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.groupAdminReg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupBio"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.groupBio), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("shell"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.shell), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("comments"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModUser.comments), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("addModUser"),    /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
   WIZARD -- Access | AddModGroup 
   --------------------------------------------------------------------------*/
   {
      T("addModGroup"),    /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetGroupSelected,    /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("grpName"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModGroup.newGrpName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kGroupNameLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("grpMembers"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.access.addModGroup.usersInGrp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("addModGroup"),    /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("access"),         /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   WIZARD -- Data Buffering
   --------------------------------------------------------------------------*/
   {
      T("dataBuffering"),  /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetDataBuffering,    /* queryFunc */
      0,                   /* last query */
      wizardCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.dataBuffering.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fileSize"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.dataBuffering.fileSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nfsPath"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.dataBuffering.nfsPath), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("showMenu"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.dataBuffering.showMenu), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("timeStamp"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.dataBuffering.timeStamp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataBuffering"),  /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
   WIZARD and EXPERT->NETWORK -- System Log
   --------------------------------------------------------------------------*/
   {
      T("systemLog"),      /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSystemLog,        /* queryFunc */
      0,                   /* last query */
      SystemLogCommit,     /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("facilityNumber"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.facilityNumber), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(KVM) || defined(ONS)
   {
      T("KVMfacility"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.KVMfacility), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("serversHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.serversHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serversCs"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.serversCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dest"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.dest), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("CASlevel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.filter.CASlevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("KVMlevel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.filter.KVMlevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("Buflevel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.filter.Buflevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("Weblevel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.filter.Weblevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("Syslevel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.filter.Syslevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dummy"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.systemLog.dummy), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("systemLog"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
     EXPERT->PORTS  
     EXPERT->APPLICATIONS->CONNECT
   --------------------------------------------------------------------------*/
   {
      T("ports"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,         /* queryFunc */
      0,                   /* last query */
      NULL,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef PMD
   {
      T("numIpdus"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetNumIpdus,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("placeholder"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gReq.bogus),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      31,                  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("connectPortsHtml"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetConnectPortsHtml,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.connectPortsHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   //[RK]Sep/14/04 - Ports Status - Refresh Action  
   {
      T("portstatus"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetPortsStatusHtml,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.portsStatusHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   //[RK]Jan/28/01 - Ports Statistics - Refresh Action  
   {
      T("portstatistics"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetPortsStatisticsHtml,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.portsStatisticsHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
     
     
#if defined(KVM) || defined(ONS) 
   {
	   T("connport"),/* key */
	   kString,             /* dataType */
	   -1,                  /* read access level */
	   -1,                  /* write access level */
	   NULL,                /* getFunc */
	   dmfSetStringFixed,   /* setFunc */
	   NULL,                /* queryFunc */
	   0,                   /* lastQuery */
	   KVMConnectPort,      /* commitFunc */
	   0,                   /* last commit */
	   &(gKVMReq.kvmconnport), /* dataStart */
	   0,                   /* offset */
	   NULL,                /* startIndex */
	   NULL,                /* endIndex */
	   0,                   /* lowerLimit */
	   32,                /* upperLimit */
	   -1,                  /* parent -- keep this -1 */
   },
   {
	   T("connresult"),/* key */
	   kString,             /* dataType */
	   -1,                  /* read access level */
	   -1,                  /* write access level */
	   dmfGetString,        /* getFunc */
	   NULL,                /* setFunc */
	   KVMConnQuery,            /* queryFunc */
	   0,                   /* lastQuery */
	   NULL,                /* commitFunc */
	   0,                   /* last commit */
	   &(gKVMReq.kvmconnresult), /* dataStart */
	   0,                   /* offset */
	   NULL,                /* startIndex */
	   NULL,                /* endIndex */
	   0,                   /* lowerLimit */
	   0,                       /* upperLimit */
	   -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("physTableHtml"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetPhysTableHtml,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.physTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADProbeString"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.ADProbeString), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      2*kADStringLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADAnswerString"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.ADAnswerString), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      2*kADStringLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("physAction"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,      	   /* queryFunc */
      0,                   /* last query */
      PhysActionCommit,	   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selected"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.selected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef PMD
   {
      T("numPowerMgm"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,        	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.numPowerMgm), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("physAction"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("physP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetPhysPConf,    	   /* queryFunc */
      0,                   /* last query */
      PhysPortCommit,	   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.physPortAction), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numPortsel"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.numPortsel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("general"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,     /* queryFunc */
      0,                   /* last query */
      NULL,	   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enable"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.enable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocol"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.protocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("alias"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.alias), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef PMDNG
   {
      T("pmvendor"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.pmVendor), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("stallowed"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.stallowed), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifndef KVM
#ifdef PMD
   {
      T("pmsessions"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.general.pmsessions), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#endif
   {
      T("general"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serial"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL, 	   /* queryFunc */
      0,                   /* last query */
      NULL,	   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("baudRate"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.baudRate), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataSize"),	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.dataSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stopBits"),  /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.stopBits), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("parity"),  	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.parity), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("flowControl"),    /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,   	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.flowControl), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dcdState"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.serial.dcdState), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serial"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("access"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,      	   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("users"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.access.users), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authType"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.access.authtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef BIDIRECT
   {
      T("lgtimeout"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.access.lgtimeout), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("termsh"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.access.termsh), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("access"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataBuf"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL, 	   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("destType"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.destType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fileSize"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.fileSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nfsFile"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.nfsFile), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("timeStamp"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.timeStamp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("showMenu"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,         /* getFunc */
      dmfSetUInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.showMenu), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   { //[RK]Feb/16/06
      T("allTime"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.allTime), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   //[AP][2007-07-30] hostname discovery
   {
      T("ADEnable"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.ADEnable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ADTimeOut"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dataBuf.ADTimeOut), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataBuf"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysBuf"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,      	   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enable"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.sysBuf.enable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("facility"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.sysBuf.facility), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bufferSize"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.sysBuf.bufferSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("allTime"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.sysBuf.allTime), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.sysBufServer.SyslogBufServer),     /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysBuf"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mus"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,      	   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("multSess"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.mus.multSess), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sniffMode"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.mus.sniffMode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("adminUsers"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.mus.adminUsers),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hotKey"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.mus.hotKey),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHotKeyLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifyUsers"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.mus.notifyUsers), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mus"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(PMD) || defined(IPMI)
   {
      T("powerMgm"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetPhysPmOutletHtml, /* queryFunc */
      0,                   /* last query */
      NULL,				   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef IPMI
   {
      T("enableIPMI"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.enableIPMI), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipmiKey"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.ipmiKey),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHotKeyLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipmiDeviceId"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.ipmiDeviceId), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipmiDeviceListHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,    /* getFunc */
      NULL,   		  /* setFunc */
      NULL,    /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.ipmiDeviceListHtml),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,   		/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif // IPMI
#ifdef PMD
   {
      T("enable"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.enable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmKey"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.pmKey),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHotKeyLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmOutlets"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.outletList),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmOutletsStringLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("allUsers"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.allUsers), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("userList"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.powerMgm.userList),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmPortUserListLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("powerMgm"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("other"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,      	   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portIpAlias"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.portIpAlias),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef IPv6enable
   {
      T("portIp6Alias"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.portIp6Alias),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef WINEMSenable
   {
      T("winEms"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.winEms), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("authBio"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.authBio), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tcpKeepAlive"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.tcpKeepAlive), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tcpIdleTmo"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.cas.tcpIdleTmo), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("host"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.ts.host),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("terminalType"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.ts.terminalType),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTermTypeLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("initChat"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dialIn.initChat),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInitChatLength,   /* upperLimit */ //[RK]Feb/02/07
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pppOpt"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.dialIn.pppOpt),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kAutoPPPLength,   /* upperLimit */ //[RK]Feb/02/07
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("socketPort"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.socketPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stty"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.stty),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSttyCommandLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("loginBanner"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.loginBanner),      /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("breakInterval"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.breakInterval), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("breakSequence"), 	   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.breakSequence), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kBreakSeqLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SSHexit"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.SSHexit), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHotKeyLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sconf"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.physP.infoP.other.sconf), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHotKeyLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("other"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("physP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   {
      T("virtualP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetVirtualPortsInfo,         /* queryFunc */
      0,                   /* last query */
      VirtualPortsInfoCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("virtualInfoHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("virtualInfoSet"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualInfoSet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nports"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.nports), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("remoteIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.remoteIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("virtualPort"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetVirtualPort,         /* queryFunc */
      0,                   /* last query */
      SetVirtualPort,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("remoteIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.remoteIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("clusteringIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.clusteringIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numOfPorts"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.numOfPorts), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("localPort"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.firstLocalPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("localTcpPort"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.localTcpPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("remoteTcpPort"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.firstRemoteTcpPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocol"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.protocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("name"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.virtualP.virtualPort.name), /* dataStart */
      kHostNameLength,     /* offset */
      &kZeroIndex,                /* startIndex */
      &(gCache.virtualP.nports),                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("virtualPort"),          /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("virtualP"),          /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ports"),          /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
     EXPERT->APPLICATIONS  
   --------------------------------------------------------------------------*/
   {
      T("applications"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->APPLICATIONS->POWER MANAGEMENT
   --------------------------------------------------------------------------*/
#ifdef PMDNG
   /*--------------------------------------------------------------------------
     New PM Outlets Manager
   --------------------------------------------------------------------------*/
   {
      T("IpduOutMan"),     /* key  OK */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpduOutMan,       /* queryFunc */
      0,                   /* last query */
      IpduOutManCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numPorts"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.numPorts), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpdus"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.portInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.ipduInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outletInfoHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.outletInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outcapInfoHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.outcapInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("showIpdu"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.showIpdu), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduName_str"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.ipduName_str), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPMDipduIDLength+kPmStringLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduModel_str"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.ipduModel_str), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmModelLength+kPmVendorLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("isServerTech"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.isServerTech), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduNofOut"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.ipduNofOut), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memSignature"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutMan.memSignature), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("IpduOutMan"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PM Outlet Groups Ctrl
   --------------------------------------------------------------------------*/
   {
      T("IpduOutGrpCtrl"), /* key  OK */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpduOutGrpCtrl,   /* queryFunc */
      0,                   /* last query */
      IpduOutGrpCtrlCommit,/* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpdus"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numGroups"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.numGroups), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupInfoHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.groupInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outletInfoHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.outletInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memSignature"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduOutGrpCtrl.memSignature), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("IpduOutGrpCtlr"), /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PM View IPDUs Info
   --------------------------------------------------------------------------*/
   {
      T("ViewIpduInfo"),   /* key  OK */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetViewIpduInfo,     /* queryFunc */
      0,                   /* last query */
      ViewIpduInfoCommit,  /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpdus"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.ipduInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("confcapHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.confcapHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memSignature"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.memSignature), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ViewIpduInfo"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PM Configuration
   --------------------------------------------------------------------------*/
   {
      T("IpduConfig"),     /* key OK */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpduConfig,       /* queryFunc */
      0,                   /* last query */
      IpduConfigCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpdus"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipduInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.ipduInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("confcapHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.confcapHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memSignature"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ViewConfIpdu.memSignature), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("IpduConfig"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PM Software Upgrade
   --------------------------------------------------------------------------*/
   {
      T("IpduSwUpgrade"),  /* key OK */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpduSwUpgrade,    /* queryFunc */
      0,                   /* last query */
      IpduSwUpgradeCommit, /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpdus"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.numIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nValidIpdus"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.nValidIpdus), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("swupInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.swupInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("latest_sw"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.latest_sw), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmModelLength,	   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memSignature"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.IpduSwUpgrade.memSignature), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("IpduSwUpgrade"),  /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PMD Config, General tab
   --------------------------------------------------------------------------*/
   {
      T("pmdGen"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetpmdGen,           /* queryFunc */
      0,                   /* last query */
      pmdGenCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numVendors"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdGen.numVendors), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("confInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdGen.confInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdGen.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmdGen"),         /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PMD Config, Outlet Groups tab
   --------------------------------------------------------------------------*/
   {
      T("pmdOutGrp"),      /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetpmdOutGrp,        /* queryFunc */
      0,                   /* last query */
      pmdOutGrpCommit,     /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupsListHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.groupsListHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("entries"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.entries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPMUserManTableEntriesLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("singleGroup"),    /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetpmdOutGrpEntry,   /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("groupName"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.singleGroup.group), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outlets"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.singleGroup.outletList), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmOutletsStringLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdOutGrp.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("singleGroup"),    /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmdOutGrp"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     New PMD Config, Users Management tab
   --------------------------------------------------------------------------*/
   {
      T("pmdUserMan"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetpmdUserMan,       /* queryFunc */
      0,                   /* last query */
      pmdUserManCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("usersListHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.usersListHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("entries"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.entries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPMUserManTableEntriesLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("singleUser"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetpmdUserManEntry,  /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("userName"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.singleUser.user), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outlets"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.singleUser.outletList), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPmOutletsStringLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmdUserMan.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("singleUser"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmdUserMan"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef IPMI
   /*--------------------------------------------------------------------------
     PM IPDU
   --------------------------------------------------------------------------*/
   {
      T("pmIpmi"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetPmIpmi,           /* queryFunc */
      0,                   /* last query */
      PmIpmiCommit,        /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numIpmiDev"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmipmi.numIpmiDev), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipmiInfoHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmipmi.ipmiInfoHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmipmi.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmipmi.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numActiveIpmiDev"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.pmipmi.numActiveIpmiDev), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmIpmi"),         /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif

   /*--------------------------------------------------------------------------
     EXPERT->APPLICATIONS->CUSTOMIZED TERMINAL PROFILE MENU
   --------------------------------------------------------------------------*/
   {
      T("menuShell"),      /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetMenuShellInfo,    /* get unit infoqueryFunc */
      0,                   /* last query */
      MenuShellCommit,     /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selectedOption"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.selectedOption), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numOptions"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.menuShInfo.numOptions), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("optionsCs"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.optionsCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHtmlListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("menuOptionHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.menuOptionHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },                
   {
      T("menuTitle"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.menuShInfo.menuTitle), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTitleLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("addModOption"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetMenuShAddModOption,  /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("title"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.addModOption.title), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTitleLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("command"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.menuShell.addModOption.command), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCommandLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("addModOption"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("menuShell"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("applications"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION 
   --------------------------------------------------------------------------*/
   {
      T("administration"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->SYSTEM(UNIT) INFO
     EXPERT->ADMINISTRATION->REBOOT
   --------------------------------------------------------------------------*/
   {
      T("unitInfo"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetUnitInfo,         /* get unit infoqueryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("reboot"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      RebootCommit,        /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.reboot), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("macAddress"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.mac_address), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kMacAddressLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("versionHtml"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      //GetUnitVersionInfo,      /* queryFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.versionHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("date"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.date), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDateLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("upTime"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.upTime), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUpTimeLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pwrSupplyHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      //GetUnitPwrSupplyInfo,      /* queryFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.pwrSupplyHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serialNumberHtml"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.serialNumber), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      30,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(KVM) || defined(ONS)
   {
      T("kvmPortStatus"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      GetUnitKVMPortStatus,      /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      gCache.unitInfo.kvmPortStatus, /* dataStart */
      sizeof(char_t *),        /* offset */
      &kZeroIndex,                /* startIndex */
      &(gCache.unitInfo.numkvmstations),                /* endIndex */
      0,                   /* lowerLimit */
      kKVMPortInfoLength,  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fanStatus"),  /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      NULL,                /* setFunc */
      NULL,      /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.fanStatus[0]), /* dataStart */
      sizeof(int),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxFanIndex,                /* endIndex */
      0,                   /* lowerLimit */
      2,     		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("ramHtml"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetUnitRamDiskInfo,  /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.ramHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cpuInfo"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      //GetUnitCpuInfo,    	 /* queryFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("processor"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.processor), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cpu"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.cpu), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCpuLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("clock"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.clock), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kClockLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("busClock"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.busClock), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kClockLength,        /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("revision"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.revision), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRevisionLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("zeroPages"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.zeroPages), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kZeroPagesLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bogomips"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.cpuInfo.bogomips), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kBogomipsLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cpuInfo"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    		         /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ifInfo"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      //GetUnitCpuInfo,    	 /* queryFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("allif"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.ifInfo.allif), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      64*(kHostNameLength+1), /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ifInfo"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    		         /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("memHtml"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      //GetUnitMemInfo,      /* queryFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.memHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,  		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef PCMCIA
   {
      T("pcmciaHtml"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      GetUnitPcmciaInfo,   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.unitInfo.pcmciaHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("unitInfo"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->BOOT INFO
   --------------------------------------------------------------------------*/
   {
      T("bootInfo"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetUnitBootConfInfo, /* queryFunc */
      0,                   /* last query */
      BootConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uBootHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.uBootHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("ipAddr"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.ipAddr), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("wdTimer"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.wdTimer), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uBoot"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.uBoot), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bType"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.bType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bootFilename"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.bootFilename), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kBootPathLength+1,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serverIpAddr"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.serverIpAddr), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("speed"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.speed), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("flashTest"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.flashTest), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ramTest"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.ramTest), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fastEthernet"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.fastEthernet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("maxEvent"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.bootInfo.maxEvent), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bootInfo"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->UPGRADE FIRMWARE
   --------------------------------------------------------------------------*/
   {
      T("upGradeInfo"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL, 							 /* queryFunc */
      0,                   /* last query */
      UpgradeCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ftpSite"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.ftpSite),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("userName"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.userName),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("passWd"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.passWd),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("filePathName"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.filePathName),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPathFilenameLength,   /* upperLimit */ //[RK]Sep/13/04 - increase the size from 50 to 100
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("checkSum"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.checkSum), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.upGradeInfo.sysMsg),  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("upGradeInfo"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->TIME/DATE
   --------------------------------------------------------------------------*/
   {
      T("timeDate"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetTimeDate,         /* queryFunc */
      0,                   /* last query */
      TimeDateCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ntp"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.ntp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ntpServer"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.ntpServer), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */ //[RK]Sep/17/04 - accept hostname
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("timezone"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.timezone), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTimezoneLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("month"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.month), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("day"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.day), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("year"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.year), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hour"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.hour), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("minute"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.min), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("second"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.sec), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tzacronym"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.dt.tzacronym), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTzAcronymLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("zlabel"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.zlabel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTzLabelLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("acronym"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.acronym), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTzAcronymLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("GMToffHours"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,         /* getFunc */
      dmfSetInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.GMToff.hour), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("GMToffMinutes"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.GMToff.min), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTactive"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTactive), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTacronym"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTacronym), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTzAcronymLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTsaveHours"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,         /* getFunc */
      dmfSetInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTsave.hour), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTsaveMinutes"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTsave.min), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTstartMonth"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTstartDate.month), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTstartWeek"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTstartDate.week), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTstartDay"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTstartDate.day), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTstartHour"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,         /* getFunc */
      dmfSetInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTstartTime.hour), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTstartMin"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTstartTime.min), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTendMonth"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTendDate.month), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTendWeek"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTendDate.week), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTendDay"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTendDate.day), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTendHour"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,         /* getFunc */
      dmfSetInt32,         /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTendTime.hour), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("DSTendMin"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.timeDate.tz.DSTendTime.min), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("timeDate"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->NOTIFICATIONS
   --------------------------------------------------------------------------*/
   {
      T("notifications"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetNotifications,    /* queryFunc */
      0,                   /* last query */
      NotificationsCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("alarm"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.alarm), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.notifHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifTable"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.notifTable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("triggerId"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        	  /* getFunc */
      dmfSetInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.triggerId), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifType"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,        /* getFunc */
      dmfSetInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.notifType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->NOTIFICATIONS -- Add/Mod Event Notif
   --------------------------------------------------------------------------*/
   {
      T("eventsNotif"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetEventsNotif,    /* queryFunc */
      0,                   /* last query */
      SetEventsNotif,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifType"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetInt32,        /* getFunc */
      NULL,        	   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.notifType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("trigger"), /* key */
      kString,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.trigger), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTriggerLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("triggerHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.triggerHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->NOTIFICATIONS -- Add/Mod Event Notif EMAIL
   --------------------------------------------------------------------------*/
   {
      T("email"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    		   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("toAddress"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.toAddress), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kEmailListLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fromAddress"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.fromAddress), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kEmailListLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("subject"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.subject), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kEmailSubjectLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("body"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.body), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kEmailBodyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serverIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.serverIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,           /* upperLimit */ //[RK]Sep/17/04 - accept host name
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serverPort"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.email.serverPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("email"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->NOTIFICATIONS -- Add/Mod Event Notif PAGER
   --------------------------------------------------------------------------*/
   {
      T("pager"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    		   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("phoneNum"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.pager.phoneNum), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPhoneNumLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("text"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.pager.text), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPagerTextLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("smsUserName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.pager.smsUserName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("smsServerIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.pager.smsServerIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,           /* upperLimit */ //[RK]Sep/17/04 - accept host name
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("smsPort"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.pager.smsPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pager"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->NOTIFICATIONS -- Add/Mod Event Notif SNMPTRAP
   --------------------------------------------------------------------------*/
   {
      T("snmpTrap"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    		   /* queryFunc */
      0,                   /* last query */
      NULL,		   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("trapNumber"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.snmptrap.trapNumber), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("community"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.snmptrap.community), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCommunityLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("serverIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.snmptrap.serverIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,           /* upperLimit */ //[RK]Sep/17/04 - accept host name
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("oid"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.snmptrap.oid), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kOidLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("body"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.notifications.event.snmptrap.body), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSnmpTrapBodyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("snmpTrap"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("eventsNotif"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("notifications"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("backupConfig"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      backupConfigCommit,  /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("Message"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtrClear,        /* getFunc */
      NULL,                /* setFunc */
      NULL,  /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.Message), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("Password"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.Password), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("UserName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.UserName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("PathName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.PathName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPathFilenameLength, /* upperLimit */ //[RK]Sep/13/04 - increase size from 50 to 100
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ServerName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.ServerName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("bkptype"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.bkptype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSDoption, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SDDefaultoption"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.SDDefaultoption), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSDoption, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SDReplaceoption"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.SDReplaceoption), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSDoption, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("command"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.backupConfig.command), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kFtpCmdLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("backupConfig"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->ADMINISTRATION->ONLINE HELP
   --------------------------------------------------------------------------*/
   {
      T("onlineHelp"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetOnlineHelpConf,   /* queryFunc */
      0,                   /* last query */
      OnlineHelpCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("path"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.onlineHelp.path), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kOnlineHelpPathLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("onlineHelp"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("administration"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   /*--------------------------------------------------------------------------
     EXPERT->NETWORK 
   --------------------------------------------------------------------------*/
   {
      T("network"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->NETWORK->SNMP DAEMON SETTINGS
   --------------------------------------------------------------------------*/
   {
      T("SNMPdaemon"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSNMPdaemon,       /* queryFunc */
      0,                   /* last query */
      SNMPdaemonCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysContact"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.sysContact), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,	       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysLocation"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.sysLocation), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,	       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("webMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.webMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      20,                  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv12Html"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12Html), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv12Entries"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12Entries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSNMPdaemonListLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv12"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSNMPv12Entry,     /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("communityName"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12.communityName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCommunityLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("source"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12.source), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCommunitySourceLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("oid"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12.oid), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kOidLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("permission"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv12.permission), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv12"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv3Html"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3Html), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv3Entries"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3Entries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSNMPdaemonListLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv3"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSNMPv3Entry,      /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("userName"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3.userName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("password"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3.password), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("permission"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3.permission), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("oid"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.SNMPdaemon.SNMPv3.oid), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kOidLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPv3"),         /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("SNMPdaemon"),     /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
  /*--------------------------------------------------------------------------
     EXPERT->NETWORK->HOST TABLE
   --------------------------------------------------------------------------*/
   {
      T("hostTable"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetHostTable,    /* queryFunc */
      0,                   /* last query */
      HostTableCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostTableHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.hostTable.hostTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numHosts"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.hostTable.numHostsSet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostTableSet"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.hostTable.hostTableSet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostTable"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef IPSEC
   /*--------------------------------------------------------------------------
     EXPERT->NETWORK->VPN
   --------------------------------------------------------------------------*/
   {
      T("VPNTable"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetVPNTable,    /* queryFunc */
      0,                   /* last query */
      VPNTableCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("VPNTableHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNTable.VPNTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("VPNTableDel"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNTable.VPNTableDel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("pubRsaKey"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNTable.pubRsaKey), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRsaKeyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("VPNTable"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	//---------------------------------------------------------------------
	{
      T("VPNEntry"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetVPNEntry,    /* queryFunc */
      0,                   /* last query */
      VPNEntryCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("VPNTableDel"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNTable.VPNTableDel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("connectionName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.connectionName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kFileNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authMethod"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.aMethod), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("authProtocol"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.aProtocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("idRht"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.rightId), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("ipAddressRht"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.rightIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("subnetMaskRht"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.rightSubnet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSubnetLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("nextHopRht"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.rightNextHop), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("rsaKeyRht"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.rightRsaKey), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRsaKeyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("idLft"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.leftId), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("ipAddressLft"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.leftIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("subnetMaskLft"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.leftSubnet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSubnetLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("nextHopLft"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.leftNextHop), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("rsaKeyLft"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.leftRsaKey), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRsaKeyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("bootAction"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.bAction), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kSnmpTrapBodyLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("sharedSecret"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.VPNEntry.secret), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength, /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("VPNEntry"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   /*--------------------------------------------------------------------------
     EXPERT->NETWORK->STATIC ROUTES
   --------------------------------------------------------------------------*/
   {
      T("staticRoutes"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetStaticRoutes,     /* queryFunc */
      0,                   /* last query */
      StaticRoutesCommit,  /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stRoutesHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.stRoutesHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("entriesList"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.entriesList), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kStRoutesEntriesListLength,/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stRoute"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetStaticRouteEntry, /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("routeType"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.routeType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("destinationIp"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.destinationIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("destinationMask"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.destinationMask), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("goTo"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.goTo), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("gateWay"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.gateWay), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("routeInterface"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.routeInterface), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("metric"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.metric), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.staticRoutes.route.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stRoute"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("staticRoutes"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->NETWORK->IP TABLES
   --------------------------------------------------------------------------*/
   {
      T("ipTables"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,         	   /* queryFunc */
      0,                   /* last query */
      NULL,       /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipTableHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetIpTableChainsHtml,    /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.ipTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		               /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chain"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,    /* queryFunc */
      0,                   /* last query */
      IpTableChainsCommit,       /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numChains"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.numChains), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chainsCs"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.chainsCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chainSelected"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.chainSelected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chain"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rules"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpTableRules,    /* queryFunc */
      0,                   /* last query */
      IpTableRulesCommit,       /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chainName"),/* key */
      kString,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.chainName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kChainNameLength,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef IPv6enable
   {
      T("chainType"),/* key */
      kString,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.chainType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kChainTypeLength,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("rulesTableHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,     	   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rulesHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		               /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rulesCs"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rulesCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("actionRule"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.actionRule), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numRules"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.numRules), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ruleSelected"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.ruleSelected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rules"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ruleSpec"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetIpTableRuleSpec,  /* queryFunc */
      0,                   /* last query */
      NULL,  /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("chainName"),/* key */
      kString,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.chainName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kChainNameLength,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ruleSelected"),/* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.ruleSelected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("targetHtml"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.targetHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("target"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.target), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTargetLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sIp"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.sourceIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sIpMask"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.sourceIpMask), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sIpInvert"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.sourceIpInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dIp"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.destinationIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dIpMask"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.destinationIpMask), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dIpInvert"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.destinationIpInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocol"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.protocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocolNumber"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.protocolNumber), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocolInvert"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.protocolInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("inInterface"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.inInterface), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInterfaceNameLength,/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("inInterfaceInvert"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.inInterfaceInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outInterface"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.outInterface), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInterfaceNameLength,/* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outInterfaceInvert"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.outInterfaceInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("fragment"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.fragment), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
	{
      T("sPort"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.SourcePort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("LastSPort"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.LastSourcePort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sPortInvert"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.SourcePortInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dPort"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.DestinationPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("LastDPort"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */ 
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.LastDestinationPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   }, 
   {
      T("dPortInvert"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.DestinationPortInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("TcpFlags"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.TcpFlags), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("TcpFlagsSet"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.TcpFlagsSet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("TcpFlagsInvert"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.TcpFlagsInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ICMPType"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.ICMPType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kICMPTypeLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ICMPTypeInvert"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.ICMPTypeInvert), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("LogLevel"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.LogLevel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("LogPrefix"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.LogPrefix), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kLogPrefixLength,    /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("LogTcpOptions"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.LogTcpOptions), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("RejectWith"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.ipTable.rule.RejectWith), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRejectWithLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ruleSpec"),   /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipTables"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->NETWORK->ACCESS METHOD
   --------------------------------------------------------------------------*/
#ifdef PCMCIA
   {
      T("accessMethod"),   /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetAccessMethodInfo, /* queryFunc */
      0,                   /* last query */
      AccessMethodCommit,  /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selectedOption"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.selectedOption), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ident"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.ident), /* dataStart */
      kIdentLength,       /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kIdentLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
//------- Modem/GSM/CDMA ---------------------------------
   { //[RK]Nov/10/06
      T("version2"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.version2), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("modemPPP"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.ppp), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pin"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.pin), /* dataStart */
      kPinLength,          /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kPinLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("modemGsmLocalIp"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.localIp), /* dataStart */
      kIpLength,           /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("modemGsmRemoteIp"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.remoteIp), /* dataStart */
      kIpLength,           /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("callback"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.callBack), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("callbackNum"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.callBackNum), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPhoneNumLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("speed"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.speed), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("addinit"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.addinit),       /* dataStart */
      kAddinitLength,      /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kAddinitLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("modemCardtype"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.modemCardtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef OTPenable
   { //[RK]Jan/20/06
      T("OTP"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.modemGsm.otp), /* dataStart */
      0,         	   /* offset */
      NULL,         	   /* startIndex */
      NULL,		   /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
//------- ISDN ---------------------------------
   {
      T("isdnLocalIp"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.isdn.localIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("isdnRemoteIp"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.isdn.remoteIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("isdnCallback"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.isdn.callBack), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("isdnCallbackNum"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.isdn.callBackNum), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPhoneNumLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
//------- Ethernet ---------------------------------
   {
      T("ethIpAddr"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.netWkConfig.ipAddr), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ethNetMask"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.netWkConfig.netMask), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kIpLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
//------- Compact Flash ---------------------------------
   {
      T("cfEnable"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.flash.enable), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cfDataBuf"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.flash.dataBuf), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
//------- Wirless ---------------------------------
   {
      T("key"),            /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.wireless.key), /* dataStart */
      kListLength,         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("essid"),          /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.wireless.essid), /* dataStart */
      kNetworkNameLength,  /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      kNetworkNameLength,  /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("channel"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.wireless.channel), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("encryption"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.accessMethod.pcmType.wireless.encryption), /* dataStart */
      sizeof(int),         /* offset */
      &kZeroIndex,         /* startIndex */
      &(gCache.unitInfo.numPcmcia),  /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("accessMethod"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("network"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->SECURITY
   --------------------------------------------------------------------------*/
   {
      T("security"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   /*--------------------------------------------------------------------------
     EXPERT->SECURITY->ACTIVE PORT SESSIONS
   --------------------------------------------------------------------------*/
   {
      T("session"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      ActiveSessionCommit, /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selectedOption"), /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.session.selectedOption), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.session.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numSessions"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetActiveSessions,   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.session.totalSessions), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sessionHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.session.sessionHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		            /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("session"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authtypeP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetAuthType,        /* queryFunc */
      0,                   /* last query */
      AuthTypeCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("unitauthtype"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.unitauthtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pppauthtype"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.pppauthtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authtypeP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetRadiusConf,        /* queryFunc */
      0,                   /* last query */
      RadiusConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusAuthServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.authServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusAccServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.accServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusAuth2Server"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.auth2Server),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusAcc2Server"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.acc2Server),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusSecret"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.secret),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusTimeout"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.timeout), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusRetries"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.retries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusServiceType"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.radius.serviceType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("radiusP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacplusP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetTacplusConf,        /* queryFunc */
      0,                   /* last query */
      TacplusConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacAuthServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.authServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacAccServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.accServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacAuth2Server"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.auth2Server),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacAcc2Server"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.acc2Server),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacSecret"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.secret),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacRaccess"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.raccess), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacTimeout"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.timeout), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacRetries"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.tacplus.retries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("tacplusP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetLdapConf,        /* queryFunc */
      0,                   /* last query */
      LdapConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapBase"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapBase),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kLdapDomainNameLength,   /* upperLimit */ //[RK]Aug/12/05 - increased the length
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapsecure"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.secure), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapUser"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapUser),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kLdapDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapPassword"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapPassword),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapLoginAttribute"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapLoginAttribute),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef KRBenable
   {
      T("kerberosP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKrbConf,        /* queryFunc */
      0,                   /* last query */
      KrbConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("krbServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.krb.krbServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("krbDomainName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.krb.krbDomainName),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("kerberosP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef SMBenable
   {
      T("smbP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSmbConf,        /* queryFunc */
      0,                   /* last query */
      SmbConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authdomain"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.smb.domain), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authserver1"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.smb.server), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authserver2"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.smb.server2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("smbP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef NISenable
   {
      T("nisP"),          /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetNisConf,        /* queryFunc */
      0,                   /* last query */
      NisConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nisDomainName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.nis.domainName),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nisServerIp"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.nis.serverIp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("nisP"),      /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   /*--------------------------------------------------------------------------
     EXPERT->SECURITY->SECURITY PROFILE
   --------------------------------------------------------------------------*/
   {
      T("profile"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetSecProfile,       /* queryFunc */
      0,                   /* last query */
      SecProfileCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("mode"), 	       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.mode), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("telnet"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.telnet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sshv1"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ssh.sshv1), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sshv2"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ssh.sshv2), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef SECPROFILE
   {
      T("sshPort"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ssh.port), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("sshRoot"),        /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ssh.rootAccess), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("http"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.http), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("https"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.https), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef SECPROFILE
   {
      T("httpPort"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.http_port), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("httpsPort"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.https_port), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("http2https"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.redirect), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ssl"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.webUI.ssl_version), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("snmp"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.snmp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rpc"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.rpc), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef KRBenable
   {
      T("ftp"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ftp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef ONS
   {
      T("tftp"),            /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.tftp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
#ifdef IPSEC
   {
      T("ipsec"),          /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.ipsec), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("icmp"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.icmp), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef SECPROFILE
   {
      T("type"),           /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.profile), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("ssh2sport"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.ssh2sport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("telnet2sport"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.telnet2sport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("raw2sport"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.raw2sport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("auth2sport"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.auth2sport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef BIDIRECT
   {
      T("bidirect"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.bidirect), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("showWarning"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.showWarning), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("directaccess"),   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.secProfile.options.directaccess), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("profile"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
 
   {
      T("security"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined(KVM) || defined(ONS)
   {
      T("kvm"),               /* key */
      kBeginSection,             /* dataType */
      0,                  /* read access level */
      0,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL, //GetKVMConf,      /* queryFunc */ /* set to NULL later */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("maxports"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetDevice,            /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &gCache.unitInfo.maxkvmports,  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numstations"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetDevice,            /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &gCache.unitInfo.numkvmstations,  /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("KVMconnectPortsHtml"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetKVMConnectPortsHtml, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &gCache.KVMconnectPortsHtml, /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("conf"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("general"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDConf,         /* queryFunc */
      0,                   /* lastQuery */
      KVMDConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authtype"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.authtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if 0
   {
      T("authdownlocal"),  /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.authdownlocal), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("directacc"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetKVMDirectAccConf, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.directacc), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("escapeseq"),               /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.escapeseq), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sunmodifier"),               /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.sunmodifier), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if 0
   {
      T("authserver1"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.authServer), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("accserver1"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.accServer), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authserver2"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.auth2Server), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("accserver2"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.acc2Server), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("secret"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.secret), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authdomain"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.domain), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kServerLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("timeout"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.timeout), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("retries"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.radius.retries), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapBase"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapBase),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kLdapDomainNameLength,   /* upperLimit */ //[MP]Dec/01/05 - increased the length
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapsecure"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.secure), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapUser"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapUser),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kLdapDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapPassword"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapPassword),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ldapLoginAttribute"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.ldap.ldapLoginAttribute),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("krbServer"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.krb.krbServer),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("krbDomainName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.authU.krb.krbDomainName),       /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDomainNameLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("general"),               /* key */
      kEndSection,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("station"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDConf,         /* queryFunc */
      0,                   /* lastQuery */
      KVMDConfCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("idletimeout"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].idletimeout), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("screensavertime"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].screensavertime), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cycletime"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].cycletime), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("kbdtype"),         /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].kbdtype), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("quitseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].quitseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("powerseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].powerseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("srvsyncseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].srvsyncseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("videoconfseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].videoconfseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("switchnextseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].switchnextseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("switchprevseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].switchprevseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portinfoseq"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.stations[0].portinfoseq), /* dataStart */
      sizeof(KVMStationConfig),/* offset */
      &gCache.unitInfo.kvmanalog, /* startIndex */
      &gCache.unitInfo.numkvmstations_1, /* endIndex */
      0,                   /* lowerLimit */
      kKeySeqLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("viewerport"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.viewerport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kViewerPortLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipsecurity"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.ipsecurity), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("des"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmconf.kvmd.general.des), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("station"),        /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("acclist"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMAccList,       /* queryFunc */
      0,                   /* lastQuery */
      KVMAccListCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("KVMPermHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.KVMPermHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("KVMDefPermHtml"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,         /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.KVMDefPermHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("currname"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.currName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("entryname"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      KVMUserCommit,       /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.entryName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("currusergroup"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.currUserGroup), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("currdefault"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.currDefault), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cancel"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.cancel), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("user"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0, 		   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("name"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.userperm.name), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("usergroup"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.userperm.usergroup), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("defperm"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.userperm.defperm), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("user"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("default"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("defperm"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.useracc.defuserperm.defperm), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("default"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDevicePermissions, /* queryFunc */
      0,                   /* lastQuery */
      KVMDevicePermissionsCommit,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("currdevice"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.currDevice), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCascNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numports"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.numports), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("defperm"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.userperm.defperm), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsnone"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.ports_none), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortRangeLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsro"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.ports_ro), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortRangeLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsrw"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.ports_rw), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortRangeLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsfull"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuser.ports_full), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPortRangeLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),           /* key */
      kEndSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("acclist"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDevice,        /* queryFunc */
      0,                   /* lastQuery */
      KVMDeviceCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceMsgError"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceMsgError), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceTableHtml"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numDevices"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.numDevices), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceTable"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,        /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceTable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("outletsHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetKVMDeviceOutlets, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.outletsHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,    		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsUsedHtml"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.portsUsedHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,		           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceCs"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceAction), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceSel"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceSelected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("maxOutlet"),      /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetMaxOutlet,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.maxOutlet), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceConf"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDeviceSel,     /* queryFunc */
      0,                   /* lastQuery */
      NULL,     	 /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("name"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.name), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCascNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numTerms"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.numTerms), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("connectionType"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.connectionType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("hostName"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.hostName), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.device), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kCascNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("connectTerms"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confDevice.connectTerms), /* dataStart */
      sizeof(UInt32),      /* offset */
      &kZeroIndex,                /* startIndex */
      &kDoisIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceConf"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("term"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDeviceTerm,         /* queryFunc */
      0,                   /* lastQuery */
      KVMDeviceTermCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceMsgError"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceMsgError), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("termTableHtml"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,        	   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.termTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("selected"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,        	   /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.selected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmoutletHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.pmoutletHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,               /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("termSel"),           /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMDeviceTermSel, /* queryFunc */
      0,                   /* lastQuery */
      0,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceNameList"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceNameList), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceNTermsList"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.deviceNTermsList), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("alias"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      GetKVMDeviceTermSel, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.alias), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("lockoutmacro"),               /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.lockoutmacro), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kKeyLogoutLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   {
      T("pmdevice"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.pmdevice), /* dataStart */
      kCascNameLength,     /* offset */
      &kZeroIndex,                /* startIndex */
      &kDoisIndex,                /* endIndex */
      0,                   /* lowerLimit */
      kCascNameLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmoutlet"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.pmoutlet), /* dataStart */
      sizeof(UInt32),      /* offset */
      &kZeroIndex,                /* startIndex */
      &kDoisIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("pmoutletstr"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.pmoutletstr), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kListLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#ifdef KVMTCPport
   {
      T("tcpport"),    /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmdevice.confTerm.tcpport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      1,                   /* lowerLimit */
      0xffff,              /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("termSel"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("term"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if defined ONS || defined KVMNETP
   {
      T("auxPort"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMauxPort,       /* queryFunc */
      0,                   /* lastQuery */
      KVMauxPortCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enable"),	   /* key */
      kInteger,		   /* dataType */
      -1,		   /* read access level */
      -1,		   /* write access level */
      dmfGetUInt32,	   /* getFunc */
      dmfSetUInt32,	   /* setFunc */
      NULL,		   /* queryFunc */
      0,		   /* lastQuery */
      NULL,		   /* commitFunc */
      0,		   /* last commit */
      &(gCache.kvmAuxPort[0].enable),/* dataStart */
      sizeof(KVMAuxPort),  /* offset */
      &kZeroIndex,	   /* startIndex */
      &kMaxAuxIndex,	   /* endIndex */
      0,		   /* lowerLimit */
      0,		   /* upperLimit */
      -1,		   /* parent -- keep this -1 */
   },
   {
      T("pidx"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].idx), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("protocol"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].protocol), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("baudRate"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].baudRate), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("dataSize"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].dataSize), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stopBits"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].stopBits), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("parity"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].parity), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("flowControl"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].flowControl), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("initChat"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].initChat), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      kInitChatLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("autoPPP"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].autoPPP), /* dataStart */
      sizeof(KVMAuxPort),                   /* offset */
      &kZeroIndex,                /* startIndex */
      &kMaxAuxIndex,                /* endIndex */
      0,                   /* lowerLimit */
      kAutoPPPLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("auxPort"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#else
   {
      T("auxPort"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMauxPort,       /* queryFunc */
      0,                   /* lastQuery */
      KVMauxPortCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("enable"),	   /* key */
      kInteger,		   /* dataType */
      -1,		   /* read access level */
      -1,		   /* write access level */
      dmfGetUInt32,	   /* getFunc */
      dmfSetUInt32,	   /* setFunc */
      NULL,		   /* queryFunc */
      0,		   /* lastQuery */
      NULL,		   /* commitFunc */
      0,		   /* last commit */
      &(gCache.kvmAuxPort[0].enable),/* dataStart */
      0,			/* offset */
      NULL,			/* startIndex */
      NULL,			/* endIndex */
      0,		   /* lowerLimit */
      0,		   /* upperLimit */
      -1,		   /* parent -- keep this -1 */
   },
   {
      T("protocol"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].protocol), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("baudRate"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].baudRate), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },

   {
      T("dataSize"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].dataSize), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("stopBits"),       /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].stopBits), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("parity"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].parity), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("flowControl"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].flowControl), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("initChat"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].initChat), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInitChatLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("autoPPP"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmAuxPort[0].autoPPP), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kAutoPPPLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("auxPort"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("conf"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uCupdate"),       /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMuCupdate,      /* queryFunc */
      0,                   /* lastQuery */
      KVMuCupdateCommit,   /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsNameHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.portsNameHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("portsValHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.portsValHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cascNameHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.cascNameHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("cascValHtml"),  /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.cascValHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0, 		   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("targettype"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.targetType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("targetport"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.targetPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTargetPortLength*20,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ftpserver"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.ftpData.ftpserver), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kHostNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("username"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.ftpData.username), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kUserNameLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("password"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.ftpData.password), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,     /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("directory"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.ftpData.directory), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("filename"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.ftpData.filename), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kDirPathLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCup.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uCupdate"),       /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uCreset"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetKVMuCreset,       /* queryFunc */
      0,                   /* lastQuery */
      KVMuCresetCommit,    /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("targettype"),     /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCres.targetType), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("targetport"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCres.targetPort), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kTargetPortLength*20,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"),         /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCres.action), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("sysMsg"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmuCres.sysMsg), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,          /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("uCreset"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   
  /* These entries below are to be deleted later */ 
   {
      T("authtype"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmConf.authtype), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#if 0
   {
      T("facility"),               /* key */
      kInteger,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.kvmConf.facility), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
   {
      T("kvm"),               /* key */
      kEndSection,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif
//[RK]Jun/14/04 - Access Privilege
// Regular User - Security 
   {
      T("regUser"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* setFunc */
      NULL,   		   /* getFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      tablePageCommit,      /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("authLocal"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      GetRegUserAuthLocal,   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.regUser.authLocal), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("operResult"),    /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetUInt32,        /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,   /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.regUser.operResult), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("passwd"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      RegUserSecurityCommit, 	/* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("oldPasswd"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.regUser.oldPasswd), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("newPasswd"),   /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.regUser.newPasswd), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kPasswordLength,           /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("passwd"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("regUser"),        /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
/* -------------------------------------------------------------------------- */

#ifdef RDPenable
   /*--------------------------------------------------------------------------
     SYSTEM->RDP SESSIONS
   --------------------------------------------------------------------------*/
   {
      T("rdpconf"),        /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */ /* set to NULL later */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),         /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetRDPDevice,        /* queryFunc */
      0,                   /* lastQuery */
      RDPDeviceCommit,     /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceMsgError"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceMsgError), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kInfoLength,         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceTableHtml"), /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceTableHtml), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPListLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("numDevices"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.numDevices), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceTable"),    /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceTable), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPListLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceCs"),       /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceCs), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPListLength,      /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("action"), 	   /* key */
      kInteger,            /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceAction), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceSel"),      /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      dmfSetUInt32,        /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.deviceSelected), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rdpport"),     /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.rdpport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPPortLength,   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("RDPconnectKVMPorts"),/* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetStringPtr,     /* getFunc */
      NULL,                /* setFunc */
      GetRDPConnectKVMPorts, /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &gCache.rdpdevice.RDPconnectKVMPorts, /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,         	         /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceConf"),     /* key */
      kBeginSection,       /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      GetRDPDeviceSel,     /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("name"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.confDevice.name), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPGenLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("ipaddr"),         /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.confDevice.ipaddr), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPGenLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("srvport"),        /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.confDevice.srvport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPGenLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("kvmport"),           /* key */
      kString,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      dmfGetString,        /* getFunc */
      dmfSetStringFixed,   /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      &(gCache.rdpdevice.confDevice.kvmport), /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      kRDPGenLength,       /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("deviceConf"),     /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("device"),           /* key */
      kEndSection,         /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
   {
      T("rdpconf"),               /* key */
      kEndSection,             /* dataType */
      -1,                  /* read access level */
      -1,                  /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* lastQuery */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
#endif	//RDPenable

   {
      T("system"),         /* key */
      kEndSection,         /* dataType */
      0,                   /* read access level */
      0,                   /* write access level */
      NULL,                /* getFunc */
      NULL,                /* setFunc */
      NULL,                /* queryFunc */
      0,                   /* last query */
      NULL,                /* commitFunc */
      0,                   /* last commit */
      NULL,                /* dataStart */
      0,                   /* offset */
      NULL,                /* startIndex */
      NULL,                /* endIndex */
      0,                   /* lowerLimit */
      0,                   /* upperLimit */
      -1,                  /* parent -- keep this -1 */
   },
};

/* initialized and declared `extern'
extern int parameterCount = sizeof(parameterList) / sizeof(parameterList[0]);*/
int parameterCount = sizeof(parameterList) / sizeof(parameterList[0]);
