<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title></title>
<link rel="STYLESHEET" type="text/css" href="/stylesLayout.css">
<script language="JavaScript" src="/scripts.js" type="text/javascript"></script>
<script type="text/javascript">
	var ReqNum = <%write(getRequestNumber());%>;
	window.name = '<%get("system.device.ip");%>_<%get("_sid_");%>_' + ReqNum;
</script>
</head>
<frameset  rows="22,*" border="0" frameborder="0">
	<frame name="tabs" src="appsPMDconfUserManTab.asp?SSID=<%get('_sid_');%>" marginwidth="0"
		marginheight="0" scrolling="no" frameborder="0" noresize>
	<frame name="page" src="appsPMDconfUserManMod.asp?SSID=<%get('_sid_');%>" marginwidth="0"
		marginheight="0" scrolling="auto" frameborder="0" noresize>
</frameset>
</html>