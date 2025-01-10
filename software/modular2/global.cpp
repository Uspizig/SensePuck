#include "global.h"
//#include "uRTCLib.h"

USBCDC USBSerial;
RTC_PCF8563 rtc;
DateTime now;
Audio audio;


std::string myString;

//paramaters for button
unsigned long shortPressAfterMiliseconds = 50;   //how long short press shoud be. Do not set too low to avoid bouncing (false press events).
unsigned long longPressAfterMiliseconds = 1000;  //how long čong press shoud be.


char buf2[51];
char Artist[51];
char Title[51];
char StationName[21];
uint8_t x = 0;
uint8_t y = 0;

String ssid =     "xxxxxxxx";
String password = "xxxxxxxxxx";
String hostname = "ESP32S3THERMOLOGGER2";
int update_rate_sensors = 1000;
int update_rate_display = 1000;
int update_rate_UHR = 1000;
int update_rate_AudioInfo = 20000;
int update_rate_SDCardLogger = 30000;

bool SDCardAvailible = 0;
bool SDCardLoggingActive = 1;


char TimeAktuell[] = "hh:mm:ss";
char dateBuf[] = "YYYYMMDD-hh:mm:ss";

float Temp_Sensor_ReadOut[8];
unsigned long previousMillisSensor = 0;
unsigned long previousMillisDisplay = 0;
unsigned long previousMillisSDCardLogger = 0;
unsigned long previousMillisUHR = 0;
unsigned long previousMillisAudioInfo = 0; 
unsigned long currentMillis = 0;




