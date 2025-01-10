#pragma once
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <Arduino.h>
#include "USB.h"

//#include "secrets.h"
#include "RTClib.h" //ADAFRUIT RTC
#include "Audio.h"

extern uint8_t x;
extern uint8_t y;

//paramaters for button
extern unsigned long shortPressAfterMiliseconds;   //how long short press shoud be. Do not set too low to avoid bouncing (false press events).
extern unsigned long longPressAfterMiliseconds;  //how long čong press shoud be.


extern std::string myString;
extern char buf2[51];
extern char Artist[51];
extern char Title[51];
extern char StationName[21];
#define NUMBER_OF_SENSORS 7
//#define NUMBER_OF_SENSORS 7
extern float Temp_Sensor_ReadOut[8];
extern unsigned long previousMillisSensor;
extern unsigned long previousMillisDisplay;
extern unsigned long previousMillisSDCardLogger;
extern unsigned long previousMillisUHR;
extern unsigned long previousMillisAudioInfo; 
extern unsigned long currentMillis;
extern USBCDC USBSerial;

//extern uRTCLib rtc;

extern char dateBuf[];
extern char TimeAktuell[];
extern RTC_PCF8563 rtc;
extern DateTime now;
extern Audio audio;




extern String ssid;
extern String password;
extern String hostname;
extern int update_rate_sensors;
extern int update_rate_display;
extern int update_rate_SDCardLogger;
extern int update_rate_UHR;
extern int update_rate_AudioInfo;
extern bool SDCardAvailible;
extern bool SDCardLoggingActive;
//extern int number_of_sensors;
#endif