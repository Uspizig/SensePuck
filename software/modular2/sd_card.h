#pragma once
#ifndef _SD_CARD_H
#define _SD_CARD_H

#include <Arduino.h>
#include "io_pins.h"
#include "global.h"

#include "SPI.h"
#include "FS.h"
#include "SD.h"

int SD_Card_setup(void);
void sd_card_checker(void);
int SD_Append_ValuesToLogFile(void);
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void createDir(fs::FS &fs, const char * path);
void removeDir(fs::FS &fs, const char * path);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void testFileIO(fs::FS &fs, const char * path);
void deleteFile(fs::FS &fs, const char * path);


#endif