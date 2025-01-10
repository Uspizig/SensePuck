#include "esp32-hal-gpio.h"
#include "audio_player.h"





void setup_audio(void){
   pinMode(I2S_SD, OUTPUT);
   digitalWrite(I2S_SD, HIGH);
   audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
   //audio.setVolume(4); // default 0...21
   audio.connecttohost("https://liveradio.swr.de/sw282p3/swr1bw/play.mp3"); //SWR1
  //  or alternative
    audio.setVolumeSteps(255); // max 255
    audio.setVolume(30);    
  //
  //  *** radio streams ***
  //    audio.connecttohost("http://stream.antennethueringen.de/live/aac-64/stream.antennethueringen.de/"); // aac
  //audio.connecttohost("http://mcrscast.mcr.iol.pt/cidadefm");                                         // mp3
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
      int size = 50;
      memcpy(buf2, info, size);
      strncpy(StationName, buf2 + 0, 20);
      StationName[20] = '\0';
  }
  void audio_showstreamtitle(const char *info){
      USBSerial.print("streamtitle ");USBSerial.println(info);
      int size = 50;
      memcpy(buf2, info, size);
      /*//funzt aver 1 String zuviel für meinen Geschmack
      myString.assign(info, size);
      int PositionDash = myString.find_first_of("/");
      
      if (PositionDash > 0){
        strncpy(Title, buf2 + 0, PositionDash); //zuerst wird  Title übertragen
        strncpy(Artist, buf2 + PositionDash+2, 15); //+2 weil / und leerzeichen wegsoll, 15 Zeichen nach Position Dash
        
        Artist[15] = '\0'; //NUll Terminierung
        Title[PositionDash] = '\0';

      }*/


      
      char myChar = '/';
      for (int z = 0 ; z < sizeof(buf2)-1; z ++) {
        if (buf2[z] == myChar) {
            int PositionDash = z;
            strncpy(Title, buf2 + 0, PositionDash); //zuerst wird  Title übertragen
            strncpy(Artist, buf2 + PositionDash+2, 15); //+2 weil / und leerzeichen wegsoll, 15 Zeichen nach Position Dash
        
            Artist[15] = '\0'; //NUll Terminierung
            Title[PositionDash] = '\0';
            break;//Do the work
        }
      }
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

