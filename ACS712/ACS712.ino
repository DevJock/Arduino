
int cSense = A3;
int VsensePin = A7;


void setup() 
{
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop()
{
  double senseValue = getCurrent(cSense);
  double voltSense = getVoltage(VsensePin);
  Serial.print(voltSense);
  Serial.print(" V, ");
  Serial.print(senseValue);
  Serial.println(" A");
  delay(250);
}

double getCurrent(int pin)
{
 
}



float getVoltage(int option)
{
  float R1 = 100000.0;
  float R2 = 10000.0; // resistance of R2 (10K)!
  int value = analogRead(option);
  float vout = (value * 1.1) / 1024.0; // see text
  float vin = vout / (R2/(R1+R2)); 
  if (vin<0.09)
  {
    vin=0.0;//statement to quash undesired reading !
  } 
  return vin;
}

