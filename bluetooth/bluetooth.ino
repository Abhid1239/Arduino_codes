
void setup() {


}

void loop() {
   BTSerial.begin(38400); for at commands baud rate of bluetooth
    digitalWrite( any pin to maek the key pin high of bluetooth,HIGH); //only for bluetooth
    Serial.println("Enter AT commnads:");
    if(BTSerial.available())
     Serial.write(BTSerial.read());
    if(Serial.available())
     BTSerial.write(Serial.read());
}
