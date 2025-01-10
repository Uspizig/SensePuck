#include "credentials.h"
#include "USB.h"

#include <Adafruit_NeoPixel.h>
USBCDC USBSerial;

int vorher_message =0;
int counter = 0;
int lastcounter=0;
int counter_last=0;
int drehregler=0;
long lastTrigger = 0;
long lastTrigger_LEDS=0;
boolean ROTARY_A_NOW = 0;
boolean ROTARY_B_NOW = 0;
boolean ROTARY_A_LAST = 0;
boolean BUTTON_CLICK = 0;





// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(ANZAHL_LEDS, RGB_LED_DATA_PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
/* nur prüfen welcher Pin zuerst veränert wurde A oder B
 *  Wenn A zuerst dann Clockwise
 *  Bei B zuerst dann Counter Clockwise
*/
/*ISR ROUTINEN */
void IRAM_ATTR rotary_movement() {
  ROTARY_A_NOW = digitalRead(ROTARY_ENCODER_A_PIN);
  ROTARY_B_NOW = digitalRead(ROTARY_ENCODER_B_PIN);
  if (ROTARY_A_NOW != ROTARY_B_NOW){// nur beim ersten voreilenden Wechsel erfassen... den zweiten Wechsel ignorieren
    if (ROTARY_A_NOW != ROTARY_A_LAST){
      //A hat sich verändert Im Uhrzeigersinn
      if (counter < max_counter)counter++;
    }
    else{
      //B hat sich zuerst verändert Gegnuhrzeigersinn
      if (counter > min_counter)counter--;
    }
  }
    
}

void IRAM_ATTR rotary_button() {
  BUTTON_CLICK = 1;  
}

/*ISR ROUTINEN ENDE */
void rotary_onButtonClick() {
    if (BUTTON_CLICK != 0){ 
      //blinky(2, 50);
      counter = 0;
      lastcounter=0;
      USBSerial.println("Button"); 
      Serial.println("Button"); 
      //LEDS_weiss();
      BUTTON_CLICK = 0; 
    }
}

void rotary_loop() {
  if (lastcounter!=counter){
    if (counter > lastcounter){
      USBSerial.print("Clockwise:"); 
      Serial.print("Clockwise:"); 
      //blinky(2, 100);
    }
    if (counter < lastcounter){
      USBSerial.print("andersRum:"); 
      Serial.print("andersRum:"); 
      //blinky(2, 100);
    }
    lastcounter = counter;
    USBSerial.println(counter);
    Serial.println(counter);
  }
}

void rotary_encoder_setup(){
  
  pinMode(ROTARY_ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_B_PIN, INPUT_PULLUP);
  pinMode(ROTARY_ENCODER_BUTTON_PIN, INPUT_PULLUP);
  

  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_A_PIN), rotary_movement, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_B_PIN), rotary_movement, FALLING);
  attachInterrupt(digitalPinToInterrupt(ROTARY_ENCODER_BUTTON_PIN), rotary_button, CHANGE);
}

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  USBSerial.begin(115200);USB.begin();
  delay(2000);
  Serial.begin(115200);
  delay(1000);
  USBSerial.print("start up ..");
  Serial.print("start up ..");
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  rotary_encoder_setup();
  lastTrigger = millis();
  for(int i=0; i<ANZAHL_LEDS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(0, 50, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  long now = millis();
  if(now - lastTrigger > (timeSeconds)){
    rotary_loop();
    rotary_onButtonClick();
    lastTrigger = millis();                              
  }
}
