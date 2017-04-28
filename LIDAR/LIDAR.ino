#include<Wire.h>
#define ledPin 13

 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  Wire.begin(2);
  Wire.onReceive(asd);
} 

void asd()
{
  
}

void loop()
{
  
}

void receiveEvent()
{
  int value = Wire.read();
  if(value == 0)
  {
    digitalWrite(ledPin,LOW);
  }
  else
  {
    digitalWrite(ledPin,HIGH);
  }
}

