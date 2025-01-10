#pragma once
#ifndef _ROTARY_H
#define _ROTARY_H

#include "AiEsp32RotaryEncoder.h"
#include "Arduino.h"
#include "io_pins.h"
#include "global.h"

#define ROTARY_ENCODER_VCC_PIN -1 /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4

//instead of changing here, rather change numbers above


void rotary_setup(void);
void on_button_short_click(void);
void on_button_long_click(void);
void handle_rotary_button(void);
void rotary_loop(void);
void IRAM_ATTR readEncoderISR(void);
  

#endif