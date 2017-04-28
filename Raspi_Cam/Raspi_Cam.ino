#include<Servo.h>

Servo servo;
int index = 0;

void setup()
{
  Serial.begin(9600);
  servo.attach(4);
  moveServo('6');
  Serial.println("ready");
}

void loop() 
{
  if(Serial.available())
  {
    char in = Serial.read();
    moveServo(in);
  }  
}


void moveServo(char pos)
{
  if(pos >= '0' && pos <= '9')
  {
    if(pos == 'q')
     index = 18 * 10;
    else
     index = 18 * (pos - '0');
    servo.write(index);
  }
  else if(pos == 'q')
  {
    if(index < 180)
     servo.write(index+=9);
  }
  else if(pos =='e')
  {
    if(index > 0)
     servo.write(index-=9);
  }
}
