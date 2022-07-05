#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
SoftwareSerial BTSerial(10,9);

int LDR=0;
char bluetooth;

void setup()
{
  myservo.attach(3);
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(13,OUTPUT);//Yellow Light
  pinMode(12,OUTPUT);//red light
}

void loop()
{
  LDR=map(analogRead(A1),0,1023,0,255);
  if (BTSerial.isListening()>0)//where value == the value we get in adjusting LDR
  {
// -------------------- door rotation -----------------------
    if( LDR <= 100){
      bluetooth = BTSerial.read();
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      if(BTSerial.available()>=0 ){
        if (bluetooth=='o')
      {
        for(int i = 0; i < 180; i++){
          myservo.write(180);
        }
        Serial.println("The Door is Opened");
        BTSerial.println("The Door is Opened");
      }
      else if(bluetooth=='c')
      {
        myservo.write(0);
        Serial.println("The Door is closed");
        BTSerial.println("The Door is closed");
      }
      if (bluetooth=='W'){
      myservo.write(0);
      Serial.println("Intruder mode! calling the authorities.");
      BTSerial.write("Intruder mode! calling the authorities.");
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      delay(100);
    }
      }
      delay(1000);
    }
    else if(LDR >= 100){
      bluetooth = BTSerial.read();
      if(BTSerial.available()>= 0)
      {
        if(bluetooth=='W'){
      myservo.write(0);
      Serial.println("Intruder mode! calling the authorities.");
      BTSerial.write("Intruder mode! calling the authorities.");
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      delay(100);
    }
      if (bluetooth=='o')
      {
        myservo.write(180);
        Serial.println("The Door is Opened");
        BTSerial.println("The Door is Opened");
      }
      else if(bluetooth=='c')
      {
        myservo.write(0);
        Serial.println("The Door is closed");
        BTSerial.println("The Door is closed");
      }
      if(bluetooth == 'F'){
        digitalWrite(12, LOW);
        Serial.println("Lights are OFF");
        BTSerial.write("Lights are OFF");
      }
      else if(bluetooth == 'O'){
        digitalWrite(12, HIGH);
        Serial.println("Lights are ON");
        BTSerial.write("Lights are ON");
      }
      if(bluetooth == 'Y'){
        digitalWrite(13, HIGH);
        Serial.println("Lights are ON");
        BTSerial.write("Lights are ON");
      }
      else if(bluetooth == 'y'){
        digitalWrite(13, LOW);
        Serial.println("Lights are OFF");
        BTSerial.write("Lights are OFF");
      }
      }
      delay(1000);
    }
  }
}