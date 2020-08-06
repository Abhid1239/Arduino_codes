#include <SoftwareSerial.h>
int tp = 3; // ultrasonic trigger pin
int ep = 4; // ultrasonic echo pin
int LR = 7; // LED Red
int LG = 8; // LED Green
int LO = 6; // LED Orange
SoftwareSerial BTserial(10, 11); // RX | TX
void setup() 
{
        Serial.begin(4800);   // to send data to serial monitor at 4800 baud rate
        pinMode(LR,OUTPUT);   // LED's to set as ouput 
        pinMode(LO,OUTPUT);
        pinMode(LG,OUTPUT);
        pinMode(tp, OUTPUT);  // trigger pin as ouput
        pinMode(ep, INPUT);   // echo pin as input
        pinMode(A0, INPUT);   // analog pin as input for oxygen sensor
       
        BTserial.begin(9600); // to send data to bluetooth at 9600 baud rate
}

void loop()
{
  // to change the name or password code for bluetooth check the bluetooth file
  
  float d  = distancecalc(); //function for distance calculate
  float o2 = Oxygenperc();   //function for oxygen calculate
  delay(5000);
  
  // To send data to smartphone through Bluetooth
  if (BTserial.available() > 0)  
  {
       char rechar = BTserial.read(); // To get data from Bluetooth
        if(rechar =='D')      // If Button Clicked For Distance
        {  
           delay(500);
           BTserial.print((float)d);
        }
        else if(rechar=='O')  // If Button Clicked For Oxygen  
        {
           delay(500);
           BTserial.print((float)o2);
        }
   }
   
   // To show the Output on Serial Monitor And LED's
   
   if (d < 25)     // to check if the distance is less than threshold
    {
      Serial.print("The Distance is to low = ");
      Serial.print(d);
      Serial.print(" cm \n")
      digitalWrite(LR, HIGH);
    }
    
 
   digitalWrite(LO, HIGH);
   Serial.print("The Distance is correct now we can measure the oxygen \n \n");
    
    else if (o2 >= 18)     // to check if the Oxygen is less than threshold
     {
        digitalWrite(LG, HIGH);
        Serial.print("Oxygen Percentage=  ");
        Serial.print(o2);
        Serial.print("% \n");
        Serial.print("THE MANHOLE IS SAFE FOR OPERATION WORK CAN BE DONE  \n \n");
      }
     else if (o2 < 18)
     {
      digitalWrite(LR, HIGH);
      Serial.print("THe oxygen is too low pls clean the manhole \n \n");
     }

}

float distancecal()
{ 
  pinMode(A0, INPUT_PULLUP);
  delay(100);
  bool True = analogRead(A0) < 100; // If the value is greater that means the oxygen is not connected properly
  float op = 0.0;
  if (True)
  {
      pinMode(A0, INPUT);
      delay(100);
      float mV = analogRead(A0);   // to read the data from oxygen which is in mV
      Serial.print("KE-25 value =");
      Serial.print(mV);
      float op = (mV * 3000 / 992) / 0.6; // this equation can be change d
    Serial.print("Oxygen Percentage=");
    Serial.print(op);
    Serial.print("% \n \n");

  }
  return op;
}

float Oxygenperc()
{
  float t, d, h;
  delay(50);
  digitalWrite(tp, LOW);
  delayMicroseconds(2);
  digitalWrite(tp, HIGH);
  delayMicroseconds(10);
  digitalWrite(tp, LOW);
  t = pulseIn(ep, HIGH);
  d = t*((100 / 2) * 29);
  h = d/100000;
    Serial.print("\n \n");
  Serial.print(h);
  Serial.print(" cm\n");
  return h;
}

float methane()
{
  return 0;
}
