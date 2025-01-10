//Initalisiert Display & SD Card

//Trick: SD Karte ist auf anderem SPI Port als das Display
//declared above void setup()
/*SPIClass * hspi = NULL;
void setup()
hspi = new SPIClass(HSPI);
hspi->begin(14, 2, 15, 13);
if (!SD.begin(SD_CS, *hspi)) {
Serial.println(“Card Mount Failed”);
return;
}*/


#include "SPI.h"
#include "FS.h"
#include "SD.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

#include "USB.h"



#define TFT_RST 42
#define TFT_DC  14
#define TFT_CS  21
#define TFT_SCK  12
#define TFT_MISO  13
#define TFT_MOSI  11
#define TFT_BL 47

#define SD_SS         48 //DAT3
#define SD_MOSI      11 //CMD
#define SD_MISO      13 //DAT0
#define SD_SCK       12 //SCK


USBCDC USBSerial;
//Display
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST, TFT_MISO);

//SD Card
SPIClass * hspi = NULL;

void setup() {
  USBSerial.begin();USB.begin();
  USBSerial.println("GC9A01A Test!");
  delay(2000);
  tft.begin();

  //SD_Card_setup();
  //sd_card_checker();
 

  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); // Backlight on


  USBSerial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  USBSerial.print(F("Screen fill              "));
  USBSerial.println(testFillScreen());
  delay(500);

  USBSerial.print(F("Text                     "));
  USBSerial.println(testText());
  delay(3000);

  USBSerial.print(F("Lines                    "));
  USBSerial.println(testLines(GC9A01A_CYAN));
  delay(500);

  USBSerial.print(F("Horiz/Vert Lines         "));
  USBSerial.println(testFastLines(GC9A01A_RED, GC9A01A_BLUE));
  delay(500);

      //declared above void setup()
    
  

  USBSerial.println(F("Done!"));
}

void loop(void) {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);
  }
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
  tft.setCursor(0, 0);
  tft.setTextColor(GC9A01A_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(GC9A01A_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(GC9A01A_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(GC9A01A_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
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

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(GC9A01A_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  n = min(tft.width(), tft.height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx-i2, cy-i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i*10, i*10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i*10, i*10, 0));
    yield();
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft.drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for(i=min(tft.width(), tft.height()); i>20; i-=6) {
    i2 = i / 2;
    tft.fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}




void SD_Card_setup(void){

   hspi = new SPIClass(HSPI);
  hspi->begin(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
   if (!SD.begin(SD_SS, *hspi)) {
     USBSerial.println("Card Mount Failed");
     return;
   }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    USBSerial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    USBSerial.println("MMC");
  } else if(cardType == CARD_SD){
    USBSerial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    USBSerial.println("SDHC");
  } else {
    USBSerial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  USBSerial.printf("SD Card Size: %lluMB\n", cardSize);
}

void sd_card_checker(void){

  listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);
  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));


}


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  USBSerial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    USBSerial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    USBSerial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      USBSerial.print("  DIR : ");
      USBSerial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      USBSerial.print("  FILE: ");
      USBSerial.print(file.name());
      USBSerial.print("  SIZE: ");
      USBSerial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void createDir(fs::FS &fs, const char * path){
  USBSerial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    USBSerial.println("Dir created");
  } else {
    USBSerial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char * path){
  USBSerial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    USBSerial.println("Dir removed");
  } else {
    USBSerial.println("rmdir failed");
  }
}

void readFile(fs::FS &fs, const char * path){
  USBSerial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
   USBSerial.println("Failed to open file for reading");
    return;
  }

  USBSerial.print("Read from file: ");
  while(file.available()){
    USBSerial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  USBSerial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    USBSerial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    USBSerial.println("File written");
  } else {
    USBSerial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
  USBSerial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    USBSerial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
      USBSerial.println("Message appended");
  } else {
    USBSerial.println("Append failed");
  }
  file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
  USBSerial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    USBSerial.println("File renamed");
  } else {
    USBSerial.println("Rename failed");
  }
}

void deleteFile(fs::FS &fs, const char * path){
  USBSerial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    USBSerial.println("File deleted");
  } else {
    USBSerial.println("Delete failed");
  }
}

void testFileIO(fs::FS &fs, const char * path){
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    USBSerial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    USBSerial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if(!file){
    USBSerial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  USBSerial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}
