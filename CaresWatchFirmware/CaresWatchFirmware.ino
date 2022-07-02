#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "logo.h"
#include "SSD1306.h"
#include <Preferences.h>
#include <ESPForm.h> //https://github.com/mobizt/ESPForm
#include "webpage.h"
#include "time.h"
#include "sntp.h"
#include <NTPClient.h>
#include <ArduinoJson.h>


SSD1306  display(0x3c, 5, 4);
Preferences preferences;
WiFiServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String mySSID;
String myPass;
String myCity;

char _ssid[20];
char _pass[20];
char _city[20];

void drawSplashScreen();
void showScreen();
int analogVolts;
long batteryCheckMillis = 0;
long weatherCheckMillis = 0;
IPAddress IP;

unsigned long prevMillis = 0;
unsigned long serverTimeout = 2 * 60 * 1000;
//struct tm timeinfo;

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
  else if (element.id == "citytext")
  {
    myCity = element.value;
  }
  else if (element.id == "savewifi-btn")
  {
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
  else if (element.id == "saveweather-btn")
  {
    preferences.putString("myCity", myCity);
    preferences.getString("myCity", _city, 20);

    if (myCity == (String)_city)
    {
      ESPForm.setElementContent("result", "Weather data saved! Please, reboot");
    }
    else
    {
      ESPForm.setElementContent("result", "Error saving weather Data");
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


long startMillis = 0;
long delayScreen = 5000;
bool display_on = false;

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

  if (!digitalRead(BUTTON_1) || !preferences.getString("mySSID", _ssid, 20) || !preferences.getString("myPass", _pass, 20) || !preferences.getString("myCity", _city, 20))
  {
    WiFi.softAP(AP_SSID, AP_PASS);

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
    ESPForm.addElementEventListener("citytext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("savewifi-btn", ESPFormClass::EVENT_ON_CLICK);
    ESPForm.addElementEventListener("saveweather-btn", ESPFormClass::EVENT_ON_CLICK);
    ESPForm.addElementEventListener("reboot-btn", ESPFormClass::EVENT_ON_CLICK);
    //Start ESPForm's Webserver
    ESPForm.begin(formElementEventCallback, serverTimeoutCallback, serverTimeout, true);

    ESPForm.startServer();

    while (1);
  }
  else
  {
    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);
    preferences.getString("myCity", _city, 20);

    mySSID = _ssid;
    myPass = _pass;
    myCity = _city;

    WiFi.begin(mySSID.c_str(), myPass.c_str());
    //
    //    while (WiFi.status() < WL_CONNECTED) {
    //      display.clear();
    //      delay(125);
    //      display.drawString(0, 20, "   ");
    //      display.display();
    //
    //      delay(125);
    //      display.drawString(0, 20, ".  ");
    //      display.display();
    //
    //      delay(125);
    //      display.drawString(0, 20, ".. ");
    //      display.display();
    //
    //      delay(125);
    //      display.drawString(0, 20, "...");
    //      display.display();
    //
    //    }
    //
    //    if (WiFi.status() == WL_CONNECTED)
    //    {
    //      display.clear();
    //      display.drawString(0, 0, "Connected to:");
    //      display.drawString(0, 10, mySSID);
    //      display.drawString(0, 20, WiFi.localIP().toString());
    //      display.display();
    //    }
    //    else
    //    {
    //      display.clear();
    //      display.drawString(0, 0, "Error connecting to ");
    //      display.drawString(0, 10, mySSID);
    //      display.display();
    //    }

    //sntp_set_time_sync_notification_cb( timeavailable );
    //    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
    //    configTzTime(time_zone, ntpServer1, ntpServer2);
  }
  xTaskCreatePinnedToCore(
    wifi_task
    ,  "wifi_task"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  ARDUINO_RUNNING_CORE);
  display_on = true;
  analogVolts = (int)((float)(analogReadMilliVolts(BATT_PIN) * 200 / VMAX_BATT));
  updateWeather();

}
int wifi_status;

void wifi_task(void *param) {
  (void) param;
  vTaskDelay(1000);

  while (true) {
    wifi_status = WiFi.status();

    if (wifi_status != WL_CONNECTED) {
      WiFi.reconnect();
    }
    vTaskDelay(10000);
  }
}

void showScreen()
{
  display_on = true;
  startMillis = millis();
}


String jsonString;
DynamicJsonDocument doc(1024);
String OW_description;
int OW_temp;
int OW_hum;
String OW_city;

int updateWeather()
{
  OW_description = "";
  OW_city = "";
  Serial.println("updateWeather");
  HTTPClient http;
  String url = (String)(OW_API + myCity + OW_APPID);
  Serial.println("url: " + url);
  http.begin(url); //HTTP
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("payload: ");
      Serial.println(payload);
      deserializeJson(doc, payload);
      //JsonObject obj = doc["weather"][0].as<JsonObject>();

      OW_description = doc["weather"][0]["description"].as<String>();
      OW_city = doc["name"].as<String>();
      OW_temp = doc["main"]["temp"].as<String>().toInt() / 10;
      OW_hum = doc["main"]["humidity"].as<String>().toInt();

      Serial.println("desc: " + OW_description);
      Serial.println("city: " + OW_city);
      Serial.println("hum: " + (String)OW_hum);

    }
  } else {
    Serial.println("Error HTTP: " + (String)httpCode);
  }

  http.end();

  return httpCode;
}

void showMainScreen()
{
  timeClient.update();
  String formattedTime;

  display.clear();
  display.setFont(ArialMT_Plain_10);

  if (millis() - batteryCheckMillis > batteryCheckDelay )
  {
    analogVolts = (int)((float)(analogReadMilliVolts(BATT_PIN) * 200 / VMAX_BATT));
    batteryCheckMillis = millis();
  }

  if (millis() - weatherCheckMillis > weatherCheckDelay )
  {
    updateWeather();
    weatherCheckMillis = millis();
  }

  if (OW_description != "" && OW_city != "")
  {
    display.drawString(0, 40, OW_city);
    String str = OW_description + ", " + (String)OW_temp + (String)"*C" + (String)", " + (String)OW_hum + (String)'%';
    display.drawString(0, 50, str);
  }

  display.drawString(100, 0, (String)analogVolts + (String)'%');

  if (wifi_status == WL_CONNECTED)
  {
    display.drawString(0, 0, mySSID);
  }
  else if  (wifi_status == WL_IDLE_STATUS)
  {
    display.drawString(0, 0, "Connecting...");
  }
  else
  {
    display.drawString(0, 0, "Not connected");
  }
  display.setFont(ArialMT_Plain_24);

  if (timeClient.isTimeSet()) {
    formattedTime = timeClient.getFormattedTime();
    display.drawString(15, 15, formattedTime);
  }
  else
  {
    display.drawString(0, 20, "  NO TIME");
  }
  display.display();
}


void loop()
{
  bool button1_state = digitalRead(BUTTON_1);
  bool button2_state = digitalRead(BUTTON_2);
  //  display.clear();


  if (!button1_state && !display_on)
  {
    Serial.println("Show screen");
    showScreen();
  }
  //  else if (!button1_state && display_on)
  //  {
  //    display.clear();
  //
  //    display.display();
  //  }

  if (display_on && (millis() - startMillis) < screenOnTime)
  {
    if (OW_description == "" || OW_city == "")
    {
      updateWeather();
    }
    showMainScreen();
  }
  else
  {
    if (display_on)
    {
      display.clear();
      display.display();
      display_on = false;
    }
  }
}

void drawSplashScreen() {
  display.drawXbm(0, 0, 128, 64, (uint8_t*)logo_bits);
}
