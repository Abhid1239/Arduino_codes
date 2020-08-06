// Arduino Code for reading data from oxygen sensor and ultrasonic sensor and send it to application via bluetooth

 
int trigger_pin = 4; // trigger pin of ultrasonic sensor connected to pin 4
int echo_pin = 3; // echo pin of ultrasonic sensor connected to pin 3

void setup() {
  
  pinMode( trigger_pin, OUTPUT ); // assigning trigger_pin as output
  pinMode( echo_pin, INPUT);      // assigning echo_pin as input
  pinMode( A0, INPUT);            // oxygen analog input on A0 pin         
  
  analogReference(INTERNAL);      // reference assign as internal for a to d conversion

  Serial.begin(9600);             // serially data sending at 9600 baud rate
}

void loop() {
  
   int oxy_val = (percentage_calc()*10);                                          // function to calc oxygen percentage
  
   int oxy1 = oxy_val/100; int oxy2 = (oxy_val%100)/10;  int oxy3 = oxy_val%10;   // value to bit to send data to bluetooth  
   
   int dist_val=(int)dist_calc();
   
   int di1 = dist_val/100; int di2 = (dist_val%100)/10;  int di3 = dist_val%10;   // value to bit to send data to bluetooth  

   // code to send data from arduino to bluetooth
 
   if (Serial.available() > 0 )                 //if bluetooth is connected and serial is available               
   {
      byte read_char = Serial.read();           // read char send by the application 
      if(read_char == 48)                       // if char is 'A' i.e '48' 
      {
          Serial.print((char)oxy1);             // send oxygen data to application
          Serial.print((char)oxy2);
          Serial.print((char)oxy3);
      }
      delay(200);
     
      read_char = Serial.read();                // again read data from serial 
      if(read_char == 65)                       // If char is 'a' i.e '65'
      {
          Serial.print((char)di1);              // send distance value to application
          Serial.print((char)di2);
          Serial.print((char)di3);
      }
      delay(200);
   }
}


float percentage_calc()                // function to calculate percentage of oxygen
{   
  const float A_REF = 1.5e3;          // setting analog refernece at 1.5e3
  const float Scalc = (1/0.6);        // formula to conv digital to percentage

  pinMode(A0, INPUT);
   
  float oxy_val_analog = analogRead(A0);                        // read analog oxygen value 
  float analog_to_digital = (oxy_val_analog * A_REF) / 1024;    // coversion into digital
  float oxy_perc = analog_to_digital * Scalc;                   // final percentage value in float
  
  delay(100);

 return oxy_perc;             // return oxygen value
}


float dist_calc()                              // function to calculate the distance between manhole and sensors
{
    delay(100);
    digitalWrite(trigger_pin, LOW);            // Initially set trigger to low
    delayMicroseconds(2);
    digitalWrite(trigger_pin, HIGH);           // send high to trigger pin to send echo
    delayMicroseconds(10);
    digitalWrite(trigger_pin, LOW);            // set trigger pin to low
  
    float echo_rec = pulseIn(echo_pin,HIGH);   // read the echo recived after hitting the target
    float distance = echo_rec * 0.034/2 ;      // formula to convert echo rec to distance in centimeters 
    
    return distance;
}
