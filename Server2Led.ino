#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = ""; // Your WiFi SSID
const char* password = ""; // Your WiFi Password

ESP8266WebServer server(80);
bool LED1status = LOW;
bool LED2status = LOW;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT); // LED 1
  pinMode(D5, OUTPUT); // LED 2

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("Wifi connected.");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/ledon1", handle_ledon1);
  server.on("/ledoff1", handle_ledoff1);
  server.on("/ledon2", handle_ledon2);
  server.on("/ledoff2", handle_ledoff2);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started.");
}

void loop() {
  server.handleClient();
  digitalWrite(D4, LED1status ? HIGH : LOW);
  digitalWrite(D5, LED2status ? HIGH : LOW);
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("LEDs: OFF");
  server.send(200, "text/html", updateWebpage(LED1status, LED2status));
}

void handle_ledon1() {
  LED1status = HIGH;
  Serial.println("LED 1: ON");
  server.send(200, "text/html", updateWebpage(LED1status, LED2status));
}

void handle_ledoff1() {
  LED1status = LOW;
  Serial.println("LED 1: OFF");
  server.send(200, "text/html", updateWebpage(LED1status, LED2status));
}

void handle_ledon2() {
  LED2status = HIGH;
  Serial.println("LED 2: ON");
  server.send(200, "text/html", updateWebpage(LED1status, LED2status));
}

void handle_ledoff2() {
  LED2status = LOW;
  Serial.println("LED 2: OFF");
  server.send(200, "text/html", updateWebpage(LED1status, LED2status));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not Found");
}

String updateWebpage(uint8_t LED1status, uint8_t LED2status) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #3498db;}\n";
  ptr += ".button-on:active {background-color: #3498db;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  ptr += "<h3>Using Access Point(AP) Mode</h3>\n";

  if (LED1status) {
    ptr += "<p>BLUE LED 1: ON</p><a class=\"button button-off\" href=\"/ledoff1\">OFF</a>\n";
  } else {
    ptr += "<p>BLUE LED 1: OFF</p><a class=\"button button-on\" href=\"/ledon1\">ON</a>\n";
  }
  
  if (LED2status) {
    ptr += "<p>BLUE LED 2: ON</p><a class=\"button button-off\" href=\"/ledoff2\">OFF</a>\n";
  } else {
    ptr += "<p>BLUE LED 2: OFF</p><a class=\"button button-on\" href=\"/ledon2\">ON</a>\n";
  }

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
