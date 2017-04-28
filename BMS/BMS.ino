#include<Wire.h>
#include "EEPROMRW.h"
#include <math.h>

#define TEMP_THRESHOLD 40
#define FULL_CELL_VOLTAGE 4.15
#define EMPTY_CELL_VOLTAGE 3.1
#define ThermistorPIN A0



float pad = 2200;
float thermr = 10000;  

int led = 13;

int r1 = 5;
int r2 = 6;
int r3 = 7;
int r4 = 8;
int r5 = 9;
;

float b1,b2,b3;
float temp;

bool canUse = false;
bool override_charge = false;
bool override_discharge = false;
bool overriden = false;

bool state = false;
int ROM_state = 0;

int packMode = 0; // 0 = parallel, 1 = series

void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  Wire.begin(3);
  Wire.onRequest(sendData);
  for(int i=5;i<10;i++)
  {
    pinMode(i,OUTPUT);
  }
  for(int i=0;i<10;i++)
  {
    digitalWrite(led,HIGH);
    delay(i*10);
    digitalWrite(led,LOW);
    delay(i*10);
  }
  EEPROM_read(0,ROM_state);
  Serial.println(ROM_state);
  if(ROM_state == 0)
  {
   // digitalWrite(led,HIGH);
   // state = false;
  }
  else
  {
    state = true;
    testPack();
  }
}

void testPack()
{
  getVoltage();
  if(b1 > EMPTY_CELL_VOLTAGE && b2 > EMPTY_CELL_VOLTAGE && b3 > EMPTY_CELL_VOLTAGE)
  {
    digitalWrite(led,HIGH);
    for(int i=5;i<10;i++)
    {
      digitalWrite(i,HIGH);
    }
    digitalWrite(led,LOW);
    canUse = true;
    packMode = 1;
  }
  else
  {
    digitalWrite(led,HIGH);
    for(int i=5;i<10;i++)
    {
      digitalWrite(i,LOW);
    }
    digitalWrite(led,HIGH);
    canUse = false;
    packMode = 0;
    state = false;
    EEPROM_write(0,0);
  }
}

void runCheck()
{
  getVoltage();
  if(b1 < EMPTY_CELL_VOLTAGE * 3 && b2 < EMPTY_CELL_VOLTAGE * 2 && b3 < EMPTY_CELL_VOLTAGE)
  {
    canUse = false;
    overriden = false;
    packMode = 0;
    state = false;
    EEPROM_write(0,0);
    digitalWrite(led,HIGH);
    for(int i=5;i<10;i++)
    {
      digitalWrite(i,LOW);
    }
    digitalWrite(led,HIGH);
  }
}

void chargeCheck()
{
  getVoltage();
  if(b1 >= FULL_CELL_VOLTAGE && b2 >= FULL_CELL_VOLTAGE && b3 >= FULL_CELL_VOLTAGE)
  {
    canUse = true;
    overriden = false;
    packMode = 1;
    state = true;
    EEPROM_write(0,1);
    digitalWrite(led,HIGH);
    for(int i=5;i<10;i++)
    {
      digitalWrite(i,HIGH);
    }
    digitalWrite(led,LOW);
  }
}

void loop()
{
  printVoltage();
  temp=Thermistor(analogRead(ThermistorPIN));
  if(temp > TEMP_THRESHOLD)
  {
    if(canUse && state == true)
    {
      runCheck();
    }
    else
    {
      chargeCheck();
    }
  }
  else
  {
    for(int i=5;i<10;i++)
    {
      digitalWrite(i,LOW);
    }
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
  }
  delay(150);
}

void getVoltage()
{
  b1 = getVoltage(A3);
  b2 = getVoltage(A2);
  b3 = getVoltage(A1);
}

void printVoltage()
{
  getVoltage();
  String line = doubleToString(b1,2) +","+doubleToString(b2,2)+","+doubleToString(b3,2)+","+packMode+","+canUse+","+state+","+doubleToString(temp,2);
  Serial.println(line);
}

void sendData()
{
  digitalWrite(led,HIGH);
  getVoltage();
  String line = doubleToString(b1,2) +","+doubleToString(b2,2)+","+doubleToString(b3,2)+","+packMode+","+canUse+","+state;
  Wire.print(line);
  digitalWrite(led,LOW);
}

String doubleToString(double input,int decimalPlaces)
{
  if(decimalPlaces!=0)
  {
    String string = String((int)(input*pow(10,decimalPlaces)));
    if(abs(input)<1)
    {
      if(input>0)
        string = "0"+string;
      else if(input<0)
        string = string.substring(0,1)+"0"+string.substring(1);
    }
    return string.substring(0,string.length()-decimalPlaces)+"."+string.substring(string.length()-decimalPlaces);
  }
  else 
  {
    return String((int)input);
  }
}

float Thermistor(int RawADC) 
{
  long Resistance;  
  float Temp;  
  Resistance=pad*((1024.0 / RawADC) - 1); 
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;                   
  return Temp;
}

float getVoltage(int option)
{
  int value = 0;
  double vout = 0;
  double vin = 0;
  for(int i=1;i<=25;i++)
  {
    value += analogRead(option);
  }
  value = value / 25.0;
  vout = value * 1.1 / 1024.0;
  vin = (vout / 0.5942028986); 
  //vin = (vout / 0.09090909091) ; 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}
