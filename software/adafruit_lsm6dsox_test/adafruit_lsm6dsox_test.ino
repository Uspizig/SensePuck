// Basic demo for accelerometer & gyro readings from Adafruit
// LSM6DSOX sensor

#include <Adafruit_LSM6DSOX.h>
#define SDA2 17
#define SCL2 8
#include "USB.h"

USBCDC USBSerial;


Adafruit_LSM6DSOX sox;
void setup(void) {
  delay(2000);
  USBSerial.begin(115200);USB.begin();
  delay(2000);
  
  Wire.begin(SDA2,SCL2);
  USBSerial.println("Adafruit LSM6DSOX test!");

  if (!sox.begin_I2C(0x6A)) {
    // if (!sox.begin_SPI(LSM_CS)) {
    // if (!sox.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
     USBSerial.println("Failed to find LSM6DSOX chip");
    while (1) {
      delay(10);
    }
  }

  USBSerial.println("LSM6DSOX Found!");

  // sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
  USBSerial.print("Accelerometer range set to: ");
  switch (sox.getAccelRange()) {
  case LSM6DS_ACCEL_RANGE_2_G:
    USBSerial.println("+-2G");
    break;
  case LSM6DS_ACCEL_RANGE_4_G:
    USBSerial.println("+-4G");
    break;
  case LSM6DS_ACCEL_RANGE_8_G:
    USBSerial.println("+-8G");
    break;
  case LSM6DS_ACCEL_RANGE_16_G:
    USBSerial.println("+-16G");
    break;
  }

  // sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS );
  USBSerial.print("Gyro range set to: ");
  switch (sox.getGyroRange()) {
  case LSM6DS_GYRO_RANGE_125_DPS:
    USBSerial.println("125 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_250_DPS:
    USBSerial.println("250 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_500_DPS:
    USBSerial.println("500 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_1000_DPS:
    USBSerial.println("1000 degrees/s");
    break;
  case LSM6DS_GYRO_RANGE_2000_DPS:
    USBSerial.println("2000 degrees/s");
    break;
  case ISM330DHCX_GYRO_RANGE_4000_DPS:
    break; // unsupported range for the DSOX
  }

  // sox.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  USBSerial.print("Accelerometer data rate set to: ");
  switch (sox.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    USBSerial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    USBSerial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    USBSerial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    USBSerial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    USBSerial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    USBSerial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    USBSerial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    USBSerial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    USBSerial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    USBSerial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    USBSerial.println("6.66 KHz");
    break;
  }

  // sox.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  USBSerial.print("Gyro data rate set to: ");
  switch (sox.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    USBSerial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    USBSerial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_26_HZ:
    USBSerial.println("26 Hz");
    break;
  case LSM6DS_RATE_52_HZ:
    USBSerial.println("52 Hz");
    break;
  case LSM6DS_RATE_104_HZ:
    USBSerial.println("104 Hz");
    break;
  case LSM6DS_RATE_208_HZ:
    USBSerial.println("208 Hz");
    break;
  case LSM6DS_RATE_416_HZ:
    USBSerial.println("416 Hz");
    break;
  case LSM6DS_RATE_833_HZ:
    USBSerial.println("833 Hz");
    break;
  case LSM6DS_RATE_1_66K_HZ:
    USBSerial.println("1.66 KHz");
    break;
  case LSM6DS_RATE_3_33K_HZ:
    USBSerial.println("3.33 KHz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    USBSerial.println("6.66 KHz");
    break;
  }
}

void loop() {

  //  /* Get a new normalized sensor event */
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  USBSerial.print("\t\tTemperature ");
  USBSerial.print(temp.temperature);
  USBSerial.println(" deg C");

  /* Display the results (acceleration is measured in m/s^2) */
  USBSerial.print("\t\tAccel X: ");
  USBSerial.print(accel.acceleration.x);
  USBSerial.print(" \tY: ");
  USBSerial.print(accel.acceleration.y);
  USBSerial.print(" \tZ: ");
  USBSerial.print(accel.acceleration.z);
  USBSerial.println(" m/s^2 ");

  /* Display the results (rotation is measured in rad/s) */
  USBSerial.print("\t\tGyro X: ");
  USBSerial.print(gyro.gyro.x);
  USBSerial.print(" \tY: ");
  USBSerial.print(gyro.gyro.y);
  USBSerial.print(" \tZ: ");
  USBSerial.print(gyro.gyro.z);
  USBSerial.println(" radians/s ");
  USBSerial.println();

  delay(100);

  //  // serial plotter friendly format

  //  USBSerial.print(temp.temperature);
  //  USBSerial.print(",");

  //  USBSerial.print(accel.acceleration.x);
  //  USBSerial.print(","); USBSerial.print(accel.acceleration.y);
  //  USBSerial.print(","); USBSerial.print(accel.acceleration.z);
  //  USBSerial.print(",");

  // USBSerial.print(gyro.gyro.x);
  // USBSerial.print(","); USBSerial.print(gyro.gyro.y);
  // USBSerial.print(","); USBSerial.print(gyro.gyro.z);
  // USBSerial.println();
  //  delayMicroseconds(10000);
}