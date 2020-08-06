void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
   pinMode(A0,INPUT); 
    analogReference(INTERNAL);

}

void loop() { const float A_REF = 1.5e3;
     const float Scalc = (1/0.6);

     float v1;
     float op = 0.0;
     float v2 = 0.0;
     pinMode(A0, INPUT); 
     v1 = analogRead(A0);
     v2 = (v1 * A_REF) / 1024;
     op = v2 * Scalc;
    Serial.println("Oxygen value: ");
     Serial.print(v1);
     Serial.print("    ");
     Serial.print(v2,4);
     Serial.print("mV    ");
     Serial.println(op,4);//prints the Oxygen value
     Serial.println("%");
     delay(5000);
  // put your main code here, to run repeatedly:

}
