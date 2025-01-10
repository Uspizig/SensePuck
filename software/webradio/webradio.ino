#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

#define SDA2 17
#define SCL2 8
#include "USB.h"

USBCDC USBSerial;
// Digital I/O used
#define SD_CS         48
#define SPI_MOSI      11
#define SPI_MISO      13
#define SPI_SCK       12
#define I2S_DOUT      37
#define I2S_BCLK      36
#define I2S_LRC       35
#define I2S_SD        42

Audio audio;

String ssid =     "XXXXXXXXX";
String password = "xxxxxxxxx";

void setup() {
    delay(2000);
    USBSerial.begin(115200);USB.begin();
    delay(2000);
  
    //Wire.begin(SDA2,SCL2);
    pinMode(SD_CS, OUTPUT);      digitalWrite(SD_CS, HIGH);
    
    //SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    pinMode(I2S_SD, OUTPUT);      digitalWrite(I2S_SD, HIGH);
    USBSerial.begin(115200);
    SD.begin(SD_CS);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    
    audio.setVolume(4); // default 0...21
//  or alternative
//  audio.setVolumeSteps(64); // max 255
//  audio.setVolume(63);    
//
//  *** radio streams ***
//    audio.connecttohost("http://stream.antennethueringen.de/live/aac-64/stream.antennethueringen.de/"); // aac
//audio.connecttohost("http://mcrscast.mcr.iol.pt/cidadefm");                                         // mp3
audio.connecttohost("https://liveradio.swr.de/sw282p3/swr1bw/play.mp3"); //SWR1
//  audio.connecttohost("http://www.wdr.de/wdrlive/media/einslive.m3u");                                // m3u
//  audio.connecttohost("https://stream.srg-ssr.ch/rsp/aacp_48.asx");                                   // asx
//  audio.connecttohost("http://tuner.classical102.com/listen.pls");                                    // pls
//  audio.connecttohost("http://stream.radioparadise.com/flac");                                        // flac
//  audio.connecttohost("http://stream.sing-sing-bis.org:8000/singsingFlac");                           // flac (ogg)
//  audio.connecttohost("http://s1.knixx.fm:5347/dein_webradio_vbr.opus");                              // opus (ogg)
//  audio.connecttohost("http://stream2.dancewave.online:8080/dance.ogg");                              // vorbis (ogg)
//  audio.connecttohost("http://26373.live.streamtheworld.com:3690/XHQQ_FMAAC/HLSTS/playlist.m3u8");    // HLS
//  audio.connecttohost("http://eldoradolive02.akamaized.net/hls/live/2043453/eldorado/master.m3u8");   // HLS (ts)
//  *** web files ***
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Pink-Panther.wav");        // wav
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Santiano-Wellerman.flac"); // flac
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Olsen-Banden.mp3");        // mp3
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Miss-Marple.m4a");         // m4a (aac)
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/Collide.ogg");             // vorbis
//  audio.connecttohost("https://github.com/schreibfaul1/ESP32-audioI2S/raw/master/additional_info/Testfiles/sample.opus");             // opus
//  *** local files ***
//  audio.connecttoFS(SD, "/test.wav");     // SD
//  audio.connecttoFS(SD_MMC, "/test.wav"); // SD_MMC
//  audio.connecttoFS(SPIFFS, "/test.wav"); // SPIFFS

//  audio.connecttospeech("Wenn die Hunde schlafen, kann der Wolf gut Schafe stehlen.", "de"); // Google TTS
}

void loop(){
    audio.loop();
    vTaskDelay(1);
}

// optional
void audio_info(const char *info){
    USBSerial.print("info        "); USBSerial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    USBSerial.print("id3data     ");USBSerial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    USBSerial.print("eof_mp3     ");USBSerial.println(info);
}
void audio_showstation(const char *info){
    USBSerial.print("station     ");USBSerial.println(info);
}
void audio_showstreamtitle(const char *info){
    USBSerial.print("streamtitle ");USBSerial.println(info);
}
void audio_bitrate(const char *info){
    USBSerial.print("bitrate     ");USBSerial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    USBSerial.print("commercial  ");USBSerial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    USBSerial.print("icyurl      ");USBSerial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    USBSerial.print("lasthost    ");USBSerial.println(info);
}
void audio_eof_speech(const char *info){
    USBSerial.print("eof_speech  ");USBSerial.println(info);
}
