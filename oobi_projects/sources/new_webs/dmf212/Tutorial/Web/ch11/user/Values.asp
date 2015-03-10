<!-- (c) 2002 Art & Logic Software Development. All Rights Reserved. -->
<!-- $Id: Values.asp,v 1.1.1.1 2005/09/01 02:36:39 edson Exp $-->

<!--	CH08: Literal text removed from ASP source, replaced with calls to
		getLabel() and getLabelVal() as appropriate.
-->

<html>
<head>
<title><%getLabel("page.title"); get("_chapter_");%></title>
</head>
<body bgcolor=<%get("_bgcolor");%>
<img src="/images/<%get("_logo");%>" alt="logo image">

<h1><%getLabel("data.values");%></h1>

<p>
This display shows simulated data from the 'Imaginary Pseudo Device'. This is
just a snapshot of the data -- press 'Refresh' on your browser to view updated
data. 
</p>
<p>
The data is color coded -- any values less than or equal to the 'lowerAlarm'
value for that item is displayed in <font color="blue">blue</font>, any values
higher than the 'upperAlarm' setting for that item is displayed in <font
color="red">red</font>.
</p>
<table border>
<tr>
   <td><%getLabel("label");%></td>
   <td><%getLabel("value");%></td>
   <td><%getLabel("lower.alarm");%></td>
   <td><%getLabel("upper.alarm");%></td>
</td>   

<%
   // see where we're supposed to start listing values...
   startPos = getQueryVal("start", 0);
   // see how many we're supposed to show at one time.
   count = getVal("_rowCount");
   if (!__success__)
   {
      /* The server hasn't been configured with a number of rows to 
       * show on a single page. We'll set a default.
       */
      count = 8;
      set("_rowCount", count);
   }
   endPos = startPos + count;
   upperAlarmColor = getVal("_upperAlarmColor");
   if (!__success__)
   {
      /* The upper Alarm color hasn;t been set. We'll set it to a 
       * default value of red here.
       */
       upperAlarmColor = "red";
       set("_upperAlarmColor", upperAlarmColor);
    }
   lowerAlarmColor = getVal("_lowerAlarmColor");
   if (__error__ == "ParameterName")
   {
      /* The lower Alarm color hasn;t been set. We'll set it to a 
       * default value of red here.
       */
       lowerAlarmColor = "blue";
       set("_lowerAlarmColor", lowerAlarmColor);
    }

   for (i = startPos; __success__ && (i < endPos); i++)
   {
      label = getVal("system.values.label", i);
      if (__success__)
      {
         value = getVal("system.values.value", i);
         upperAlarm = getVal("system.values.upperAlarm", i);
         lowerAlarm = getVal("system.values.lowerAlarm", i);
         write("<tr>\n");
         write("<td>" + label + "</td>\n");
         isAlarm = 0
         write("<td>");
         if (value >= upperAlarm)
         {
            write("<font color=\"" + upperAlarmColor + "\">");
            isAlarm = 1
         }
         else if (value <= lowerAlarm)
         {
            write("<font color=\"" + lowerAlarmColor + "\">");
            isAlarm = 1
         }

         write(value); 
         if (isAlarm)
         {
            write("</font>");
         }
         write("</td>\n");
         write("<td>"+ lowerAlarm + "</td>\n");
         write("<td>"+ upperAlarm + "</td>\n</tr>\n");
      }
   }
   write("</table>\n");
   /*
    * see if we need to display a 'previous' link.
    */
   if (startPos >= count)
   {
      write('<a href="/user');
      write('/Values.asp?start=' + (startPos - count) + '">');
      write(getLabelVal("previous.values") + '</a><br />\n');
   }

   /* test to see if there are any items after what we've just displayed...*/
   value = getVal("system.values.value", endPos);
   if (__success__)
   {
      // we successfully got a value past what we've already displayed -- 
      // display a link to show the next page of values.
      write('<a href="/user');
      write('/Values.asp?start=' + endPos + '">' + getLabelVal("more.values") + "</a>");
   }

   /* CH07: If the current user has membership in at least the 'tech' group, 
    *  allow them to edit the parameter values...
    */
   if (userCanAccess("tech"))
   {
      write('<br />\n<a href="/tech/ConfigValues.asp">');
      write(getLabelVal("configure.values") + '</a>\n');
   }

   
%>
</body>
</html>
