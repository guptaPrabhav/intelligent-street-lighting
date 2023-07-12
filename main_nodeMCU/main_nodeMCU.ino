#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

const char ssid[] = "Hotspot/WiFi Name"; //SSID
const char pass[] = "Hotspot/WiFi Password"; // Password
const int pin0 = D0;
const int pin1 = D1;
const int pin2 = D2;
const int pin3 = D3;

WiFiClient client;
unsigned long myChannelField = 2216371; // Channel ID

const char* myWriteAPIKey = "0WY385VU8D9I04FH"; // Write-API Key

void setup(){
  Serial.begin(9600);
  pinMode(pin0,INPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void loop(){
  
  ThingSpeak.writeField(myChannelField, 1, digitalRead(pin0), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 2, digitalRead(pin1), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 3, digitalRead(pin2), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 4, digitalRead(pin3), myWriteAPIKey);
  delay(1000);
}