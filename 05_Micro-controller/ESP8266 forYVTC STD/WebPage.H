//由於V3 Bug,字串不得超過256,所以以下拆分為五組,而且專案設定中的列表檔必須選擇不生成
const char *HTTPHeader={"\
HTTP/1.0 200 OK\r\n\
Date: Fri, 31 Dec 2015 23:59:59 GMT\r\n\
Content-Type: text/html\r\n\
Content-Length: 865\r\n\
Connection: Closed\r\n\r\n"};

const char *WebPage1={"\
<html><h1>Welcome to Steven's ESP8266 Web Server Testing</h1>\
<body><title>Steven's Mini8266 Server</title>\
<form action=\"\"method=\"post\">\
<p><h3> This is a Test by Using ESP8266 as Web Server to Response and Control the LED States.</h3></p>\
<hr>"};

const char *WebPage2={"\
<fieldset><legend>Red LED State</legend>\
<input type=\"radio\" name=\"RLED\" value=\"R1\"> ON\
<input type=\"radio\" name=\"RLED\" value=\"R0\" checked=\"checked\"> OFF<br>\
</fieldset><br>"};

const char *WebPage2_1={"\
<fieldset><legend>Red LED State</legend>\
<input type=\"radio\" name=\"RLED\" value=\"R1\" checked=\"checked\"> ON\
<input type=\"radio\" name=\"RLED\" value=\"R0\"> OFF<br>\
</fieldset><br>"};

const char *WebPage3={"\
<fieldset><legend>Green LED State</legend>\
<input type=\"radio\" name=\"GLED\" value=\"G1\"> ON\
<input type=\"radio\" name=\"GLED\" value=\"G0\" checked=\"checked\"> OFF<br>\
</fieldset><br>"};

const char *WebPage3_1={"\
<fieldset><legend>Green LED State</legend>\
<input type=\"radio\" name=\"GLED\" value=\"G1\" checked=\"checked\"> ON\
<input type=\"radio\" name=\"GLED\" value=\"G0\"> OFF<br>\
</fieldset><br>"};

const char *WebPage4={"\
<fieldset><legend>Blue LED State</legend>\
<input type=\"radio\" name=\"BLED\" value=\"B1\"> ON\
<input type=\"radio\" name=\"BLED\" value=\"B0\" checked=\"checked\"> OFF<br>\
</fieldset><br>"};

const char *WebPage4_1={"\
<fieldset><legend>Blue LED State</legend>\
<input type=\"radio\" name=\"BLED\" value=\"B1\" checked=\"checked\"> ON\
<input type=\"radio\" name=\"BLED\" value=\"B0\"> OFF<br>\
</fieldset><br>"};

const char *WebPage5={"\
<br><input type=\"submit\" value=\"submit\"><hr>\
<center><p><h5>By Steven 2024.04.18 @MUST</h2></p>\
</form></body></html>"};
