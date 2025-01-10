#include "TFTDisplay.h"
#include <Arduino.h>
#include "io_pins.h"
#include "global.h"

#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#define DEG2RAD 0.0174532925


//Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST, TFT_MISO);

Adafruit_GC9A01A tft(DISP_CS, DISP_DC, SPI_MOSI, SPI_SCK, DISP_RST, SPI_MISO);


uint8_t red = 31; // Red is the top 5 bits of a 16-bit colour value
uint8_t green = 0;// Green is the middle 6 bits
uint8_t blue = 0; // Blue is the bottom 5 bits
uint8_t state = 0;

void tft_backlight_controller(boolean BACKLIGHT_STATUS){


  pinMode(DISP_BLK, OUTPUT);
  digitalWrite(DISP_BLK, BACKLIGHT_STATUS); // Backlight on

}

void tft_start(void){
  tft_backlight_controller(LOW);
  pinMode(DISP_RST, OUTPUT);
  pinMode(DISP_DC, OUTPUT);
  pinMode(DISP_CS, OUTPUT);
  USBSerial.println("GC9A01A Test!");
  tft.begin();
  tft.setRotation(screen_rotation);
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setTextSize(2);
  //tft.setFont(&FreeMonoBoldOblique12pt7b);
  tft_backlight_controller(HIGH);
}
void tft_tester(void){

  USBSerial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  USBSerial.print(F("Screen fill              "));
  USBSerial.println(testFillScreen());
  delay(500);

  USBSerial.print(F("Text                     "));
  USBSerial.println(testText());
  delay(1000);
/*
  USBSerial.print(F("Lines                    "));
  USBSerial.println(testLines(GC9A01A_CYAN));
  delay(500);

  USBSerial.print(F("Horiz/Vert Lines         "));
  USBSerial.println(testFastLines(GC9A01A_RED, GC9A01A_BLUE));
  delay(500);*/
  USBSerial.println(F("TFT Test Done!"));

}


void TFTDisplay_TouchCoordinates(int pos_x, int pos_y){
  tft.setCursor(pos_x, pos_y);
  tft.print("X:"); tft.print(x); tft.print(" Y:"); tft.print(y);

}

void TFTDisplay_MeasurementResults(int x, int y){ 
  
  char buf1[] = "hh:mm:ss";
  now.toString(buf1);
  //USBSerial.print(now.toString(buf1));USBSerial.println(";");
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setCursor(x+20, y+15);
  //tft.print(TimeAktuell); //zeigt aktuelle Uhrzeit an.
  tft.print(buf1); //zeigt aktuelle Uhrzeit an.
  //tft.setCursor(x+20, y+35);
  //tft.print("Web Radio"); //zeigt aktuelle Uhrzeit an.
}

void TFT_ArtistTitle(int x, int y){
      tft.setCursor(x, y); tft.print("A:"); tft.print(Artist);
      tft.setCursor(x, y+20); tft.print("T:"); tft.print(Title);
}

void TFT_StationName(int x, int y){
        
      tft.setCursor(x, y); tft.print(StationName);
}


void TFT_audio_info(const char *info, int x, int y){    
    tft.setCursor(x, y); 
    tft.print(info);        
}


void TFTDisplay_Hello(int x, int y){
  tft.setCursor(x+20, y+35);
  tft.print(millis()); //zeigt aktuelle Uhrzeit an.
  tft.setCursor(x+20, y+55);
  tft.print("Display Test"); //zeigt aktuelle Uhrzeit an.
}
// #########################################################################
// Draw a circular or elliptical arc with a defined thickness
// #########################################################################

// x,y == coords of centre of arc
// start_angle = 0 - 359
// seg_count = number of 6 degree segments to draw (60 => 360 degree arc)
// rx = x axis outer radius
// ry = y axis outer radius
// w  = width (thickness) of arc in pixels
// colour = 16-bit colour value
// Note if rx and ry are the same then an arc of a circle is drawn

void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour)
{

  uint8_t seg = 6; // Segments are 3 degrees wide = 120 segments for 360 degrees
  uint8_t inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to segment start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}





// #########################################################################
// Return a 16-bit rainbow colour
// #########################################################################
int rainbow(uint8_t value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  switch (state) {
    case 0:
      green ++;
      if (green == 64) {
        green = 63;
        state = 1;
      }
      break;
    case 1:
      red--;
      if (red == 255) {
        red = 0;
        state = 2;
      }
      break;
    case 2:
      blue ++;
      if (blue == 32) {
        blue = 31;
        state = 3;
      }
      break;
    case 3:
      green --;
      if (green == 255) {
        green = 0;
        state = 4;
      }
      break;
    case 4:
      red ++;
      if (red == 32) {
        red = 31;
        state = 5;
      }
      break;
    case 5:
      blue --;
      if (blue == 255) {
        blue = 0;
        state = 0;
      }
      break;
  }
  return red << 11 | green << 5 | blue;
}


void Display_BlackScreen(void){
  tft.fillScreen(GC9A01A_BLACK);
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  tft.fillScreen(GC9A01A_RED);
  yield();
  tft.fillScreen(GC9A01A_GREEN);
  yield();
  tft.fillScreen(GC9A01A_BLUE);
  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(GC9A01A_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 30);
  tft.setTextColor(GC9A01A_WHITE);  tft.setTextSize(1);
  tft.println("Hello Thermo1!");
  tft.setTextColor(GC9A01A_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(GC9A01A_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GC9A01A_GREEN);
  tft.setTextSize(5);
  tft.println("HOOORAY");
  tft.setTextSize(2);
  tft.println("This is startup,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) tft.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}