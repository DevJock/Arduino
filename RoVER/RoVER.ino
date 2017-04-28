/*  RoVER Mission Control

    Programmed and Developed By Chiraag Bangera
    
    No modification of Code allowed 
    
    Contact me @ chiraagxbl@live.com
    
    © Chiraag Bangera 2012 - 2013

*/

int motor1 = 6; //D1
int motor2 = 5; //D2 
int enable1 = 8; //M1 
int enable2 = 7; //M2
int RF = 0;
int GD = 2;
int led = 3;
int tme= 0;
int dspeed = 254;

void setup()
{
 Serial.begin(9600);
 for(int i=0;i<=8;i++)
 pinMode(i,OUTPUT);
 pinMode(RF,INPUT);
 pinMode(GD,INPUT);
 pinMode(led,OUTPUT);

}



void loop()
{
  Serial.flush();
   while(Serial.available()==0)
   {
     int vcx;
  int m = analogRead(RF);
  int n = !digitalRead(GD);
  String t ="",v="";
  v=String(readVcc()/10);
  t=String(readTemp()/1000);
  String out =String(m)+","+t+"."+v+":"+String(n);    // ddd,ttt.vvv.g
  Serial.println(out);                                // 0123456789101112
   }
  char ch = Serial.read();
  switch(ch)
  {
   case 'W' :
   {
     moveForward(dspeed,dspeed);
   } break;
   case 'A' :
   {
     turnLeft(dspeed,dspeed);
   } break;
   case 'D' :
   {
     turnRight(dspeed,dspeed);
   } break;
   case 'S' :
   {
     moveBackward(dspeed,dspeed);
   } break;
   case 'L' :
   {
     toggleLed();
   }break;
   default:
   {
     Stop();
   }break;
  }
}


boolean laststate = 0;
void toggleLed()
{
  if(!laststate)
  {
    digitalWrite(led,HIGH);
    laststate=1;
  }
  else
  {
    digitalWrite(led,LOW);
    laststate=0;
  }
}



void Reset()
{
  Stop();
  delay(tme);
}

void Stop()
{
   digitalWrite(enable1,LOW);
   digitalWrite(enable2,LOW);
   analogWrite(motor1,0);
   analogWrite(motor2,0);
   
}


void moveForward(int lspeed,int rspeed)
{
  Reset();
  digitalWrite(enable1,HIGH);
  analogWrite(motor1,lspeed);  // motor 1
  digitalWrite(enable2,HIGH);
  analogWrite(motor2,rspeed); // motor 2
}

void moveBackward(int lspeed,int rspeed)
{
  Reset();
  digitalWrite(enable1,LOW);
  analogWrite(motor1,lspeed);  // motor 1
  digitalWrite(enable2,LOW);
  analogWrite(motor2,rspeed); // motor 2
}

void turnLeft(int lspeed,int rspeed)
{
  Reset();
  digitalWrite(enable1,LOW);
  analogWrite(motor1,lspeed);  // motor 1
  digitalWrite(enable2,HIGH);
  analogWrite(motor2,rspeed); // motor 2
}

void turnRight(int lspeed,int rspeed)
{
  Reset();
  digitalWrite(enable1,HIGH);
  analogWrite(motor1,lspeed);  // motor 1
  digitalWrite(enable2,LOW);
  analogWrite(motor2,rspeed); // motor 2
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(20); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

long readTemp() 
{
  long result;
  // Read temperature sensor against 1.1V reference
  ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
  delay(20); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = (result - 125) * 1075;
  return result;
}

