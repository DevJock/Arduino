#include<SoftwareSerial.h>

int Vpin = 7;
SoftwareSerial xbee(2,3);

void setup()
{
  Serial.begin(9600);
  xbee.begin(9600);
  pinMode(Vpin,INPUT);
  

}

void loop() 
{
  Serial.print(getVoltage());
  Serial.println(" V");
  xbee.print(getVoltage());
  xbee.println(" V");
  delay(250);
}



float getVoltage()
{
  float R1 = 100000.0; // resistance of R1 (100K)!
  float R2 = 10000.0; // resistance of R2 (10K)!
  int value = analogRead(Vpin);
  float vout = (value * 5.0) / 1024.0; // see text
  float vin = vout / (R2/(R1+R2)); 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}
