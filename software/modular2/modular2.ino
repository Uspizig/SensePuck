#include "io_pins.h"
#include "Arduino.h"
#include "WiFi.h"
#include "audio_player.h"
#include "leds.h"
#include "global.h"
#include "sd_card.h"
#include "TFTDisplay.h"
#include "wifi_connect.h"
#include "USB.h"
#include "Wire.h"
#include "RTCtimekeeper.h"
#include "Touch.h"
#include "Rotary.h"
#include "gyro_mag_acc.h"

uint8_t inc = 0;
uint8_t col = 0;
uint8_t sek = 0;

// Digital I/O used

//Touch fehlt
//LSM auslesen fehlt
//LIS auslesen fehlt



void setup() {
    delay(2000);
    USBSerial.begin(115200);USB.begin();
    delay(2000);
    Wire.begin(SDA2 ,SCL2);
    RTC_Setup();
    now = rtc.now(); //frisst speicher in loop deshalb hier

    initWiFi();//Wifi muss vor Audio
    tft_start(); 
    //SD_Card_setup(); //Blockiert das Display
    
    setup_audio();
    //tft_tester();
    touch_init();
    previousMillisDisplay = millis();
    previousMillisUHR = millis();
    previousMillisAudioInfo = millis();
    rotary_setup();
    gyro_mag_setup();
// 
}

void loop(){
    rotary_loop();
    if (chsc6x_is_pressed()){
      chsc6x_get_xy();
    }
    audio.loop();
    vTaskDelay(1);
    currentMillis = millis();
    //now = rtc.now();//frisst speicher ohne ende
    
    if(currentMillis - previousMillisDisplay > update_rate_display) {
     //USBSerial.println("Update Display");
     previousMillisDisplay = currentMillis;   
     //TFTDisplay_Hello(20, 50);
     
     sek = now.second();
      //sek = (millis() / 1000) % 60;//funzt
      fillArc(120, 120, sek*6, 1, 120, 120, 10, rainbow(col)); //Zeigt Uhr Animantion an
      inc++;
      if (inc > 59){ inc = 0; col++; }//*Display_BlackScreen();}
      if (col > 191) col = 0;
      //RTC_time_formatter();
      TFTDisplay_MeasurementResults(50,19); // Displays the value Temp_Sensor_ReadOut to the TFT Display*/
      TFTDisplay_TouchCoordinates(50,180);
      calculate_heading();
    }

    
    if(currentMillis - previousMillisUHR > update_rate_UHR) {
      previousMillisUHR = currentMillis; 
      now = rtc.now();
      
    }

    if(currentMillis - previousMillisAudioInfo > update_rate_AudioInfo) {
      previousMillisAudioInfo = currentMillis; 
      TFT_ArtistTitle(20, 90);
      TFT_StationName(25, 150);
    }
    
}


