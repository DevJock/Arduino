int cyclesPerSecond = 979;

//pins
int clockInterrupt = 0; //interrupt 0 is pin 2 on UNO
int pwmOut = 6; //pin 6

//timekeeping
int seconds = 0;
int minutes = 0;
int hours = 0;
int masterClock = 0;//number of square waves

void setup(void) 
{
// clockInterrupt is our interrupt, clockCounter() function is called when invoked on a RISING clock edge
attachInterrupt(clockInterrupt, clockCounter, RISING);
delay(2000);
analogReference(DEFAULT);//not sure if this is needed
Serial.println(pwmOut);
analogWrite(pwmOut, 127); // this starts our PWM 'clock' with a 50% duty cycle//digital pin 10 for analogWrite pwm out
}


void clockCounter() // called by interrupt 0 (pin 2 on the UNO) receiving a rising clock edge PWM
{
masterClock ++; // with each clock rise add 1 to masterclock count
if(masterClock == cyclesPerSecond) // 974hz on pin 6, may be 490Hz if you use pin 9 or 10
{
seconds ++; // after one cycle add 1 second
masterClock = 0; //reset clock counter

if(seconds==60){
minutes++;
seconds = 0;//reset seconds counter

if(minutes==60){
hours++;
minutes = 0;
}
}
serialPrintTime();
}
return;
}


void serialPrintTime()
{
if(hours<10){
Serial.print("0");
}
Serial.print(hours);
Serial.print(":");

if(minutes<10){
Serial.print("0");
}
Serial.print(minutes);
Serial.print(":");
if(seconds<10){
Serial.print("0");
}
Serial.println(seconds);
}
