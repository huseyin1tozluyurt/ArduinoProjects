#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid="";
const char* password="";

int val;
int pin=A0;

WiFiClient client;

unsigned long myChannelNum=2605151;
const char* myWriteAPIKey="O4P1Q5J3C9UYM8UX";
void setup() {
  Serial.begin(9600);
  delay(20);
  WiFi.begin(ssid,password);
  ThingSpeak.begin(client);

}

void loop() {
  val=analogRead(pin);
  val=map(val,0,1023,0,100);
  Serial.print("Pot: ");
  Serial.println(val);  
  delay(100);
  ThingSpeak.writeField(myChannelNum,1,val,myWriteAPIKey);
  delay(200);

}
