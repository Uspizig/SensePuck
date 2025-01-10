#pragma once
#ifndef _RTCTIMEKEEPER_H
#define _RTCTIMEKEEPER_H

//https://wolles-elektronikkiste.de/ds3231-echtzeituhr
#include <Arduino.h>
#include "io_pins.h"
#include "global.h"
#include "RTCLib.h"

void RTC_Setup(void);
void RTC_time_date_formatter(void);
void RTC_time_formatter(void);
#endif