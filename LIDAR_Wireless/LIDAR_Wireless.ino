#include<SoftwareSerial.h>
#include<Wire.h>

#define rxPin 2
#define txPin 3

SoftwareSerial xbee(rxPin,txPin);
int ledPin = 13;

void setup() 
{
  Serial.begin(9600);
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  xbee.begin(9600);
}

void loop() 
{

}

void receiveEvent(int howMany)
{
  digitalWrite(ledPin,HIGH);
  delay(50);
  String inData = "";
  while(Wire.available())
  {
    inData += (char)Wire.read();
  }
  Serial.println(inData);
  xbee.println(inData);
  digitalWrite(ledPin,LOW);
  delay(250);
}
