#define NUMREADINGS 30 // raise this number to increase data smoothing

int senseLimit = 10; // raise this number to decrease sensitivity (up to 1023 max)
int val = 0;


int led0 = 2;
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;
int led6 = 8;
int led7 = 9;

int ant = 5;

int readings[NUMREADINGS];                // the readings from the analog input
int index = 0;                            // the index of the current reading
int total = 0;                            // the running total
int average = 0;    

//CHANGE THIS TO affect the speed of the updates for numbers. Lower the number the faster it updates.
int updateTime = 10;


void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;  
  for(int i=2;i<10;i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(ant,INPUT);
}

void test()
{
  for(int i=2;i<10;i++)
  {
    if(i > 0)
    digitalWrite(i-1,LOW);
    digitalWrite(i,HIGH);
    delay(250);
    if(i>8)
    digitalWrite(i,LOW);
  }
}


void loop()
{
  val = analogRead(ant);  // take a reading from the probe
  if(val >= 1)
  {                // if the reading isn't zero, proceed
    val = constrain(val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
    val = map(val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range

    total -= readings[index];               // subtract the last reading
    readings[index] = val; // read from the sensor
    total += readings[index];               // add the reading to the total
    index = (index + 1);                    // advance to the next index

    if (index >= NUMREADINGS)               // if we're at the end of the array...
      index = 0;                            // ...wrap around to the beginning

    average = total / NUMREADINGS;          // calculate the average

    if (average > 50){                // if the average is over 50 ...
      turnLedsOn(0);   // Show a 0

    }

    if (average > 150){               // and so on ...
      turnLedsOn(1);  // Show a 1
    }

    if (average > 250){
     turnLedsOn(2);   // Show a 2
    }

    if (average > 350){
      turnLedsOn(3);   // Show a 3
    }


    if (average > 450){
     turnLedsOn(4);  // Show a 4
    }

    if (average > 550){
      turnLedsOn(5);   // Show a 5
    }

    if (average > 650){
      turnLedsOn(6); // Show a 6

    }

    if (average > 750){
      turnLedsOn(7);   // Show a 7
    }

    if (average > 850){
      turnLedsOn(8);   // Show a 8
    }

    Serial.print("EMF Reading: ");  // use output to aid in calibrating
    Serial.println(average);
    delay(updateTime);
  }

}

void turnLedsOn(int num)
{
  switch(num)
  {
    case 0:
    {
      for(int i=2;i<=9;i++)
      digitalWrite(i,LOW);
      break;
    }
    case 1:
    {
      for(int i=2;i<=2;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 2:
    {
      for(int i=2;i<=3;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 3:
    {
      for(int i=2;i<=4;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 4:
    {
      for(int i=2;i<=5;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 5:
    {
      for(int i=2;i<=6;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 6:
    {
      for(int i=2;i<=7;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 7:
    {
      for(int i=2;i<=8;i++)
      digitalWrite(i,HIGH);
      break;
    }
    case 8:
    {
      for(int i=2;i<=9;i++)
      digitalWrite(i,HIGH);
      break;
    }
  }
}


