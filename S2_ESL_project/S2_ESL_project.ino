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
  pinMode(13,OUTPUT);//Yellow Light
  pinMode(12,OUTPUT);//Green light
  pinMode(11,OUTPUT);
}

void loop()
{
  LDR=map(analogRead(A1),0,1023,0,255);
  if (BTSerial.listen()>0 && LDR <=50)//where value == the value we get in adjusting LDR
  {
    int count=0;
    if (count==0){
    Serial.println("WELCOME.....THE LIGHTS ARE TURNED ON");
    BTSerial.write("WELCOME.....THE LIGHTS ARE TURNED ON");
    count+=1;}
    digitalWrite(13,HIGH);//Yellow light
    digitalWrite(12,HIGH);//Red light
    //digitalWrite(11,HIGH); 
    if (BTSerial.available()>0){
      bluetooth=BTSerial.read();
      if (bluetooth=='o')
      {
        for(int rotate=0;rotate<=180;rotate++)
        {
          myservo.write(rotate);
        }
        Serial.println("The Door is Opened");
        BTSerial.println("The Door is Opened");
      }
      else if(bluetooth=='f')
      {
        for (int rotate=180;rotate>=0;rotate--)
        {
          myservo.write(rotate);
        }
        Serial.println("The Door is closed");
        BTSerial.println("The Door is closed");
      }
      else if (bluetooth=='O')
      {
        digitalWrite(12,HIGH);
        digitalWrite(13,LOW);
        printf("The Red Light is on");
      }
      else if(bluetooth=='F')
      {
        digitalWrite(13,HIGH);
        digitalWrite(12,LOW);
        BTSerial.println("The Yellow Light is on");
        Serial.println("The Yellow light is on:");
      }
  }
}
