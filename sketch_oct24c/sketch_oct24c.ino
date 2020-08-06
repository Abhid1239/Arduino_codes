#include <SoftwareSerial.h>
//SoftwareSerial sserial(11, 10); // RX | TX
void setup() {
  // put your setup code here, to run once:

       // to send data to bluetooth at 9600 baud rate
        
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.begin(9600);
   Serial.print("50000          ");
    delay(5000);
   Serial.begin(4800);
         Serial.print("500");

}
