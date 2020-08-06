#include <SoftwareSerial.h>
#define SensorPin A0;  // Oxygen Sensor pin

int tp = 3;            // ultrasonic trigger pin
int ep = 4;            // ultrasonic echo pin
int LR = 7;            // LED Red
int LG = 8;            // LED Green
int LO = 6;             // LED Orange

SoftwareSerial BTserial(10, 11); // RX | TX
void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:
  
  BTserial.print("50000");
  BTserial.print("\n \n"); 
  BTserial.print("400"); 
}
