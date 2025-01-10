#pragma once
#ifndef _GYRO_MAG_ACC_H
#define _GYRO_MAG_ACC_H
#include <Arduino.h>
#include <Wire.h>
#include "io_pins.h"
#include "global.h"
#include <LIS3MDL.h>
#include <LSM6.h>


void gyro_mag_setup(void);
void calculate_heading(void);
template <typename T> float computeHeading(LIS3MDL::vector<T> from);
float computeHeading(void);

#endif