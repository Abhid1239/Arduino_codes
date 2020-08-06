
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 

 
}

void loop() {
 if (Serial.available() > 0)  
  {
       byte rechar = Serial.read(); // To get data from Bluetooth
        if(rechar ==65)      //write ascii code If Button Clicked For Distance
        {  
          int  d=10;
          Serial.print((int)d);
           delay(500);
        }
        else if(rechar==79)  // If Button Clicked For Oxygen  
        {
          int o2=20;
           Serial.print((int)o2);
           delay(500);
        }
}
}
