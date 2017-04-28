int minDistance = 50;


int redLedL = 2;
int redLedR = 3;
int whiteLed = 5;
int blueLedL = 6;
int blueLedR = 7;
int SPKR = 10;
int white_delay = 50 ;
int flash_delay = 130;
int change_delay = 100;
int pin = 9; // connected to the Trig on the module, this serves as both Trigger and Echo
unsigned long time;
unsigned long sizeofpulse;
float distance;

void loop()
{
pinMode(pin, OUTPUT); //return digital pin to OUTPUT mode after reading
digitalWrite(pin, LOW);
delayMicroseconds(25);
digitalWrite(pin, HIGH); //Trig pin pulsed LOW for 25usec
time = micros(); //record timer
pinMode(pin, INPUT); //change pin to INPUT to read the echo pulse 
sizeofpulse = pulseIn(pin, LOW, 18000); //should be approx 150usec, timeout at 18msec
time = micros() - time - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
distance = (time*340.29/2/10000)-3; // convert to distance in centimeters
Serial.print(" Distance: ");
Serial.print(distance);
Serial.println(" cm");
delay(100);
if(distance < minDistance )
{
  pattern3();
}
else
turnOff();
}

void setup()
{
 
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); // Trig pin is normally HIGH
  pinMode(SPKR,OUTPUT);
  pinMode(redLedL,OUTPUT);
  pinMode(redLedR,OUTPUT);
  pinMode(blueLedL,OUTPUT);
  pinMode(blueLedR,OUTPUT);
  pinMode(whiteLed,OUTPUT);  
}

//void pulse(){}


void pulse()
{
  noTone(SPKR);
  tone(SPKR,680);
  digitalWrite(whiteLed,HIGH);
  delay(white_delay);
   noTone(SPKR);
  tone(SPKR,980);
  digitalWrite(whiteLed,LOW);
  delay(white_delay);
  noTone(SPKR);
  tone(SPKR,680);
  digitalWrite(whiteLed,HIGH);
  delay(white_delay);
   noTone(SPKR);
  tone(SPKR,980);
  digitalWrite(whiteLed,LOW);
  delay(white_delay);
}


void turnOff()
{
  digitalWrite(redLedL,LOW);
  digitalWrite(redLedR,LOW);
  digitalWrite(whiteLed,LOW);
  digitalWrite(blueLedL,LOW);
  digitalWrite(blueLedR,LOW);
  
}




//digitalWrite(redLedL,HIGH);

void pattern1()
{
 delay(change_delay);
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
digitalWrite(whiteLed,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
digitalWrite(whiteLed,HIGH);
delay(flash_delay);
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
digitalWrite(whiteLed,LOW);
delay(change_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);
digitalWrite(whiteLed,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
digitalWrite(whiteLed,HIGH);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);
digitalWrite(whiteLed,LOW);

}

void pattern2()
{
 
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(change_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);
delay(change_delay);


// NOW BLUE

digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
delay(change_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(change_delay);
}



void pattern3()
{
 
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);

delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,HIGH);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,HIGH);
pulse();
delay(change_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,LOW);
digitalWrite(blueLedR,LOW);
digitalWrite(redLedR,LOW);
delay(flash_delay);
digitalWrite(redLedL,LOW);
digitalWrite(blueLedL,HIGH);
digitalWrite(blueLedR,HIGH);
digitalWrite(redLedR,LOW);
pulse();
delay(change_delay);
}






