<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
  <title>General</title>
  <link rel="STYLESHEET" type="text/css" href="/stylesLayout.css">
   <script language="JavaScript" src="/scripts.js" type="text/javascript"></script>
   <script type="text/javascript"> 
   </script>
</head>

<% var sid=getQueryVal("SSID","0"); %>

<!-- frames -->
<frameset  rows="22,*" border="0" frameborder="0">
    <frame name="tabs" src="configKVMGeneralTab.asp?tab=gen&SSID=<%write(sid);%>" marginwidth="0" marginheight="0" scrolling="no" frameborder="0" noresize>
    <frame name="page" src="configKVMGeneralMod.asp?SSID=<%write(sid);%>;" marginwidth="0" marginheight="0" scrolling="auto" frameborder="0" noresize> 
</frameset>
</html>

