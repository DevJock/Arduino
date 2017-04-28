int red = 9;
int green = 10;
int blue = 11;

int debug_Led = 1;

int trans_delay = 100  ;

int changeVal = 5;

int rLim = 255;
int gLim = 255;
int bLim = 255;


void setup()
{
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(debug_Led,OUTPUT);
    analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,0);
  
}


void test()
{
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
  digitalWrite(blue,LOW);
  delay(1000);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  digitalWrite(blue,LOW);  
  delay(1000);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  digitalWrite(blue,HIGH);  
  delay(1000);
}


void loop()
{  
  Serial.println("UP");
  
  for(int i =0;i<=255;i+= changeVal)
  {
    analogWrite(red,i);
    Serial.print("RED: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  delay(1000);
  
  for(int i =255;i>=0;i-= changeVal)
  {
    analogWrite(red,i);
    Serial.print("RED: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  
  for(int i =0;i<=gLim;i+= changeVal)
  {
    analogWrite(green,i);
    Serial.print("Green: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  delay(1000);
  
  for(int i =gLim;i>=0;i-= changeVal)
  {
    analogWrite(green,i);
    Serial.print("Green: ");
    Serial.println(i);
    delay(trans_delay);
  }
 
  
  for(int i =0;i<=bLim;i+= changeVal)
  {
    analogWrite(blue,i);
    Serial.print("Blue: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  delay(1000);
  for(int i =bLim;i>=0;i-= changeVal)
  {
    analogWrite(blue,i);
    Serial.print("Blue: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  for(int i =0;i<=rLim;i+= changeVal)
  {
    analogWrite(red,i);
    Serial.print("RED: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  for(int i =0;i<=gLim;i+= changeVal)
  {
    analogWrite(green,i);
    Serial.print("Green: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  for(int i =0;i<=bLim;i+= changeVal)
  {
    analogWrite(blue,i);
    Serial.print("Blue: ");
    Serial.println(i);
    delay(trans_delay);
  }
 
  
  Serial.println("DOWN");
  for(int i =rLim;i>=0;i-= changeVal)
  {
    analogWrite(red,i);
    Serial.print("RED: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  for(int i =gLim;i>=0;i-= changeVal)
  {
    analogWrite(green,i);
    Serial.print("Green: ");
    Serial.println(i);
    delay(trans_delay);
  }
  
  for(int i =bLim;i>=0;i-= changeVal)
  {
    analogWrite(blue,i);
    Serial.print("Blue: ");
    Serial.println(i);
    delay(trans_delay);
  }  
  analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,0);
  delay(1000);
}



