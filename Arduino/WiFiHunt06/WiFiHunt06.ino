#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

const char *wifissid = "WiFiHunt06";
const char *wifipass = "maspwort";
const byte wifikanaal = 11;
const byte DNS_PORT = 53;

IPAddress apIP(10, 10, 10, 10);
ESP8266WebServer webServer(80);
DNSServer dnsServer;

String responseHTML = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width'><title>WiFiHunt06</title></head><body><h1><pre>"
  " Wat is de uitkomst? <br> &nbsp; <br> <img src='schakeling.png' width='295' height='156' alt='schakeling' border='0'>"
  " <br> &nbsp; <br> Antwoord: <br> O: 0 <br> P: 1 <br> S: ERROR</pre></h1></body></html>";

String getContentType(String filename) {
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  return "text/plain";
}

bool handleFileRead(String path) {
  String contentType = getContentType(path);
  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    webServer.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifissid, wifipass, wifikanaal);

  dnsServer.start(DNS_PORT, "*", apIP);
  
  LittleFS.begin();

  webServer.onNotFound([]() {
    if (!handleFileRead(webServer.uri())) {
        webServer.send(200, "text/html", responseHTML);
    }
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
