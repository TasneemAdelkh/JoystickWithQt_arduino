#include <Wire.h>
#define Hin1 5
#define Hin2 4
#define Hin3 3
#define Hin4 2
#define Hena 11
#define Henb 10
#define Vin1 6
#define Vin2 7
#define Vin3 8
#define Vin4 9
#define Vena 12
#define Venb 13
String DIRECTION,speeds[2];
int speedVI,speedHI,flag=0;
void setup() {
  // put your setup code here, to run once:
Wire.begin(20);
Serial.begin(9600);
pinMode(Hin1,OUTPUT);
pinMode(Hin2,OUTPUT);
pinMode(Hin3,OUTPUT);
pinMode(Hin4,OUTPUT);
pinMode(Hena,OUTPUT);
pinMode(Henb,OUTPUT);
pinMode(Vin1,OUTPUT);
pinMode(Vin2,OUTPUT);
pinMode(Vin3,OUTPUT);
pinMode(Vin4,OUTPUT);
pinMode(Vena,OUTPUT);
pinMode(Venb,OUTPUT);
}
void receiving_speed(){
  if(Wire.available()){
    if(flag==0){
      speeds[0]=Wire.readString();
      flag=1;
    }
    else if(flag==1)
    {
      speeds[1]=Wire.readString();
    }
  }
  speedHI=speeds[0].toInt();
  speedVI=speeds[1].toInt();
}
void UP(int Vspeed){
  digitalWrite(Vin1,HIGH);
  digitalWrite(Vin2,LOW);
  digitalWrite(Vin3,HIGH);
  digitalWrite(Vin4,LOW);
  digitalWrite(Vena,Vspeed);
  digitalWrite(Venb,Vspeed);
}
void DOWN(int Vspeed){
   digitalWrite(Vin2,HIGH);
  digitalWrite(Vin1,LOW);
  digitalWrite(Vin4,HIGH);
  digitalWrite(Vin3,LOW);
  digitalWrite(Vena,Vspeed);
  digitalWrite(Venb,Vspeed);
}
void FORWARD(int Hspeed){
  digitalWrite(Hin1,HIGH);
  digitalWrite(Hin2,LOW);
  digitalWrite(Hin3,HIGH);
  digitalWrite(Hin4,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void BACKWARD(int Hspeed){
  digitalWrite(Hin2,HIGH);
  digitalWrite(Hin1,LOW);
  digitalWrite(Hin4,HIGH);
  digitalWrite(Hin3,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void RIGHT(int Hspeed){
  digitalWrite(Hin1,HIGH);
  digitalWrite(Hin2,LOW);
  digitalWrite(Hin4,HIGH);
  digitalWrite(Hin3,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void LEFT(int Hspeed){
  digitalWrite(Hin2,HIGH);
  digitalWrite(Hin1,LOW);
  digitalWrite(Hin3,HIGH);
  digitalWrite(Hin4,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void RotateRIGHT(int Hspeed){
  digitalWrite(Hin1,HIGH);
  digitalWrite(Hin2,LOW);
  digitalWrite(Hin3,LOW);
  digitalWrite(Hin4,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void RotateLEFT(int Hspeed){
  digitalWrite(Hin1,LOW);
  digitalWrite(Hin2,LOW);
  digitalWrite(Hin3,HIGH);
  digitalWrite(Hin4,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
}
void PAUSE(int Hspeed,int Vspeed){
  digitalWrite(Hin1,LOW);
  digitalWrite(Hin2,LOW);
  digitalWrite(Hin3,LOW);
  digitalWrite(Hin4,LOW);
  digitalWrite(Hena,Hspeed);
  digitalWrite(Henb,Hspeed);
  digitalWrite(Vin1,LOW);
  digitalWrite(Vin2,LOW);
  digitalWrite(Vin3,LOW);
  digitalWrite(Vin4,LOW);
  digitalWrite(Vena,Vspeed);
  digitalWrite(Venb,Vspeed);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  DIRECTION=Serial.readString();
  if(DIRECTION=="UP")
    UP(speedVI);
  else if (DIRECTION=="DOWN")
    DOWN(speedVI);
    else if(DIRECTION=="FORWARD")
  FORWARD(speedHI);
  else if (DIRECTION=="BACKWARD")
  BACKWARD(speedHI);
  else if (DIRECTION=="RIGHT")
  RIGHT(speedHI);
  else if (DIRECTION=="LEFT")
  LEFT(speedHI);
  else if (DIRECTION=="RotateRIGHT")
  RotateRIGHT(speedHI);
  else if(DIRECTION == "RotateLEFT")
  RotateLEFT(speedHI);
  else if (DIRECTION=="PAUSE")
  PAUSE(speedHI,speedVI);
}
}
