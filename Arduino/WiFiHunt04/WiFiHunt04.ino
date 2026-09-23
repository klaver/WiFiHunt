#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *wifissid = "WiFiHunt04";
const char *wifipass = "maspwort";
const byte wifikanaal = 1;
const byte DNS_PORT = 53;

IPAddress apIP(10, 10, 10, 10);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width'><title>WiFiHunt04</title></head><body><h5><pre>"
  "                               ,@@@,                        <br>"
  "                               @o@o@                        <br>"
  "                               @@@@@                        <br>"
  "                               '@@@'                        <br>"
  " @@@@@@@@@@@@@@@@=@@@@@@@@@@@@@@@@@@@@%                     <br>"
  " #######*=:                 '@@@@@@@@@%@@@%                 <br>"
  " ######+:.:                  @@@@@@@@@  %@@@,               <br>"
  " ####+:...:                  @@@@@@@@@    %%@@              <br>"
  " ##+::....:                  @@@@@@@@@       %@,            <br>"
  " *-::::::::                  @@@@@@@@@         %@,          <br>"
  "                             @@@@@@@@@          %@@,        <br>"
  "                             @@@@@@@@@           =+%@@      <br>"
  "                             '@@@@@@@'         =-:-##@@     <br>"
  "                              @     @         -:..-###%@@   <br>"
  "                              @     @      <-:....-#####%@S <br>"
  "                              @     @       ::....-#####**  <br>"
  "                              @     @         -:..-####*    <br>"
  "                              @     @           ::-###      <br>"
  "                              @     @             =#        <br>"
  "                             ,@     @,                      <br>"
  "                          ,@@@@     @@@@,                   <br>"
  "</pre></h5></body></html>";

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
