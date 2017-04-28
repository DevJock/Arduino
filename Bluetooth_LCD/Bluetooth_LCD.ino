#include <LiquidCrystal.h>

#define rxPin 10
#define txPin 11
#define ledPin 13

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);


float distance;
String in = "";
int i = 0;

void setup()
{
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.print("Hello i'm iMac");
 pinMode(rxPin, INPUT);
 pinMode(txPin, OUTPUT);
 pinMode(ledPin,OUTPUT);
}

void loop()
{
 if(Serial.available())
 {
   in = Serial.readStringUntil('\n');
   in.setCharAt(in.length() - 1,' ');
   Serial.print("Received: ");
   Serial.println(in);
   lcd.clear();
   lcd.print(in);
 }
}


