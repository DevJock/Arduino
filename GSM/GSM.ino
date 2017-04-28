void setup() 
{
  Serial1.begin(115200);
  Serial.begin(9600);
  Serial.println(sendCmd("AT+CPIN?",1000));
  Serial.println(sendCmd("AT+CSQ",1000));
}


void loop() 
{
  if(Serial.available())
  {
    char ch = Serial.read();
    switch(ch)
    {
      case 'S':
      {
        Serial.println("Enter the Mobile Number");
        String number ="";
        while(!Serial.available()); //wait till text entered
        while(Serial.available())
        {
          number += Serial.read();
        }
        Serial.println("Enter the Text to Send and press Enter");
        String message ="";
        while(!Serial.available()); //wait till text entered
        while(Serial.available())
        {
          message += Serial.read();
        }
        Serial.println(sendCmd("AT+CMGF=\""+message+"\"",1000));
        Serial.println("Sending..");
        Serial.println(sendCmd("AT+CMGS=\""+number+"\"",1000));
        //Serial.println(sendCmd(char(26),1000));
      }break;
      
      case 'R':
      {
        Serial.println("Enabling Receive Mode");
        Serial.println(sendCmd("AT+CMGF=1",1000));
      }break;
      
      case 'D':
      {
        Serial.println("Enter the Mobile Number");
        String number ="";
        while(!Serial.available());
        while(Serial.available())
        {
          number += Serial.read();
        }
        Serial.println("Dailing..");
        Serial.println(sendCmd("ATD+"+number,1000));
      }break;
      
    }
  }
  
}




String sendCmd(String command,int Delay)
{
  String response = "";
  response.concat("\r");
  Serial1.println(command);
  delay(Delay);
  while(Serial1.available())
  {
    response += (char)Serial1.read();
  }
  return response;
}
