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


// NTP Settings
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
const char* time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";  // TimeZone rule for Europe/Rome including daylight adjustment rules (optional)
#define NTP_OFFSET  +2  * 60 * 60       // s
#define NTP_INTERVAL 60 * 1000          // ms
#define NTP_ADDRESS  "0.pool.ntp.org"   // Url NTP
// END NTP Settings

// Battery Settings
const long batteryCheckDelay = 30000;
// END Battery settings
#endif
