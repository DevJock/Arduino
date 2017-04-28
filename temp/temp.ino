int cyclesPerSecond = 979;
int led = 13;
int masterClock = 0;
int seconds = 0;

bool started = false;


void setup() 
{
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(9600);
  analogWrite(9,51);
  attachInterrupt(0,runThis,CHANGE);
  attachInterrupt(1,timer,RISING);
}

void loop() 
{
  Serial.println(masterClock);
  delay(250);
}

void timer()
{
  masterClock ++;
}

void runThis()
{
  if(!started)
  {
    masterClock = 0;
    digitalWrite(led,HIGH);
    analogWrite(6,127);
    started = true;
  }
  else
  {
    digitalWrite(led,LOW);
    analogWrite(6,0);
    started = false;
  }
}
