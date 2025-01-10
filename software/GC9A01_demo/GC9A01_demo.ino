#include <SPI.h>
#include "USB.h"
#include "GC9A01.h"

#include <Wire.h>


//SEEED DISPLAY

#define RES 0
#define DC  14
#define CS  21
#define SCK  12
#define MISO  13
#define MOSI  11
#define SS  21
#define BLK 47

#define SDA2 17
#define SCL2 8

#define LCD_CS 21
#define LCD_MOSI 11
#define LCD_MISO 13
#define LCD_SCK 12
#define LCD_DC 14
#define LCD_BL 47
#define SD_CS 48
#define TOUCH_INT 9
#define BAT_READ 6

USBCDC USBSerial;

void GC9A01_set_reset(uint8_t val) {
    digitalWrite(RES, val);
}

void GC9A01_set_data_command(uint8_t val) {
    digitalWrite(DC, val);
}

void GC9A01_set_chip_select(uint8_t val) {
    digitalWrite(CS, val);
}

void GC9A01_spi_tx(uint8_t *data, size_t len) {
    while (len--) {
        SPI.transfer(*data);
        data++;
    }
}

void GC9A01_delay(uint16_t ms) {
    delay(ms);
}

void setup() {
    
    
    USBSerial.begin();USB.begin();
    pinMode(BLK, OUTPUT);
    pinMode(RES, OUTPUT);
    pinMode(DC, OUTPUT);
    pinMode(CS, OUTPUT);
    USBSerial.println("Pin Mode Set");
    //SPI.begin(22, 21);
    digitalWrite(BLK, 1);
    USBSerial.println("Pin Set BLK");
    SPI.begin(SCK, MISO, MOSI, SS);
    USBSerial.println("SPI Begin erledigt");
    USBSerial.println("Booting");
    GC9A01_init();
    struct GC9A01_frame frame = {{0,0},{239,239}};
    GC9A01_set_frame(frame);
    Wire.begin(SDA2, SCL2);
}

void loop() {
    scani2c();
    uint8_t color[3];

    // Triangle
    color[0] = 0xFF;
    color[1] = 0xFF;
    

    // Checkerboard
    USBSerial.println("Schachbrett");
    for (int x = 0; x < 240; x++) {
        for (int y = 0; y < 240; y++) {
            if ((x / 10) % 2 ==  (y / 10) % 2) {
                color[0] = 0xFF;
                color[1] = 0xFF;
                color[2] = 0xFF;
            } else {
                color[0] = 0x00;
                color[1] = 0x00;
                color[2] = 0x00;
            }
            if (x == 0 && y == 0) {
                GC9A01_write(color, sizeof(color));
            } else {
                GC9A01_write_continue(color, sizeof(color));
            }
        }
    }

    delay(1000);

    // Swiss flag
    USBSerial.println("Swiss flag");
    color[0] = 0xFF;
    for (int x = 0; x < 240; x++) {
        for (int y = 0; y < 240; y++) {
            if ((x >= 1*48 && x < 4*48 && y >= 2*48 && y < 3*48) ||
                (x >= 2*48 && x < 3*48 && y >= 1*48 && y < 4*48)) {
                color[1] = 0xFF;
                color[2] = 0xFF;
            } else {
                color[1] = 0x00;
                color[2] = 0x00;
            }
            if (x == 0 && y == 0) {
                GC9A01_write(color, sizeof(color));
            } else {
                GC9A01_write_continue(color, sizeof(color));
            }
        }
    }

    delay(1000);

}

void scani2c(void){
 byte error, address;
  int nDevices;
  USBSerial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      USBSerial.print("I2C device found at address 0x");
      if (address<16) {
        USBSerial.print("0");
      }
      USBSerial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      USBSerial.print("Unknow error at address 0x");
      if (address<16) {
        USBSerial.print("0");
      }
      USBSerial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    USBSerial.println("No I2C devices found\n");
  }
  else {
    USBSerial.println("done\n");
  }
  delay(5000);          
}
