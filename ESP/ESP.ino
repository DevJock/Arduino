#include<SoftwareSerial.h>


const String  wSSID = "Xpress_Network";
const String  wPSWD = "KudlaKatapadi123456";
int RST = 4;
int rx = 3;
int tx = 2;
int c = 0;

SoftwareSerial esp(rx,tx);

void setESP()
{
  String r="";
  String SSPW = "AT+CWJAP=\""+wSSID+"\",\""+wPSWD+"\"";
  digitalWrite(RST,LOW);
  delay(100);
  digitalWrite(RST,HIGH);
  Serial.println(sendCmd("AT+QWAP",2000));
  Serial.println(sendCmd("AT+MODE=1",2000));
  Serial.println(sendCmd(SSPW,5000));
  Serial.println(sendCmd("AT+CIFSR",0));
}


String sendCmd(String cmd,int delayTime)
{
  String response="";
  cmd.concat("\r");
  esp.println(cmd);
  delay(delayTime);
  while(esp.available())
  {
    response += (char)esp.read();
  }
  return response;
}



void setup() 
{
 Serial.begin(9600);
 esp.begin(9600);
 Serial.println("Started");
 pinMode(RST,OUTPUT);
 setESP();
}

void loop() 
{
  if(esp.available())
  {
    while(esp.available())
    {
      char c = (char)esp.read();
      Serial.write(c);
    }
  }
  
  if(Serial.available())
  {
    delay(100);
    String cmd = "";
    while(Serial.available())
    {
      cmd += (char)Serial.read();
    }
    cmd.concat("\r");
    esp.println(cmd);
  }
}
