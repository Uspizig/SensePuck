#pragma once
#ifndef _LEDS_H
#define _LEDS_H

#include <Arduino.h>
#include "io_pins.h"
#include "global.h"


void led_setup(void);
void led_test(void);
void led_set(uint8_t sensor_number);
void led_red(uint8_t sensor_number);
void led_off(uint8_t sensor_number);
#endif