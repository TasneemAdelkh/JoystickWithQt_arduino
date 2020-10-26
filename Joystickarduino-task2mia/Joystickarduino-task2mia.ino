#include <SoftwareSerial.h>
#include <Wire.h>  
#define redled A5
#define Pressure A4
const int MPU = 0x68;
const int pressure_minv =102;
const int pressure_maxv= 921;
float GyroX,GyroY,GyroZ,elapsedTime, currentTime=0, previousTime,gyroAngleX, gyroAngleY,yaw;
int pressurevalue;
String command,speedH,speedV;
int speedHI,speedVI;
char Vbuffer[4];
char Hbuffer[4];
SoftwareSerial sensors_send(2,3);

int pressure(){
  int pressurevalue;
  pressurevalue= analogRead(Pressure);
  pressurevalue=map(pressurevalue,pressure_minv,pressure_maxv,0,100);
  return pressurevalue;
}

void IMU(){
  Wire.beginTransmission(MPU);   //beginning communication with MPU sensor
  Wire.write(0x43);              // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;  
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
    gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
    gyroAngleY = gyroAngleY + GyroY * elapsedTime;
    yaw =  yaw + GyroZ * elapsedTime;
    sensors_send.print(gyroAngleX);
    sensors_send.print(",");
    sensors_send.print(gyroAngleY);
    sensors_send.print(",");
    sensors_send.print(yaw);
}
void speed_send(int speedH,int speedV){
  Wire.beginTransmission(20);
  Wire.write(speedH);
  Wire.write(speedV);
  Wire.endTransmission();
  delay(100);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(redled,OUTPUT);
  
Serial.begin(9600);
sensors_send.begin(9600);
 Wire.begin();                      // Initialize i2c comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset to start the MPU to work- place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  command=Serial.readString();
  int Vindex=command.indexOf('V');
  speedH=command.substring(1,Vindex);
  speedV=command.substring(Vindex+1);
  speedHI =speedH.toInt();
 speedVI  =speedV.toInt();
  digitalWrite(redled,HIGH);
  speed_send(speedHI,speedVI); 
}
pressurevalue= pressure();
sensors_send.print(pressurevalue);
sensors_send.print(",");
IMU();
sensors_send.flush();
delay(1000);

}
