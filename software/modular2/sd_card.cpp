#include "io_pins.h"
#include "global.h"
#include "sd_card.h"

#include "SPI.h"
#include "FS.h"
#include "SD.h"

//SD Card
SPIClass * hspi = NULL;


int SD_Card_setup(void){
  USBSerial.println("SD Card Setup started");
  pinMode(SD_SS, OUTPUT);      digitalWrite(SD_SS, HIGH);
  /*hspi = new SPIClass(HSPI); 
  hspi->begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_SS);
   if (!SD.begin(SD_SS, *hspi)) {
     SDCardAvailible = 0; 
     USBSerial.println("Card Mount Failed");
     return 0;
   }*/
   //SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SD_SS);
   if (!SD.begin(SD_SS, SPI)) {
     SDCardAvailible = 0; 
     USBSerial.println("Card Mount Failed");
     return 0;
   }
   else{
    SDCardAvailible = 1; 
    USBSerial.println(" SD Card was mounted ok");
   }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    USBSerial.println("No SD card attached");
    SDCardAvailible = 0; 
    return 0;
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
  
  return 1;
}


int SD_Append_ValuesToLogFile(void){

    //if (SDCardLoggingActive == 1){
    if (SDCardAvailible == 1 && SDCardLoggingActive == 1){
      char buf2[] = "YYMMDD-hh:mm:ss";
      USBSerial.println(now.toString(buf2));
      appendFile(SD, "/logfile.txt", buf2);
      //appendFile(SD, "/logfile.txt", dateBuf);
      for (int i = 1; i <= NUMBER_OF_SENSORS; i++){
        char output[10];
        dtostrf(Temp_Sensor_ReadOut[i], 4, 3, output); //Konvertierung FLoat to Char
        appendFile(SD, "/logfile.txt", output);
        appendFile(SD, "/logfile.txt", ",");
      }
      appendFile(SD, "/logfile.txt", "\n");
      USBSerial.println("Logfile stored");  
      return 1;
    }
    else{
      USBSerial.print(SDCardAvailible); 
      USBSerial.print(SDCardLoggingActive); 
      USBSerial.println(" Could not store Logfile"); 
      return 0;
    }
}
void sd_card_checker(void){

  //listDir(SD, "/", 0);
  //createDir(SD, "/mydir");
  //listDir(SD, "/", 0);
  //removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt", "Hello ");
  //appendFile(SD, "/hello.txt", "World!\n");
  //readFile(SD, "/hello.txt");
  //deleteFile(SD, "/foo.txt");
  //renameFile(SD, "/hello.txt", "/foo.txt");
  //readFile(SD, "/foo.txt");
  //testFileIO(SD, "/test.txt");
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
