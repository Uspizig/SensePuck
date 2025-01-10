#define mySSID "XXXXXXXX"
#define myPASSWORD "xxxxxx"


#define mqtt_client_on
#define rotary1

#ifdef rotary1
    #define ANZAHL_LEDS 1 
    #define RGB_LED_DATA_PIN 16
    
    #define RXD2 35
    #define TXD2 33
    
    #define ROTARY_ENCODER_A_PIN 41
    #define ROTARY_ENCODER_B_PIN 15
    #define ROTARY_ENCODER_BUTTON_PIN 38
    #define LED_PIN 16
    
    #define BUTTON_DISABLED 0
    #define BUTTON_ENABLED 1
    #define timeSeconds 200
    #define updaterate_leds 2000
    #define max_counter 255
    #define min_counter 0
#endif

