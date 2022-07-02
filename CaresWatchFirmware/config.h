#ifndef __CONFIG_H__
#define __CONFIG_H__

#define BUTTON_1  33
#define BUTTON_2  25
#define BATT_PIN  12

const float VMAX_BATT = 4350.0;

const char* AP_SSID = "CARES Watch";
const char* AP_PASS = "";

// FreeRTOS Settings
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
// END FreeRTOS Settings

// Screen Settings
const long screenOnTime = 5000;
// END Screen Settings

// OpenWeather Settings
const long weatherCheckDelay = 3600*1000/2; //30 minutes

const String OW_API = "https://api.openweathermap.org/data/2.5/weather?q=";
const String OW_APPID = "&APPID=405c2a8dcfc56cbffeb70ff89adc1a0e";
// END OpenWeather Settings

// NTP Settings
#define NTP_OFFSET  +2  * 60 * 60       // s
#define NTP_INTERVAL 60 * 1000          // ms
#define NTP_ADDRESS  "0.pool.ntp.org"   // Url NTP
// END NTP Settings

// Battery Settings
const long batteryCheckDelay = 30000;
// END Battery settings
#endif
