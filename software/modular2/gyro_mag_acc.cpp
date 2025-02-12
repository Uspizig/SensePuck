#include "gyro_mag_acc.h"
#include "global.h"
#include "io_pins.h"
#include <LIS3MDL.h>
#include <LSM6.h>

LIS3MDL mag;
LSM6 imu;
char report[90];

/*
Calibration values; the default values of +/-32767 for each axis
lead to an assumed magnetometer bias of 0. Use the Calibrate example
program to determine appropriate values for your particular unit.
*/
LIS3MDL::vector<int16_t> m_min = { -5766,  -4453,  -5963};
LIS3MDL::vector<int16_t> m_max = { +6458,  +2186,  +4912};


void gyro_mag_setup(void){
 if (!mag.init())
  {
    USBSerial.println("Failed to detect and initialize LIS3MDL magnetometer!");
    while (1);
  }
  mag.enableDefault();

  if (!imu.init())
  {
    USBSerial.println("Failed to detect and initialize LSM6 IMU!");
    while (1);
  }
  imu.enableDefault();

   
}

void calculate_heading(void){
  mag.read();
  imu.read();
  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d",
    imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z);

  /*
  When given no arguments, the heading() function returns the angular
  difference in the horizontal plane between a default vector (the
  +X axis) and north, in degrees.
  */
  float heading = computeHeading();

  /*
  To use a different vector as a reference, use the version of
  computeHeading() that takes a vector argument; for example, call it like this
  to use the -Z axis as a reference:
  */
  //float heading = computeHeading((LIS3MDL::vector<int>){0, 0, -1});

  
  /*snprintf(report, sizeof(report), "H: %6d A: %6d %6d %6d    G: %6d %6d %6d",
    heading, imu.a.x, imu.a.y, imu.a.z,
    imu.g.x, imu.g.y, imu.g.z);*/
  USBSerial.print(report);
  USBSerial.print(" H: ");
  USBSerial.println(heading);


}


/*
Returns the angular difference in the horizontal plane between the
"from" vector and north, in degrees.

Description of heading algorithm:
Shift and scale the magnetic reading based on calibration data to find
the North vector. Use the acceleration readings to determine the Up
vector (gravity is measured as an upward acceleration). The cross
product of North and Up vectors is East. The vectors East and North
form a basis for the horizontal plane. The From vector is projected
into the horizontal plane and the angle between the projected vector
and horizontal north is returned.
*/
template <typename T> float computeHeading(LIS3MDL::vector<T> from)
{
  LIS3MDL::vector<int32_t> temp_m = {mag.m.x, mag.m.y, mag.m.z};

  // copy acceleration readings from LSM6::vector into an LIS3MDL::vector
  LIS3MDL::vector<int16_t> a = {imu.a.x, imu.a.y, imu.a.z};

  // subtract offset (average of min and max) from magnetometer readings
  temp_m.x -= ((int32_t)m_min.x + m_max.x) / 2;
  temp_m.y -= ((int32_t)m_min.y + m_max.y) / 2;
  temp_m.z -= ((int32_t)m_min.z + m_max.z) / 2;

  // compute E and N
  LIS3MDL::vector<float> E;
  LIS3MDL::vector<float> N;
  LIS3MDL::vector_cross(&temp_m, &a, &E);
  LIS3MDL::vector_normalize(&E);
  LIS3MDL::vector_cross(&a, &E, &N);
  LIS3MDL::vector_normalize(&N);

  // compute heading
  float heading = atan2(LIS3MDL::vector_dot(&E, &from), LIS3MDL::vector_dot(&N, &from)) * 180 / PI;
  if (heading < 0) heading += 360;
  return heading;
}

/*
Returns the angular difference in the horizontal plane between a
default vector (the +X axis) and north, in degrees.
*/
float computeHeading(void)
{
  return computeHeading((LIS3MDL::vector<int>){1, 0, 0});
}
