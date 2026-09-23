#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *wifissid = "WiFiHunt08";
const char *wifipass = "marpwost";
const byte wifikanaal = 6;
const byte DNS_PORT = 53;

IPAddress apIP(10, 10, 10, 10);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width'><title>WiFiHunt08</title></head><body><h1><pre>"
  " Na QTH volgt: <br> &nbsp; <br> K: een stationsnaam <br> L: een frequentie <br> M: een locatie </pre></h1></body></html>";

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
