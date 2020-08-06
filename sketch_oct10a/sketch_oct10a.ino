int LR=7;
int LG=5;
int LO=6;
void setup() {
  pinMode(LR,OUTPUT);
  pinMode(LO,OUTPUT);
  pinMode(LG,OUTPUT);

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
        digitalWrite(LO,HIGH);
  digitalWrite(LR,HIGH);
  digitalWrite(LG,HIGH);
  delay(1000);
  digitalWrite(LO,LOW);
  digitalWrite(LR,LOW);
  digitalWrite(LG,LOW);
  delay(1000);
      digitalWrite(LO,HIGH);
  digitalWrite(LR,HIGH);
  digitalWrite(LG,HIGH);
  delay(1000);
  digitalWrite(LO,LOW);
  digitalWrite(LR,LOW);
  digitalWrite(LG,LOW);

}
