#include <WiFi.h>
#include "config.h"
#include "logo.h"
#include "SSD1306.h"
#include <Preferences.h>
#include <ESPForm.h> //https://github.com/mobizt/ESPForm
#include "webpage.h"

SSD1306  display(0x3c, 5, 4);
Preferences preferences;
WiFiServer server(80);

String mySSID;
String myPass;
char _ssid[20];
char _pass[20];
void drawSplashScreen();
void showScreen();
int analogVolts;
IPAddress IP;

unsigned long prevMillis = 0;
unsigned long serverTimeout = 2 * 60 * 1000;

void formElementEventCallback(ESPFormClass::HTMLElementItem element)
{
  if (element.id == "ssidtext")
  {
    mySSID = element.value;
  }
  else if (element.id == "passtext")
  {
    myPass = element.value;
  }
  else if (element.id == "save-btn")
  {
    ESPForm.setElementContent("result", mySSID + " " + myPass);

    preferences.putString("mySSID", mySSID);
    preferences.putString("myPass", myPass);

    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);
    if (mySSID == (String)_ssid && myPass == (String)_pass)
    {
      ESPForm.setElementContent("result", "WiFi data saved! Please, reboot");
    }
    else
    {
      ESPForm.setElementContent("result", "Error saving WiFi Data");
    }

  }
  else if (element.id == "reboot-btn")
  {
    ESP.restart();
  }

  Serial.println();
  Serial.println("***********************************");
  Serial.println("id: " + element.id);
  Serial.println("value: " + element.value);
  Serial.println("type: " + element.type);
  Serial.println("event: " + ESPForm.getElementEventString(element.event));
  Serial.println("***********************************");
  Serial.println();
}

void serverTimeoutCallback()
{

  //If server timeout (no client connected within specific time)
  Serial.println("***********************************");
  Serial.println("Server Timeout");
  Serial.println("***********************************");
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  preferences.begin("myWatch", false);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  analogVolts = (int)((float)(analogReadMilliVolts(BATT_PIN) / VMAX_BATT) * 200);
  drawSplashScreen();
  display.display();

  //  preferences.putString("mySSID", String("ssid"));
  //  preferences.putString("myPass", String("pass"));
  //  if (!preferences.getString("mySSID", mySSID, 20) || !preferences.getString("myPass", myPass, 20))

  if (!digitalRead(BUTTON_1) || !preferences.getString("mySSID", _ssid, 20) || !preferences.getString("myPass", _pass, 20))
  {
    WiFi.softAP(AP_SSID, AP_PASS);
    //      server.begin();

    IP = WiFi.softAPIP();

    display.clear();
    display.drawString(0, 0, "Connect to " + (String)AP_SSID);
    display.drawString(0, 10, "and visit this address");
    display.drawString(0, 20, "with your browser:");
    display.drawString(0, 30, IP.toString());
    display.display();

    //Add the html contents (in html.h) for the web page rendering
    ESPForm.addFileData(index_html, "index.html");

    //Add html element event listener, id "text1" for onchange event
    ESPForm.addElementEventListener("ssidtext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("passtext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("save-btn", ESPFormClass::EVENT_ON_CLICK);
    ESPForm.addElementEventListener("reboot-btn", ESPFormClass::EVENT_ON_CLICK);
    //Start ESPForm's Webserver
    ESPForm.begin(formElementEventCallback, serverTimeoutCallback, serverTimeout, true);

    ESPForm.startServer();
  }
  else
  {
    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);

    mySSID = _ssid;
    myPass = _pass;

    display.clear();
    display.drawString(0, 0, "Connecting to:");
    display.drawString(0, 10, mySSID);
    display.display();

    WiFi.begin(mySSID.c_str(), myPass.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      delay(125);
      display.drawString(0, 20, "   ");
      display.display();

      delay(125);
      display.drawString(0, 20, ".  ");
      display.display();

      delay(125);
      display.drawString(0, 20, ".. ");
      display.display();

      delay(125);
      display.drawString(0, 20, "...");
      display.display();

    }
    display.clear();
    display.drawString(0, 0, "Connected to:");
    display.drawString(0, 10, mySSID);
    display.drawString(0, 20, WiFi.localIP().toString());
    display.display();

    //      drawSplashScreen();
    //      display.display();


  }



  //  else
  //  {
  //    preferences.getString("mySSID", mySSID, 20);
  //    preferences.getString("myPass", myPass, 20);
  //    display.clear();
  //    display.drawString(0, 0, mySSID);
  //    display.drawString(0, 30, myPass);
  //    display.display();
  //  }
}

//void loop() {
//  WiFiClient client = server.available();
//  if (client) {
//    display.drawString(0, 20, "            ");
//    display.drawString(0, 20, "New Client");
//    display.drawString(0, 30, client.remoteIP().toString());
//    display.display();
//  }
//  else
//  {
//    display.drawString(0, 20, "No Client");
//    display.drawString(0, 30, "               ");
//
//    display.display();
//  }
//  delay(1000);
//}

void loop()
{
  //If a client existed
  if (ESPForm.getClientCount() > 0)
  {

    if (millis() - prevMillis > 1000)
    {
      prevMillis = millis();
      //The event listener for text2 is not set because we don't want to listen to its value changes
      //      ESPForm.setElementContent("result", ssid + pass);
    }
  }
}

void drawSplashScreen() {
  display.drawXbm(0, 0, 128, 64, (uint8_t*)logo_bits);
}
