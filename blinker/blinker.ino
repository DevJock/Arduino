int light_1=3;
int light_2=4;
int light_3=5;
int light_4=6;
int light_5=7;
int cindex=-1;
int dled =13;
int ldr = 0;
int thresh=15;
int c=-1;

boolean on[] = {true,false,false,false,false};

void setup()
{

  for (int i=3;i<8;i++)
  pinMode(i,OUTPUT);
  pinMode(dled,OUTPUT);
  pinMode(ldr,INPUT);
  Serial.begin(9600);

 }


void Update()
{
  for(int i=3;i<8;i++)
  {
    if(on[i-3]==true)
    {
    digitalWrite(i,HIGH);
    //Serial.println("true:r"+i);
    }
    else if(on[i-3]==false)
    {
    digitalWrite(i,LOW);
  //  Serial.println("false:r"+i);
    }
  }
}






void Lighter()
{
c=0;
cindex=cindex+1;
on[cindex]=true;
if(cindex>0)
on[cindex-1]=false;
Update();
Print();
  
}

void Print()
{
  for(int i=0;i<5;i++)
  {
    Serial.print(on[i]);
    delay(50);
  }
  Serial.println("");
}


void Supress()
{
for(int i =0;i<5;i++)
if(on[i]==true)
on[i]=false;
Update();
}


void loop()
{
  while(analogRead(ldr)<600 && analogRead(ldr)>=thresh)
  {
    Serial.println(analogRead(ldr));
    Supress();
    delay(200);
  }
  
  digitalWrite(dled,HIGH);
 delay(200);
  Lighter(); 
 digitalWrite(dled,LOW);
 delay(200);
 
}
