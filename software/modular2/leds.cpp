#include "io_pins.h"
#include "global.h"
#include "leds.h"


#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);


#define DELAYVAL 200 // Time (in milliseconds) to pause between pixels

void led_setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}


void led_test(void){
  pixels.clear(); // Set all pixel colors to 'off'
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 20, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

void led_set(uint8_t sensor_number){
  pixels.setPixelColor(sensor_number, pixels.Color(0, 15, 0));
  pixels.setPixelColor(15-sensor_number, pixels.Color(0, 250, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
}
void led_red(uint8_t sensor_number){
  pixels.setPixelColor(sensor_number, pixels.Color(15, 0, 0));
  pixels.setPixelColor(15-sensor_number, pixels.Color(250, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void led_off(uint8_t sensor_number){
  pixels.setPixelColor(sensor_number, pixels.Color(0, 0, 0));
  pixels.setPixelColor(15-sensor_number, pixels.Color(0, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
}