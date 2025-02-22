#include <Wire.h>
#include <LIS3MDL.h>
#define SDA2 17
#define SCL2 8
#include "USB.h"

USBCDC USBSerial;
LIS3MDL mag;
LIS3MDL::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

char report[80];

void setup()
{
  delay(2000);
  USBSerial.begin(115200);USB.begin();
  delay(2000);
  
  Wire.begin(SDA2,SCL2);

  if (!mag.init())
  {
    USBSerial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }

  mag.enableDefault();
}

void loop()
{
  mag.read();

  running_min.x = min(running_min.x, mag.m.x);
  running_min.y = min(running_min.y, mag.m.y);
  running_min.z = min(running_min.z, mag.m.z);

  running_max.x = max(running_max.x, mag.m.x);
  running_max.y = max(running_max.y, mag.m.y);
  running_max.z = max(running_max.z, mag.m.z);

  snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}   max: {%+6d, %+6d, %+6d}",
    running_min.x, running_min.y, running_min.z,
    running_max.x, running_max.y, running_max.z);
  USBSerial.println(report);

  delay(100);
}
