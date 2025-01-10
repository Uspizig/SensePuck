#include "WString.h"
#include "RTCtimekeeper.h"
#include "global.h"
#include "io_pins.h"

void RTC_Setup(void){


 if (! rtc.begin()) {
    delay(500);
    USBSerial.println("Couldn't find RTC");
 }
 else{
   USBSerial.println("RTC found");
   if (rtc.lostPower()) {
    USBSerial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    rtc.start();
  }
 }
  
}

void RTC_time_formatter(void){
    //rtc.refresh();
    
    
    //USBSerial.println(now.toString(TimeAktuell));
}


void RTC_time_date_formatter(void){
      //rtc.refresh();
      //DateTime now = rtc.now();
      //USBSerial.println(now.toString(dateBuf));
}