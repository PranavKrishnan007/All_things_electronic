#include <SoftwareSerial.h>
#include <Servo.h>

Servo myservo;
SoftwareSerial BTSerial(10,9);

int LDR=0;
char bluetooth;

void setup()
{
  myservo.attach(2);
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(13,OUTPUT);//Yellow Light
  pinMode(12,OUTPUT);//red light
}

int door = 0, light = 0;

void loop()
{
  LDR=map(analogRead(A1),0,1023,0,255);
  if (BTSerial.listen()>0)//where value == the value we get in adjusting LDR
  {
// -------------------- door rotation -----------------------
    if(BTSerial.available()>=0 && LDR <= 100){
      bluetooth = BTSerial.read();
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
        digitalWrite(13, LOW);
        Serial.println("Lights are OFF");
        BTSerial.write("Lights are OFF");
      }
      else if(bluetooth == 'O'){
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        Serial.println("Lights are ON");
        BTSerial.write("Lights are ON");
      }
    }
    else if(BTSerial.available()>= 0 && LDR >= 100){
      bluetooth = BTSerial.read();
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
    }
    else if (BTSerial.available()>= 0 && (BTSerial.read()=='W')){
      myservo.write(0);
      Serial.println("Intruder mode! calling the authorities.");
      BTSerial.write("Intruder mode! calling the authorities.");
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    }
  }
}