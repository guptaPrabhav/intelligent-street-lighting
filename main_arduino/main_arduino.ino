#include <SoftwareSerial.h>

const int nodepin0 = 4;
const int nodepin1 = 7;
const int nodepin2 = 8;
const int nodepin3 = 12;

const int LEDpin1 = 3;
const int LEDpin2 = 9;
const int LEDpin3 = 10;
const int LEDpin4 = 11;  
const int photoPIN1 = A0;  
const int photoPIN2 = A1;
const int photoPIN3 = A2;
const int photoPIN4 = A3;

const int threshold_light = 70;
const int subtractor = 150;
const int multiplier = 1.8;
const int max_ambient = 250;

const int ratio = 3;
        
void setup() {  
  // initializing the serial communication:  
  Serial.begin(9600); 
  delay(2000);
  pinMode(photoPIN1, INPUT);  
  pinMode(photoPIN2, INPUT); 
  pinMode(photoPIN3, INPUT); 
  pinMode(photoPIN4, INPUT); 
  pinMode(LEDpin1, OUTPUT);  
  pinMode(LEDpin2, OUTPUT);
  pinMode(LEDpin3, OUTPUT);
  pinMode(LEDpin4, OUTPUT);
  pinMode(nodepin0,OUTPUT);
  pinMode(nodepin1,OUTPUT);
  pinMode(nodepin2,OUTPUT);
  pinMode(nodepin3,OUTPUT);
  Serial.println("START");
}

void loop() {
  Serial.println("----------");
  int sensorStatus1 = analogRead(photoPIN1);
  int sensorStatus2 = analogRead(photoPIN2);
  int sensorStatus3 = analogRead(photoPIN3);
  int sensorStatus4 = analogRead(photoPIN4);

  float ambient_light1 = ((sensorStatus1/ratio)-subtractor)*multiplier;
  float ambient_light2 = ((sensorStatus2/ratio)-subtractor)*multiplier;
  float ambient_light3 = ((sensorStatus3/ratio)-subtractor)*multiplier;
  float ambient_light4 = ((sensorStatus4/ratio)-subtractor)*multiplier;

  float LED_light1 = max_ambient - ambient_light1;
  float LED_light2 = max_ambient - ambient_light2;
  float LED_light3 = max_ambient - ambient_light3;
  float LED_light4 = max_ambient - ambient_light4;

  if(ambient_light1 > threshold_light){
    analogWrite(LEDpin1,0);
    digitalWrite(nodepin0,0);
  }
  else{
    analogWrite(LEDpin1, LED_light1);
    digitalWrite(nodepin0,1);
  }

  if (ambient_light2 > threshold_light){
    analogWrite(LEDpin2, 0); //turn off the LED
    digitalWrite(nodepin1,0);
  }
  else{
    analogWrite(LEDpin2, LED_light2);
    digitalWrite(nodepin1,1);
  }

  if (ambient_light3 > threshold_light){
    analogWrite(LEDpin3, 0); //turn off the LED
    digitalWrite(nodepin2,0);
  }
  else{
    analogWrite(LEDpin3, LED_light3);
    digitalWrite(nodepin2,1);
  }

  if (ambient_light4 > threshold_light){
    analogWrite(LEDpin4, 0); //turn off the LED
    digitalWrite(nodepin3,0);
  }
  else{
    analogWrite(LEDpin4, LED_light4);
    digitalWrite(nodepin3,1);
  }
  Serial.println(ambient_light4);
  Serial.println(sensorStatus4);
  delay(1000);
}