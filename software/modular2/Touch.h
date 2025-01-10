#pragma once
#ifndef _TOUCH_H
#define _TOUCH_H
#include <Arduino.h>
#include <Wire.h>
#include "io_pins.h"
#include "global.h"

#define CHSC6X_I2C_ID 0x2e
#define CHSC6X_MAX_POINTS_NUM 1
#define CHSC6X_READ_POINT_LEN 5

void touch_init(void);
bool chsc6x_is_pressed(void);
void chsc6x_convert_xy(void);
void chsc6x_get_xy(void);

#endif