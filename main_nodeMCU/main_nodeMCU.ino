#include "ThingSpeak.h" //Header file for communicating with ThingSpeak


/* Header file for using NodeMCU's WiFi module.
   This needs to be installed separately:
   https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/ */
#include <ESP8266WiFi.h>


//Internet connection details
const char ssid[] = "WiFi name"; //SSID
const char pass[] = "WiFi password"; // Password


//These are the pins that receive digital values from Arduino UNO, one for each streetlight.
const int pin0 = D0;
const int pin1 = D1;
const int pin2 = D2;
const int pin3 = D3;


WiFiClient client; //an instance of WiFiClient
unsigned long myChannelField = 0000000; // Put your ThingSpeak Channel's ID here
const char* myWriteAPIKey = "XXXXXXXXXXXXXXXX"; // Write-API Key of the ThingSpeak channel
void setup(){
  Serial.begin(9600);


  //Set INPUT pins
  pinMode(pin0,INPUT);
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  pinMode(pin3,INPUT);
  WiFi.mode(WIFI_STA);


  //connect to WiFi
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
  ThingSpeak.begin(client); //establish connection with ThingSpeak
}
void loop(){
  /* Send values received via INPUT pins to the corresponding field on the ThingSpeak cloud
      Syntax:
      ThingSpeak.writeField(Channel_ID, Field_Number, Value_to_be_Sent, Write_API_Key) */
  ThingSpeak.writeField(myChannelField, 1, digitalRead(pin0), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 2, digitalRead(pin1), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 3, digitalRead(pin2), myWriteAPIKey);
  ThingSpeak.writeField(myChannelField, 4, digitalRead(pin3), myWriteAPIKey);
  delay(1000);
}
