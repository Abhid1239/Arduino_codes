
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "nodemcu-5ac5f.firebaseio.com"
#define FIREBASE_AUTH "2MLxe1NPJOn9xmU3Fhi8xi8oLZsw0Fn3J8RW8mBb"
#define WIFI_SSID "punam"
#define WIFI_PASSWORD "#prashant@6.12"


#include <SoftwareSerial.h>
int tp=2; // pin numbers ahet connection che
int ep=0;
int LR=16;
int LG=5;
int LO=4;

void setup() {
  Serial.begin(9600);
  
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(A0,INPUT);  //oxygen sensor
  digitalWrite(LO,LOW);
  digitalWrite(LR,LOW);
  digitalWrite(LG,LOW);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;
float  d = 10.0;
void loop() {

  
  float d=distancecalc();


  // set value
  Firebase.setFloat("d", d);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      
      }
  delay(500);

  float o2=percentagecalc();

 
//  
//  if(d<50)
//  {
//    Serial.print("Too LOW PLS SAVE YOUR COMPONENTS");
//    digitalWrite(LR,HIGH);
//  }
//  else{
//    if(o2>20 && o2<30)
//  }
//  {
//    digitalWrite(LO,HIGH);
//   Serial.print("Oxygen Is Low in The MAnhole Pls Clean The Manhole");
//   }
//   else if(o2<15)
//  {
//   digitalWrite(LR,HIGH);
//   Serial.print("NO HUMAN CAN SURVIVE IN THIS");
//   }
//   digitalWrite(LG,HIGH);
//   Serial.print("THE MANHOLE IS SAFE FOR OPERATION WORK CAN BE DONE");
//     
  }
   


float percentagecalc()
{ 
  pinMode(A0,INPUT_PULLUP);
  delay(1);
  bool r= analogRead(A0)<900; // 900 is not fix depends on the sensor for ke50
  float op=0.0;
  if(r)
  {
    pinMode(A0,INPUT);
    delay(1);
    float mV=analogRead(A0);
    Serial.print("KE-25 value =");
    Serial.print(mV);
    float op=(mV*3000/992)/0.6;    // this equation can be change depending on the oxygen sensor refernece ghetla ahe
    Serial.print("Oxygen Percentage=");
    
  // set value
  Firebase.setFloat("op", op);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      
      }
  delay(2000);



  // set value
  Firebase.setFloat("d", d);
  d = d+1;
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      
      }
  delay(500);
  
    Serial.print(op);
    Serial.print("% \n \n");
   
  }
 return op;
}

float distancecalc()
{
    float t,d,h;
 delay(50);
digitalWrite(tp, LOW);
delayMicroseconds(2);
digitalWrite(tp, HIGH);
delayMicroseconds(10);
digitalWrite(tp, LOW);
//  t=pulseIn(ep,HIGH);

 t=50;
  d=t*0.034/2;
  h=d;

 
  Serial.print(d);
  Serial.print("cm\n");
  delay(1000);
  digitalWrite(LG,HIGH);
  return h;
}
