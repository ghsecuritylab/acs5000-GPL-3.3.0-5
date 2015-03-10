
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>Untitled</title>
   <link rel="STYLESHEET" type="text/css" href="/stylesLayout.css">
   <script language="JavaScript" src="/scripts.js" type="text/javascript"></script>
   <script language="JavaScript" src="/menu.js" type="text/javascript"></script>
   <script language="JavaScript">

   function init()
   {
      parent.menuReady = 1;
   }

   var pageName = "/normal/information/infoMenu.asp";
   var topItem = "INF";
   var menuPages = new Array;
   var i = 0;

   menuPages[i++] = new menuObj("SYS", "General", "/normal/information/infoGeneral.asp");
   if (parent.family_model == "ONS")
     menuPages[i++] = new menuObj("KPS", "KVM User Status", "/normal/information/infoPortStatus.asp");
   else
     menuPages[i++] = new menuObj("KPS", "Station Status", "/normal/information/infoPortStatus.asp");

   if (parent.family_model == "ONS") {
     menuPages[i++] = new menuObj("ST", "Serial Ports Status", "/normal/ports/portsStatus.asp");
     menuPages[i++] = new menuObj("PS", "Serial Ports Statistics", "/normal/ports/portsStatistics.asp");
   }
 
   if (parent.family_ext == "KVMNETP" ) {
      menuPages[i++] = new menuObj("TEMP", "Temperature Sensor", "/normal/applications/appsTempSensor.asp");
   }

   </script> 

   <script language="JavaScript" src="/menuNav.js" type="text/javascript"></script>

</head>

<body onload="init();" class="bgColor11" bottommargin="0" topmargin="0" leftmargin="0" rightmargin="0" marginheight="0" marginwidth="0">
<table border="0" cellpadding="0" cellspacing="0" width="204" height="100%">    
    <tr>
        <td class="bgColor8">   
            <table border="0" cellpadding="0" cellspacing="0" width="16" height="100%">
                <tr>
                    <td background="/Images/leftEdge.gif" height="100%"><img src="/Images/1pixelTrans.gif" alt="" width="1" height="1" border="0"></td>
                </tr>
            </table>
        </td>
        
        <td class="bgColor8" valign="top">
            <table border="0" cellpadding="0" cellspacing="0" width="163" height="100%">
                <tr>
                    <td class="bgColor8" align="center" valign="bottom"><img src="/Images/menuTop.gif" alt="" width="163" height="4" border="0"></td>
                </tr>
                <tr>
                    <td background="/Images/menuBackground.gif" height="100%" width="100%" valign="top">
                        &nbsp;
                    </td>                    
                </tr>
            </table>
        </td>
        <td class="bgColor8" width="25">
            &nbsp;
        </td>
    </tr>
</table>     

<script language="JavaScript">
<!-- Begin Hide
  print_table_menu(20, 2, menuPages);
// End Hide -->
</script>

</body>
</html>
