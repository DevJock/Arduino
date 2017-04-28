int ledControlPin = 13;

int potPin = A0;
int readValue = 0;

bool ledON;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledControlPin,OUTPUT);
  pinMode(potPin,INPUT);
  ledON = false;
  digitalWrite(ledControlPin,LOW);
}

void loop() 
{
  if(!Serial.available())
  {
    readValue = map(analogRead(potPin),0,1023,0,1000);
    Serial.print("DelayTime: ");
    Serial.println(readValue);
  }
  else
  {
    if(ledON)
    {
      ledON = false;
      digitalWrite(ledControlPin,LOW);
    }
    else
    {
      ledON = true;
      digitalWrite(ledControlPin,HIGH);
    }
    delay(readValue);
  }
}
