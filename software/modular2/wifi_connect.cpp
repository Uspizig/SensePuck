#include <wifi_connect.h>
#include <global.h>
#include <io_pins.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPDash.h>

uint8_t counter = 0;



void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  USBSerial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED && counter < 20) {
    USBSerial.print('.');
    delay(200);
  }
  USBSerial.println(WiFi.localIP());
  USBSerial.print("RRSI: ");
  USBSerial.println(WiFi.RSSI());
}