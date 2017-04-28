// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

void getVoltages();
float getVoltage(int option);
double getCurrent(int pin);

int b1CurrentSense = A0;
int Solar_Panel = A1;
int VCC_Regulator = A2;
int Batt_1 = A3;
int Batt_2 = A4;
int b2CurrentSense = A5;

int ledPin = 13;

int r1 = 46; //b1
int r2 = 47; //b2

int r3 = 48; //bat_sw
int r4 = 49; //chrg_sw
int r5 = 50;
int r6 = 51;
int r7 = 52;
int r8 = 53;

float b1,b2,sp,vr;

bool charge = false;

int bToCharge = 1;

int binUse = 0;

double b1Current = 0;
double b2Current = 0;

float tVolts = 6.0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  for(int i = 46;i<=53;i++)
    pinMode(i,OUTPUT);
}

void displayData()
{
  lcd.clear();
  if(bToCharge == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("B1 V:");
    lcd.print(b1,1);
    lcd.print(" A:");
    lcd.print(b1Current,1);

    lcd.setCursor(0,1);
    lcd.print("B2 V:");
    lcd.print(b2,1);
    lcd.print(" A:");
    lcd.print(b2Current,1);
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("B1 V:");
    lcd.print(b1,1);
    lcd.print(" A:");
    lcd.print(b1Current,1);

    lcd.setCursor(0,1);
    lcd.print("B2 V:");
    lcd.print(b2,1);
    lcd.print(" A:");
    lcd.print(b2Current,1);
  }

  Serial.print("B1: ");
  Serial.print(b1);
  Serial.print(", B2: ");
  Serial.print(b2);
  Serial.print(", SP: ");
  Serial.print(sp);
  Serial.print(", VR: ");
  Serial.println(vr);
}



void loop() 
{
  getVoltages();
  b1Current = -1* getCurrent(b1CurrentSense);
  b2Current = -1* getCurrent(b2CurrentSense);
  displayData();
  if(b1>b2)
  bToCharge = 1;
  else
  bToCharge = 0;
  if(vr >= 6.0 && vr <= 6.5)
  charge = true;
  if(charge)
  {
    if(bToCharge == 0)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,HIGH);
      digitalWrite(r1,HIGH);
      digitalWrite(r4,HIGH);
    }
    else
    {
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      digitalWrite(r3,LOW);
      digitalWrite(r4,HIGH);
    }
  }
  else
  {
    if(bToCharge == 0)
    {
      digitalWrite(r2,HIGH);
      digitalWrite(r3,HIGH);
      digitalWrite(r1,HIGH);
      digitalWrite(r4,LOW);
    }
    else
    {
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW);
      digitalWrite(r3,LOW);
      digitalWrite(r4,LOW);
    }
  }
  delay(250);
}


void getVoltages()
{
  b1 = getVoltage(Batt_1);
  b2 = getVoltage(Batt_2);
  sp = getVoltage(Solar_Panel);
  vr = getVoltage(VCC_Regulator);
  delay(25);
}


double getCurrent(int pin)
{
  int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
  int RawValue= 0;
  int ACSoffset = 2500; 
  double Voltage = 0;
  double Amps = 0;
  RawValue = analogRead(pin);
  Voltage = (RawValue / 1023.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  return Amps;
}

float getVoltage(int option)
{
  float R1 = 100000.0;
  float R2 = 10000.0; // resistance of R2 (10K)!
  int value = analogRead(option);
  float vout = (value * 5.0) / 1024.0; // see text
  float vin = vout / (R2/(R1+R2)); 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}

