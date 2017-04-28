void setup() 
{
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(getVoltage(A0));
  Serial.println(" V");
  delay(150);
}


double getCurrent(int pin)
{ 
   double current = 0;
   int in  = 0;
   double pinVolt = 0;
   for(int i=1;i<=25;i++)
   {
    in += analogRead(pin);
   }
   in = in / 25.0;
   pinVolt = ((in * 1.10 / 1023.0 / 0.09090909091))*1000;
   current = (pinVolt - 2500) / 185;
   return current;
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
  vout = value * 1.10 / 1023.0;
  vin = (vout / 0.09090909091) - 0.1; 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}
