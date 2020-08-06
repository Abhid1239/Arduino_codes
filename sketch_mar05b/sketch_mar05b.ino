

void setup() {
  // put your setup code here, to run once:


Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  byte rc;
  int a=976; 
  int oxy1=a/100; int oxy2=(a%100)/10;   int oxy3 =a%10;

  int d=123;
    int di1=d/100; int di2=(d%100)/10; int di3 =d%10;

  



  
  if (Serial.available() > 0 )
  {
     rc = Serial.read();
    if(rc == 48)
    {
     
        Serial.print((char)oxy1);
        Serial.print((char)oxy2);
        Serial.print((char)oxy3);
        
        
      
      }
             delay(200);

      rc = Serial.read();
    if(rc == 65)
    {
     
        Serial.print((char)di1);
        Serial.print((char)di2);
        Serial.print((char)di3);
        
        
      
      }
       delay(200);
    }


delay(1000);
}
