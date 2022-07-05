#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

//Raw content of index.html in plain text
static const char *index_html = R"--espform--(
<!DOCTYPE html>
<html lang="en">

<head>
  <title> CARES Watch configuration </title>
  <style>
body {
    padding: 20px;
  }
  
  label {
    font-size: 17px;
    font-family: sans-serif;
  }
  
  input {
    display: block;
    width: 300px;
    height: 40px;
    padding: 4px 10px;
    margin: 10 0 10 0;
    border: 1px solid #03A9F4;
    background: #cce6ff;
    color: #1c87c9;
    font-size: 17px;
  }
}
  </style>
</head>

<body>
  <form>
    <label for="text1">SSID</label>
    <input type="text" id="ssidtext" name="ssidtext" value=""/>
    <label for="text2">Password</label>
    <input type="text" id="passtext" name="passtext" value=""/>
    <button type="button" id="savewifi-btn" class="btn btn-primary">Save WiFi Data</button>
    <label id="result" for="result"></label>
    <div />
    <label for="text3">Weather city</label>
    <input type="text" id="citytext" name="citytext" value=""/>
    <label for="text3">OpenWeather token</label>
    <input type="text" id="owtoken" name="owtoken" value=""/>
    <button type="button" id="saveweather-btn" class="btn btn-primary">Save Weather Data</button>
    <label id="result" for="result"></label>
    <div />
    <button type="button" id="reboot-btn" class="btn btn-primary">Reboot CARES Watch</button>

</body>

</html>
)--espform--";

#endif
