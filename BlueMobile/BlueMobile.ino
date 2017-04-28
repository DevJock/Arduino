#include<SoftwareSerial.h>
#include <math.h>

#define FULL_CELL_VOLTAGE 4.15
#define EMPTY_CELL_VOLTAGE 3.1

float pad = 10000;
float thermr = 10000;


int voltageSensor = A0;
int thermPIN = A1;


int rx = 2;
int tx = 3;

int led = 13;

int driveMotor1 = 7;
int driveMotor2 = 8;
int driveMotorSpeed = 11;
int steerMotor1 = 9;
int steerMotor2 = 10;
SoftwareSerial xbee(rx,tx);

float voltage = 0.0;

int Speed = 0;
int Dir = 1;
int Light = 0;

void setup() 
{
 // analogReference(INTERNAL);
  Serial.begin(9600);
  xbee.begin(9600);
  
  pinMode(voltageSensor,INPUT);
  pinMode(driveMotor1,OUTPUT);
  pinMode(driveMotor2,OUTPUT);
  pinMode(steerMotor1,OUTPUT);
  pinMode(steerMotor2,OUTPUT);
}

void loop() 
{
  if(Serial.available() || xbee.available())
  {
    String in = "";
    int s = 0;
    int d = 0;
    int l = 0;
    //!speed,dir,light#
    //!255,1,0#
    //012345678
    if(Serial.available())
    {
      in = Serial.readString();
    }
    else
    {
      in = xbee.readString();
    }
    s = in.substring(1,4).toInt();
    d = in.substring(5,6).toInt();
    l = in.substring(7,8).toInt();
    printLine("Received: ",0);
    printLine(in,1);
    if(l == 0)
    {
      digitalWrite(led,LOW);
    }
    else
    {
      digitalWrite(led,HIGH);
    }

    
    if(s > 256)
    {
      analogWrite(driveMotorSpeed,(s-255));
      digitalWrite(driveMotor1,LOW);
      digitalWrite(driveMotor2,HIGH);
    }
    else if(s < 256)
    {
      analogWrite(driveMotorSpeed,(s));
      digitalWrite(driveMotor1,HIGH);
      digitalWrite(driveMotor2,LOW);
    }
    else
    {
      analogWrite(driveMotorSpeed,(0));
      digitalWrite(driveMotor1,LOW);
      digitalWrite(driveMotor2,LOW);
    }

    if(d == 0)
    {
      digitalWrite(steerMotor1,LOW);
      digitalWrite(steerMotor2,HIGH);
    }
    else if(d == 2)
    {
      digitalWrite(steerMotor1,HIGH);
      digitalWrite(steerMotor2,LOW);
    }
    else
    {
      digitalWrite(steerMotor1,LOW);
      digitalWrite(steerMotor2,LOW);
    }
  }
  else
  {
    voltage = getVoltage();
    //printLine("Voltage: ",0);
    printLine(String(temp())+","+String(voltage),1);
    delay(100);
  }

}

void printLine(String Data,int lineMode)
{
  if(lineMode == 0)
  {
    Serial.print(Data);
    xbee.print(Data);
  }
  else
  {
    Serial.println(Data);
    xbee.println(Data);
  }
}


float temp() 
{
  long Resistance;  
  float Temp;  
  Resistance=pad*((1024.0 / analogRead(thermPIN)) - 1); 
  Temp = log(Resistance);
   Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;                   
  return Temp;
}



float getVoltage()
{
  int value = 0;
  double vout = 0;
  double vin = 0;
  for(int i=1;i<=25;i++)
  {
    value += analogRead(voltageSensor);
  }
  value = value / 25.0;
  vout = value * 5.0 / 1024.0;
  //vin = (vout / 0.5942028986); 
  vin = (vout / 0.09090909091) ; 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}


