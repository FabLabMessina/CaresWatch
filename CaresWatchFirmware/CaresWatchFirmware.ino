#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "logo.h"
#include <Wire.h>
#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>
#include <Preferences.h>
#include <ESPForm.h> //https://github.com/mobizt/ESPForm
#include "webpage.h"
#include "time.h"
//#include "sntp.h"
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

//SSD1306  display(0x3c, 5, 4);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

Preferences preferences;
WiFiServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

String mySSID;
String myPass;
String myCity;
String myOWToken;

char _ssid[20];
char _pass[20];
char _city[20];
char _owtoken[50];

void drawSplashScreen();
void showScreen();
int analogVolts;
long batteryCheckMillis = 0;
long weatherCheckMillis = 0;
long displayOffMillis = 0;
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
  else if (element.id == "owtoken")
  {
    myOWToken = element.value;
  }
  else if (element.id == "save-btn")
  {
    preferences.putString("mySSID", mySSID);
    preferences.putString("myPass", myPass);

    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);

    preferences.putString("myCity", myCity);
    preferences.getString("myCity", _city, 20);

    preferences.putString("myOWToken", myOWToken);
    preferences.getString("myOWToken", _owtoken, 50);

    if (mySSID == (String)_ssid && myPass == (String)_pass &&
        myCity == (String)_city && myOWToken == (String)_owtoken)
    {
      ESPForm.setElementContent("result", "Data has been saved! Please, reboot");
    }
    else
    {
      ESPForm.setElementContent("result", "An error has occurred while saving");
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
bool display_on = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(5, 4);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  preferences.begin("myWatch", false);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(180);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 2);
  display.setFont();
  analogVolts = constrain(analogReadMilliVolts(BATT_PIN) * 2, VMIN_BATT, VMAX_BATT);

  drawSplashScreen();

  if (!digitalRead(BUTTON_1) || !preferences.getString("mySSID", _ssid, 20) || !preferences.getString("myPass", _pass, 20) || !preferences.getString("myCity", _city, 20) || !preferences.getString("myOWToken", _owtoken, 50) )
  {
    WiFi.softAP(AP_SSID, AP_PASS);

    IP = WiFi.softAPIP();
    display.clearDisplay();
    display.setCursor(0, 2);
    display.print("Connect to\n\"" + (String)AP_SSID + (String)"\" WiFi\nand visit this address with your browser:\n\n" + IP.toString()) ;
    display.display();

    //Add the html contents (in html.h) for the web page rendering
    ESPForm.addFileData(index_html, "index.html");

    //Add html element event listener, id "text1" for onchange event
    ESPForm.addElementEventListener("ssidtext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("passtext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("citytext", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("owtoken", ESPFormClass::EVENT_ON_CHANGE);
    ESPForm.addElementEventListener("save-btn", ESPFormClass::EVENT_ON_CLICK);
    ESPForm.addElementEventListener("reboot-btn", ESPFormClass::EVENT_ON_CLICK);
    //Start ESPForm's Webserver
    ESPForm.begin(formElementEventCallback, serverTimeoutCallback, serverTimeout, true);

    ESPForm.startServer();

    while (ESPForm.getClientCount() == 0);
    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);
    preferences.getString("myCity", _city, 20);
    preferences.getString("myOWToken", _owtoken, 50);
    ESPForm.setElementContent("ssidtext", _ssid);
    ESPForm.setElementContent("passtext", _pass);
    ESPForm.setElementContent("citytext", _city);
    ESPForm.setElementContent("owtoken", _owtoken);

    while (1);
  }
  else
  {
    preferences.getString("mySSID", _ssid, 20);
    preferences.getString("myPass", _pass, 20);
    preferences.getString("myCity", _city, 20);
    preferences.getString("myOWToken", _owtoken, 50);

    mySSID = _ssid;
    myPass = _pass;
    myCity = _city;
    myOWToken = _owtoken;
    WiFi.begin(mySSID.c_str(), myPass.c_str());
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
  updateWeather();
}

int wifi_status;

void wifi_task(void *param) {
  (void) param;
  vTaskDelay(1000);

  while (true) {
    wifi_status = WiFi.status();

    if (wifi_status != WL_CONNECTED && wifi_status != WIFI_OFF) {
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
  String url = (String)(OW_API + myCity + OW_APPID + myOWToken);
  Serial.println("url: " + url);
  http.begin(url); //HTTP
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("payload: ");
      Serial.println(payload);
      deserializeJson(doc, payload);

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

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(0.6);
  display.setCursor(0, 2);
  display.setFont();
  /*if (millis() - batteryCheckMillis > batteryCheckDelay )
    {
    analogVolts = (int)((float)(analogReadMilliVolts(BATT_PIN) * 200 / VMAX_BATT));
    batteryCheckMillis = millis();
    }*/

  if (millis() - weatherCheckMillis > weatherCheckDelay )
  {
    updateWeather();
    weatherCheckMillis = millis();
  }

  if (OW_description != "" && OW_city != "")
  {
    display.setCursor(0, 45);
    display.print(OW_city);
    String str = OW_description + ", " + (String)OW_temp + (String)"'C" + (String)", " + (String)OW_hum + (String)'%';
    display.setCursor(0, 55);
    display.print(str);
  }
  display.setCursor(104, 2);

  int batt_percentage = map(analogVolts, VMIN_BATT, VMAX_BATT, 0, 100);
  display.print((String)batt_percentage + (String)'%');

  if (wifi_status == WL_CONNECTED)
  {
    display.setCursor(0, 2);
    display.print(mySSID);
  }
  else if  (wifi_status == WL_IDLE_STATUS)
  {
    display.setCursor(0, 2);
    display.print("Connecting...");
  }
  else
  {
    display.setCursor(0, 2);
    display.print("Not connected");
  }

  display.setFont(&FreeSansBold12pt7b);
  if (timeClient.isTimeSet()) {
    formattedTime = timeClient.getFormattedTime();
    display.setCursor(16, 36);
    display.print(formattedTime);
  }
  else
  {
    display.setCursor(16, 36);
    display.print("NO TIME");
  }
  display.display();
}


void loop()
{
  bool button1_state = digitalRead(BUTTON_1);
  bool button2_state = digitalRead(BUTTON_2);
  //  display.clearDisplay();


  if (!button1_state && !display_on)
  {
    Serial.println("Show screen");
    showScreen();
  }
  else if (!display_on && (millis() - displayOffMillis) > batteryCheckDelay)
  {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    analogVolts = constrain(analogReadMilliVolts(BATT_PIN) * 2, VMIN_BATT, VMAX_BATT);
    WiFi.begin(mySSID.c_str(), myPass.c_str());
    displayOffMillis = millis();
  }
  //  else if (!button1_state && display_on)
  //  {
  //    display.clearDisplay();
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
      display.clearDisplay();
      display.display();
      display_on = false;
      displayOffMillis = millis();
    }
  }
}

void drawSplashScreen() {
  display.clearDisplay();
  display.display();
  display.drawBitmap(0, 0, (uint8_t*)logo_bits, 128, 64, SSD1306_WHITE);
  display.display();

}
