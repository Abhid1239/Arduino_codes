#include <SoftwareSerial.h>
#define SensorPin A0;  // Oxygen Sensor pin

int tp = 3;            // ultrasonic trigger pin
int ep = 4;            // ultrasonic echo pin
int LR = 7;            // LED Red
int LG = 8;            // LED Green
int LO = 6;             // LED Orange

SoftwareSerial BTserial(10, 11); // RX | TX


void setup() 
{
        Serial.begin(4800);   // to send data to serial monitor at 4800 baud rate
        
        pinMode(LR,OUTPUT);   // LED's to set as ouput 
        pinMode(LO,OUTPUT);
        pinMode(LG,OUTPUT);
        
        pinMode(tp, OUTPUT);  // trigger pin as ouput
        pinMode(ep, INPUT);   // echo pin as input
        
        analogReference(INTERNAL);
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
      
          Serial.print(" cm \n");
          digitalWrite(LR, HIGH);
      }
   
   else 
      {
      
          digitalWrite(LO, HIGH);
          Serial.print("The Distance is correct now we can measure the oxygen \n \n");
      
          if (o2 >= 20)     // to check if the Oxygen is less than threshold
              {
                  digitalWrite(LG, HIGH);
                  Serial.print("Oxygen Percentage=  ");
                  Serial.print(o2);
      
                  Serial.print("% \n");
                  Serial.print("THE MANHOLE IS SAFE FOR OPERATION WORK CAN BE DONE  \n \n");
              }
    
          else if (o2 < 20)
     
          {
                  digitalWrite(LR, HIGH);
                  Serial.print("THe oxygen is too low pls clean the manhole \n \n");
          }

      }
}


float Oxygenperc()
{ /*
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
    Serial.print("% \n \n"); }*/

  const float A_REF =1.5e3;
  const float Scalc =(1/0.6);
  float v1;
  float oxy=0.0;
  float v2=0.0;

  v1=analogRead(A0);      // To read the value form the oxugen sensor
  
  v2=(v1*A_REF)/1024;     // To convert the value in mV and by the graph we can now convert it into percentage
  
  oxy =v2*Scalc;          /// To convert the mV value in Percentage
  
    Serial.print("Oxygen Value=");
    Serial.print(oxy,2); 
    Serial.print("% \n");
    Serial.print("Oxygem value=");
    Serial.print(v2,2); 
    Serial.print("mV    \n \n");
  
  return oxy;
}

float distancecalc()
{
    float t, d, h;
    delay(50);
    digitalWrite(tp, LOW);    //  initialize the trigger pin of ultrasonic to 0 
    delayMicroseconds(2);
    
    digitalWrite(tp, HIGH);   // sends an echo for 10 micro seconds on ultrasonic
    delayMicroseconds(10);
    
    digitalWrite(tp, LOW);    // ends the echo
    
    t = pulseIn(ep, HIGH);    // senses the echo and sends the time required to gets the pulse
    
    d = t*((1 / 2) * 29.2);   // convert the time into distance in centimeters
    h = d/1000;
    
    Serial.print(" \n");
    Serial.print(h);          // print the following on serial monitor
    Serial.print(" cm\n");    
    return h;
}

float methane()
{
  return 0;
}
