void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
   pinMode(A0,INPUT); 
analogReference(INTERNAL);


}

void loop() {
  // put your main code here, to run repeatedly:


float  VALUE=analogRead(A0);
  float MV=VALUE*(1.47564/1024)*1000;
  Serial.println(VALUE);
  Serial.println("    VALUE READED");
  Serial.println(MV);
  Serial.println("    MILLI VOLt");
  Serial.println("OXYGEN PERCENTAGE");
  Serial.println((MV*100)/60,4);
  
  delay(1000);
}
