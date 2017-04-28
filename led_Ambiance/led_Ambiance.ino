#include<EEPROM.h>

int ch1_1 = 3;//r
int ch1_2 = 5;//g
int ch1_3 = 6;//b

int ch2_1 = 9;//r
int ch2_2 = 11;//g
int ch2_3 = 10;//b

int rVal1=255,bVal1=255,gVal1=255,rVal2=255,bVal2=255,gVal2=255;
void setup()
{
  Serial.begin(9600);
  pinMode(ch1_1,OUTPUT);
  pinMode(ch1_2,OUTPUT);
  pinMode(ch1_3,OUTPUT);
  //
  pinMode(ch2_1,OUTPUT);
  pinMode(ch2_2,OUTPUT);
  pinMode(ch2_3,OUTPUT);
  
  analogWrite(ch1_1,rVal1);
  analogWrite(ch1_2,gVal1);
  analogWrite(ch1_3,bVal1);
  
  analogWrite(ch2_1,rVal2);
  analogWrite(ch2_2,gVal2);
  analogWrite(ch2_3,bVal2);
  
}

//111 111 111 111 111 111 
//012 345 678 901 234 567

// 1 2 3
// r g b

//ch color value
//1   1    222
void loop()
{
  int i=0;
  int ch[18];
  while(Serial.available() == 0);
  while(Serial.available())
  {
  delay(10);
  ch[i] = Serial.read() - '0';
  i++;
  }
  process(ch);
}



int reverseVoltage(int voltage)
{
  return 255 - voltage;
}


int EEPROM_read()
{
  int addr = 0;
  int arr[18];
  byte datasize = EEPROM.read(addr++);
  for (int i=1;i<datasize; i++) 
   {
      arr[i] =EEPROM.read(addr++);
   }
   return *arr;
}


void EEPROM_write(int *data, byte datasize) 
{
   int addr = 0;
   EEPROM_erase();
   EEPROM.write(addr++, datasize);
   for (int i=0; i<datasize; i++) 
   {
      EEPROM.write(addr++, data[i]);
   }
}

void EEPROM_erase()
{
  for(int i = 0;i<512;i++)
  {
    EEPROM.write(i,0);
  }
}
//1111111111111111


//11222


void process(int *param)
{
  int r1val = param[0]*100 + param[1]*10 + param[2];
  int g1val = param[3]*100 + param[4]*10 + param[5];
  int b1val = param[6]*100 + param[7]*10 + param[8];
  
  int r2val = param[9]*100 + param[10]*10 + param[11];
  int g2val = param[12]*100 + param[13]*10 + param[14];
  int b2val = param[15]*100 + param[16]*10 + param[17];
//  EEPROM_write(param,18);
  LEDs_PWM(r1val,g1val,b1val,r2val,g2val,b2val);
}


void LEDs_PWM(int r1,int g1,int b1,int r2,int g2,int b2)
{
  analogWrite(ch1_1,reverseVoltage(r1));
  analogWrite(ch1_2,reverseVoltage(g1));
  analogWrite(ch1_3,reverseVoltage(b1));
  analogWrite(ch2_1,reverseVoltage(r2));
  analogWrite(ch2_2,reverseVoltage(g2));
  analogWrite(ch2_3,reverseVoltage(b2));
}

