#include <SoftwareSerial.h>
#define SensorPin A0;  // Oxygen Sensor pin
#define SensorPin A1;
int tp = 3;            // ultrasonic trigger pin
int ep = 4;            // ultrasonic echo pin
int LR = 6;            // LED Red
int LG = 8;            // LED Green
int LO = 7;            // LED Orange
int KEY = 13;          // for stopping the timer

//SoftwareSerial Serial(10, 11); // RX | TX


void setup() 
{
        //Serial.begin(4800);   // to send data to serial monitor at 4800 baud rate
        pinMode(LR,OUTPUT);     // LED's to set as ouput 
        pinMode(LO,OUTPUT);
        pinMode(LG,OUTPUT);
        
        pinMode(tp, OUTPUT);    // trigger pin as ouput
        pinMode(ep, INPUT);     // echo pin as input
        pinMode(A1, INPUT);
        analogReference(INTERNAL);
        pinMode(A0, INPUT);     // analog pin as input for oxygen sensor
        pinMode(KEY, INPUT);    // key to stop the timer
        Serial.begin(9600);     // to send data to bluetooth at 9600 baud rate
}

void loop()
{ //float d,o2;
  // to change the name or password code for bluetooth check the bluetooth file
  
  float d  = distancecalc(); //function for distance calculate
  float o2 = Oxygenperc();   //function for oxygen calculate
  float Ms = methane();
 
  // To send data to smartphone through Bluetooth
 
  if (Serial.available() > 0)  
  {
       char rechar = Serial.read(); // To get data from Bluetooth
        if(rechar =='A')      // If Button Clicked For Distance
        {  
          
          Serial.print((int)d);
           delay(500);
        }
        else if(rechar=='O')  // If Button Clicked For Oxygen  
        {
          
           Serial.print((int)o2);
           delay(500);
        }
   }


   
   // To show the Output on Serial Monitor And LED's
   
   if (d < 100)     // to check if the distance is less than threshold
      {
          Serial.print("The Distance is to low = ");
          Serial.print(d);
          delay(1000);
          Serial.print(" cm \n");
          digitalWrite(LR, HIGH);
          delay(5000);
      }
   
   else 
      {
      
          digitalWrite(LO, HIGH);
          Serial.print("The Distance is correct now we can measure the oxygen & Methane \n \n");
          delay(5000);
          if (o2 >= 19.5 && Ms > 100)     // to check if the Oxygen is less than threshold
              {
                  digitalWrite(LG, HIGH);
                  Serial.print("Oxygen Percentage=  ");
                  Serial.print(o2);
                  Serial.print("Methane Percentage=  ");
                  Serial.print(Ms);
                  Serial.print("% \n");
                  Serial.print("THE MANHOLE IS SAFE FOR OPERATION WORK CAN BE DONE  \n \n");
                  //calltimer();
                  digitalWrite(LR, LOW);
              }
    
          else if (o2 < 19.5)
     
          {
                  digitalWrite(LR, HIGH);
                  Serial.print("THe oxygen is too low pls clean the manhole \n \n");
          }
          else if(Ms < 100)
          {       digitalWrite(LR, HIGH);
                  Serial.print("THe methane is too low pls clean the manhole \n \n");
          }

      }
}


float Oxygenperc()
{ delay(1100);
  /*
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
    
    //d = t*((1 / 2) * 29.2);   // convert the time into distance in centimeters
    h=(t/2)*0.0343;  
  
   // h = d/1000;
    
    Serial.print(" \n");
    Serial.print(h);          // print the following on serial monitor
    Serial.print(" cm\n");    
    return h;
}

float methane()
{ int Ms = analogRead(A1);
Ms = Ms +50;
  Serial.println(Ms);
  return Ms;
}

void calltimer()
{
 /* int count=0;
  int minutes=0;
  int OFF = digitalRead(KEY);
  digitalWrite(LO, HIGH);
  digitalWrite(LG, HIGH);
  while(OFF == 0)
  { delay(1000);
    ++count;
    if(count == 60)
    {
      count = 0;
      ++minutes;
      Serial.println(minutes);
      Serial.print(" minutes");
    }
  }
   if(OFF == 1)
   {
    Serial.println("The amount of time the worker was working in the manhole was");
    Serial.println(minutes);
    Serial.println("min");  
    }*/
}
