#include "LedControl.h"
#include "binary.h"

LedControl lc=LedControl(10,11,12,2);

int oldData = -1;
int cyclesPerSecond = 979;

//pins
int clockInterrupt = 0; //interrupt 0 is pin 2 on UNO
int pwmOut = 6; //pin 6

//timekeeping
int seconds = 0;
int minutes = 0;
int hours = 0;
int masterClock = 0;//number of square waves



int digits[10][8]={
                   {B0110,
                    B1001,
                    B1001,
                    B1001,
                    B1001,
                    B1001,
                    B1001,
                    B0110},
                   {B0110,
                    B1010,
                    B0010,
                    B0010,
                    B0010,
                    B0010,
                    B0010,
                    B1111},
                   {B0110,
                    B1001,
                    B0001,
                    B0001,
                    B0010,
                    B0100,
                    B1000,
                    B1111},
                   {B0110,
                    B1001,
                    B0010,
                    B0100,
                    B0100,
                    B0010,
                    B1001,
                    B0110},
                   {B1000,
                    B1000,
                    B1010,
                    B1111,
                    B0010,
                    B0010,
                    B0010,
                    B0010},
                   {B1111,
                    B1000,
                    B1000,
                    B1110,
                    B0001,
                    B0001,
                    B0010,
                    B1100},
                   {B0011,
                    B0100,
                    B1000,
                    B1110,
                    B1001,
                    B1001,
                    B1001,
                    B0110},
                   {B1111,
                    B0001,
                    B0010,
                    B0010,
                    B0100,
                    B0100,
                    B1000,
                    B1000},
                   {B0110,
                    B1001,
                    B1001,
                    B0110,
                    B0110,
                    B1001,
                    B1001,
                    B0110},
                   {B0110,
                    B1001,
                    B1001,
                    B0111,
                    B0001,
                    B0001,
                    B0010,
                    B0100}
                  };

int alphabets[26][4] = {
                        {B0110,
                         B1001,
                         B1111,
                         B1001},
                        {B1110,
                         B1010,
                         B1010,
                         B1110},
                        {B0111,
                         B1000,
                         B1000,
                         B0111},
                        {B1110,
                         B1001,
                         B1001,
                         B1110},
                        {B1111,
                         B1100,
                         B1100,
                         B1111},
                        {B1111,
                         B1100,
                         B1100,
                         B1000},
                        {B0111,
                         B1000,
                         B1011,
                         B0111},
                        {B1001,
                         B1111,
                         B1111,
                         B1001},
                        {B1111,
                         B0100,
                         B010,
                         B1111},
                        {B1111,
                         B0010,
                         B1010,
                         B0110},
                        {B1010,
                         B1100,
                         B1100,
                         B1010},
                        {B1000,
                         B1000,
                         B1000,
                         B1111},
                        {B1001,
                         B1111,
                         B1001,
                         B1001},
                        {B1001,
                         B1101,
                         B1011,
                         B1001},
                        {B0110,
                         B1001,
                         B1001,
                         B0110},
                        {B1111,
                         B1001,
                         B1110,
                         B1000},
                        {B0110,
                         B1001,
                         B1011,
                         B0111},
                        {B1111,
                         B1010,
                         B1010,
                         B1001},
                        {B0111,
                         B1000,
                         B0100,
                         B0111},
                        {B1111,
                         B0100,
                         B0100,
                         B0100},
                        {B1001,
                         B1001,
                         B1001,
                         B1111},
                        {B1001,
                         B1001,
                         B1001,
                         B0110},
                        {B1001,
                         B1001,
                         B1111,
                         B1001},
                        {B1001,
                         B0110,
                         B0110,
                         B1001},
                        {B1001,
                         B0110,
                         B0100,
                         B1000},
                        {B1111,
                         B0010,
                         B0100,
                         B1111}};

void setup()
{
  Serial.begin(9600);
  attachInterrupt(clockInterrupt, clockCounter, RISING);
  delay(2000);
  analogReference(DEFAULT);
  Serial.println(pwmOut);
  analogWrite(pwmOut, 127);
  for(int i =0;i<2;i++)
  {
    lc.shutdown(i,false);
    lc.setIntensity(i,1);
    lc.clearDisplay(i);
  }
}


void clockCounter()
{
  masterClock ++;
  if(masterClock == cyclesPerSecond)
  {
    seconds ++; 
    masterClock = 0; 
    if(seconds==60)
    {
      minutes++;
      seconds = 0;//reset seconds counter
      if(minutes==60)
      {
        hours++;
        minutes = 0;
      }
    }
  serialPrintTime();
  }
  return;
}




int byteToInt(int b1,int b2)
{
  int data = b1*10000 + b2;
  return data;
}




void Digitizer(int n,int mode)
{
  if(oldData == -1)
  {
    oldData = n;
  }
  int firstDigit = 0, secondDigit = 0,thirdDigit =0, fourthDigit = 0;
  if(n <9)
  {
    firstDigit = 0;
    secondDigit = 0;
    thirdDigit = 0;
    fourthDigit = n;
  }
  else if(n >9 && n<=99)
  {
    fourthDigit = n % 10;
    n = n/10;
    thirdDigit = n;
    secondDigit = 0;
    firstDigit = 0;
  }
  else if(n > 99 && n <=999)
  {
    fourthDigit = n % 10;
    n = n/10;
    thirdDigit = n % 10;
    n = n/10;
    secondDigit = n;
    firstDigit = 0;
  }
  else if(n > 999 && n <= 9999)
  {
    fourthDigit = n % 10;
    n = n/10;
    thirdDigit = n % 10;
    n = n/10;
    secondDigit = n % 10;
    n = n/10;
    firstDigit = n;
  }
  if(oldData != n)
  {
    oldData = n;
    Serial.print("Setting output to: ");
    Serial.print(firstDigit);
    Serial.print(secondDigit);
    Serial.print(thirdDigit);
    Serial.println(fourthDigit);
  }
  if(mode == 0)
  {
    for(int j=8;j>-1;j--)
     {
       lc.setColumn(0,j,byteToInt(digits[firstDigit][7-j],digits[secondDigit][7-j]));
       lc.setColumn(1,j,byteToInt(digits[thirdDigit][7-j],digits[fourthDigit][7-j]));
       delay(0);
     }
  }
  else  if(mode == 1)
  {
    for(int j=8;j>-1;j--)
     {
       lc.setColumn(0,j,byteToInt(Inverter(digits[firstDigit][7-j]),Inverter(digits[secondDigit][7-j])));
       lc.setColumn(1,j,byteToInt(Inverter(digits[thirdDigit][7-j]),Inverter(digits[fourthDigit][7-j])));
       //delay(50);
     }
  }
}

int Inverter(int line)
{
  int inv = ~line;
  return inv;
}


void setData(String input)
{
  h = input.substring(0,2).toInt();
  m = input.substring(2,4).toInt();
  s = input.substring(4,6).toInt();
}


void loop()
{
   if(Serial.available())
  {
    String in = Serial.readStringUntil('\n');
    Serial.print("Received Data: ");
    Serial.println(in);
    setData(in);
  }
}




void serialPrintTime()
{
  if(hours<10)
  {
    Serial.print("0");
  }
  Serial.print(hours);
  Serial.print(":");
  if(minutes<10)
  {
    Serial.print("0");
  }
  Serial.print(minutes);
  Serial.print(":");
  if(seconds<10)
  {
    Serial.print("0");
  }
  Serial.println(seconds);
}
