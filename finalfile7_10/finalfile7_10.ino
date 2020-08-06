#include <SoftwareSerial.h>
int tp=9; // pin numbers ahet connection che
int ep=10;
int LR=13;
int LG=12;
int LO=11;
SoftwareSerial BTserial(0,1); //RX | TX
// to send data through the bluetooth port u have to use the above command 
// get the buttons using serail.read 
void setup() {
  Serial.begin(9650);
  //BTserial.begin(9600);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(A0,INPUT);  //oxygen sensor
  digitalWrite(LO,LOW);
  digitalWrite(LR,LOW);
  digitalWrite(LG,LOW);
  BTserial.begin(9600);
}

void loop() 
{
  float d=distancecalc();
  float o2=percentagecalc();
  delay(5000);
  if(BTserial.available() > 0)
  {
    char rechar = BTserial.read();
     if(rechar =='A')
     {  delay(500);
        BTserial.print((float)d);
     }
     else if(rechar=='D'){
        delay(500);
        BTserial.print((float)o2); 
     }  
  }
  
  if(d<30)
  {
    Serial.print("Too LOW PLS SAVE YOUR COMPONENTS");
    digitalWrite(LR,HIGH); 
  }
  else
  { 
   if(o2<20 && o2>15)
   {
    digitalWrite(LO,HIGH); 
    Serial.print("Oxygen Is Low in The MAnhole Pls Clean The Manhole"); 
   }
   else if(o2<=15)
   {
    digitalWrite(LR,HIGH);
    Serial.print("NO HUMAN CAN SURVIVE IN THIS");
   }
   digitalWrite(LG,HIGH);
   Serial.print("THE MANHOLE IS SAFE FOR OPERATION WORK CAN BE DONE");
     
  }
    
}

float percentagecalc()
{ pinMode(A0,INPUT_PULLUP);
  delay(1);
  bool r= analogRead(A0)<900; // 900 is not fix depends on the sensor for ke50
  float op=0.0;
  if(r)
  {
    pinMode(A0,INPUT);
    delay(1);
    float mV=analogRead(A0);
    Serial.print("KE-25 value =");
    Serial.print(mV);
    float op=(mV*3000/992)/0.6;    // this equation can be change depending on the oxygen sensor refernece ghetla ahe
    Serial.print("Oxygen Percentage=");
    Serial.print(op);
    Serial.print("% \n \n");
    
  }
 return op;
}

float distancecalc()
{
    float t,d,h;
 delay(50);
digitalWrite(tp, LOW);
delayMicroseconds(2);
digitalWrite(tp, HIGH);
delayMicroseconds(10);
digitalWrite(tp, LOW);
  t=pulseIn(ep,HIGH);
  
  d=t*((100 / 2) / 29); 
  h=d;

  Serial.print(d);
  Serial.print("cm\n");
  delay(1000);
  digitalWrite(LG,HIGH);
  return h;
}
