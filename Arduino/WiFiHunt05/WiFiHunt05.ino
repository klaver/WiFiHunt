#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *wifissid = "WiFiHunt05";
const char *wifipass = "martwosp";
const byte wifikanaal = 6;
const byte DNS_PORT = 53;

IPAddress apIP(10, 10, 10, 10);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width'><title>WiFiHunt05</title></head><body><h1><pre>"
  " 01000001 <br> 01001110 <br> 01010100 <br> 01010111 <br> 01001111 <br> 01001111 <br> 01010010 <br> 01000100 <br> &nbsp; <br> 01010111 </pre></h1></body></html>";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifissid, wifipass, wifikanaal);

  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
