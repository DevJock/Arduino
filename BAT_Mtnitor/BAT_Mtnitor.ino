#include<LiquidCrystal.h>

// number of analog samples to take per reading
#define NUM_SAMPLES 10

int sum = 0;                    // sum of samples taken
unsigned char sample_count = 0; // current sample number
float voltage = 0.0;            // calculated voltage

 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

 
void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}
 
void loop() 
{
 //lcd.clear();
     // take a number of analog samples and add them up
  while (sample_count < NUM_SAMPLES) 
   {
     sum += analogRead(A0);
     sample_count++;
     delay(10);
   }
   // calculate the voltage
   // use 5.0 for a 5.0V ADC reference voltage
   // 5.015V is the calibrated reference voltage
   voltage = ((float)sum / (float)NUM_SAMPLES * 5.015) / 1024.0;
   // send voltage for display on Serial Monitor
   // voltage multiplied by 11 when using voltage divider that
   // divides by 11. 11.132 is the calibrated voltage divide
   // value
   //Serial.print(voltage * 11.132);
   //Serial.println (" V");
   lcd.setCursor(0,0);
   lcd.print("DC VOLTMETER");
   lcd.setCursor(0,1);
   lcd.print("Volts: ");
   lcd.setCursor(7,1);
   lcd.print(voltage * 11.132);
   sample_count = 0;
   sum = 0;
   delay(50);
 }
