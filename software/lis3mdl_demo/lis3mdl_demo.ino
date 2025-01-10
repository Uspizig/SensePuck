// Basic demo for magnetometer readings from Adafruit LIS3MDL

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#define SDA2 17
#define SCL2 8
#include "USB.h"

USBCDC USBSerial;

Adafruit_LIS3MDL lis3mdl;
#define LIS3MDL_CLK 13
#define LIS3MDL_MISO 12
#define LIS3MDL_MOSI 11
#define LIS3MDL_CS 10

void setup(void) {
  delay(2000);
  USBSerial.begin(115200);USB.begin();
  delay(2000);
  
  Wire.begin(SDA2,SCL2);
  USBSerial.println("Adafruit LIS3MDL test!");
  
  // Try to initialize!
  if (! lis3mdl.begin_I2C(0x1E)) {          // hardware I2C mode, can pass in address & alt Wire
  //if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
  //if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
    USBSerial.println("Failed to find LIS3MDL chip");
    while (1) { delay(10); }
  }
  USBSerial.println("LIS3MDL Found!");

  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  USBSerial.print("Performance mode set to: ");
  switch (lis3mdl.getPerformanceMode()) {
    case LIS3MDL_LOWPOWERMODE: USBSerial.println("Low"); break;
    case LIS3MDL_MEDIUMMODE: USBSerial.println("Medium"); break;
    case LIS3MDL_HIGHMODE: USBSerial.println("High"); break;
    case LIS3MDL_ULTRAHIGHMODE: USBSerial.println("Ultra-High"); break;
  }

  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  USBSerial.print("Operation mode set to: ");
  // Single shot mode will complete conversion and go into power down
  switch (lis3mdl.getOperationMode()) {
    case LIS3MDL_CONTINUOUSMODE: USBSerial.println("Continuous"); break;
    case LIS3MDL_SINGLEMODE: USBSerial.println("Single mode"); break;
    case LIS3MDL_POWERDOWNMODE: USBSerial.println("Power-down"); break;
  }

  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
  // You can check the datarate by looking at the frequency of the DRDY pin
  USBSerial.print("Data rate set to: ");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_0_625_HZ: USBSerial.println("0.625 Hz"); break;
    case LIS3MDL_DATARATE_1_25_HZ: USBSerial.println("1.25 Hz"); break;
    case LIS3MDL_DATARATE_2_5_HZ: USBSerial.println("2.5 Hz"); break;
    case LIS3MDL_DATARATE_5_HZ: USBSerial.println("5 Hz"); break;
    case LIS3MDL_DATARATE_10_HZ: USBSerial.println("10 Hz"); break;
    case LIS3MDL_DATARATE_20_HZ: USBSerial.println("20 Hz"); break;
    case LIS3MDL_DATARATE_40_HZ: USBSerial.println("40 Hz"); break;
    case LIS3MDL_DATARATE_80_HZ: USBSerial.println("80 Hz"); break;
    case LIS3MDL_DATARATE_155_HZ: USBSerial.println("155 Hz"); break;
    case LIS3MDL_DATARATE_300_HZ: USBSerial.println("300 Hz"); break;
    case LIS3MDL_DATARATE_560_HZ: USBSerial.println("560 Hz"); break;
    case LIS3MDL_DATARATE_1000_HZ: USBSerial.println("1000 Hz"); break;
  }
  
  lis3mdl.setRange(LIS3MDL_RANGE_4_GAUSS);
  USBSerial.print("Range set to: ");
  switch (lis3mdl.getRange()) {
    case LIS3MDL_RANGE_4_GAUSS: USBSerial.println("+-4 gauss"); break;
    case LIS3MDL_RANGE_8_GAUSS: USBSerial.println("+-8 gauss"); break;
    case LIS3MDL_RANGE_12_GAUSS: USBSerial.println("+-12 gauss"); break;
    case LIS3MDL_RANGE_16_GAUSS: USBSerial.println("+-16 gauss"); break;
  }

  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true, // enable z axis
                          true, // polarity
                          false, // don't latch
                          true); // enabled!
}

void loop() {
  lis3mdl.read();      // get X Y and Z data at once
  // Then print out the raw data
  USBSerial.print("\nX:  "); USBSerial.print(lis3mdl.x); 
  USBSerial.print("  \tY:  "); USBSerial.print(lis3mdl.y); 
  USBSerial.print("  \tZ:  "); USBSerial.println(lis3mdl.z); 

  /* Or....get a new sensor event, normalized to uTesla */
  sensors_event_t event; 
  lis3mdl.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  USBSerial.print("\tX: "); USBSerial.print(event.magnetic.x);
  USBSerial.print(" \tY: "); USBSerial.print(event.magnetic.y); 
  USBSerial.print(" \tZ: "); USBSerial.print(event.magnetic.z); 
  USBSerial.println(" uTesla ");

  delay(100); 
  USBSerial.println();
}