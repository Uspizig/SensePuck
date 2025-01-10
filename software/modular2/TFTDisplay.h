#pragma once
#ifndef _TFTDISPLAY_H
#define _TFTDISPLAY_H

#include <Arduino.h>
#include "io_pins.h"
#include "global.h"

#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include <Fonts/FreeMonoBoldOblique12pt7b.h>

void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour);
void tft_start(void); // Initializes the TFT screen
void tft_tester(void); //runs various tests on the screen and measures performance
void TFTDisplay_TouchCoordinates(int pos_x, int pos_y);
void TFTDisplay_MeasurementResults(int x, int y); //shows content of Array Temp_Sensor_ReadOut to the screen
void TFTDisplay_Hello(int x, int y);
unsigned long testFillScreen();
unsigned long testText();
unsigned long testLines(uint16_t color);
unsigned long testFastLines(uint16_t color1, uint16_t color2);
void tft_backlight_controller(boolean BACKLIGHT_STATUS);
int rainbow(uint8_t value);
void Display_BlackScreen(void);
void TFT_ArtistTitle(int x, int y);
void TFT_audio_info(const char *info, int x, int y);
void TFT_StationName(int x, int y);

#endif