
int inputPin = 2; // choose input pin (for Infrared sensor) 
int val = 0; // variable for reading the pin status
void setup() {
  
   pinMode(inputPin, INPUT);
   Serial.begin(9600);// declare Infrared sensor as input


}

void loop() {

   val = digitalRead(inputPin); // read input value 
   if (val == HIGH)
   { // check if the input is HIGH
     Serial.println(val); 
     delay(1000);// turn LED OFF   
   } 
   else 
   { 
       Serial.println(val);  
       delay(1000);// turn LED ON 
   } 
  // put your main code here, to run repeatedly:

}
