#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *wifissid = "WiFiHunt02";
const char *wifipass = "mostwarp";
const byte wifikanaal = 6;
const byte DNS_PORT = 53;

IPAddress apIP(10, 10, 10, 10);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width'><title>WiFiHunt02</title></head><body><h1><pre>"
  " Op QTH locatie: <br> Julliet <br> Oscar <br> Twee <br> Een <br> Hotel <br> Victor <br> Drie <br> Een <br> &nbsp; <br>"
  " Vind je: <br> A: Clubhuis <br> B: Gemeentehuis <br> C: Politiebureau </pre></h1></body></html>";

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
