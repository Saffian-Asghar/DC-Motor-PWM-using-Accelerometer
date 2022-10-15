#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

const int IN1 = 6;
const int IN2 = 7;

const int IN3 = 8;
const int IN4 = 9;

// 3 and 5 on Leonardo are PWMs
const int ENA = 5;
const int ENB = 3;

int speedControl = 0; // Thats our PWM Variable

void setup() 
{
  
  Serial.begin(115200);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Sensor NOT FOUND!");
    delay(500);
  }
}


void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  Serial.println(rawAccel.XAxis);

  speedControl = rawAccel.XAxis / 45 ;
  if(speedControl > 255){
    speedControl = 255 // Limit to max PWM
  }
  // 48 because upon checking the values of x axis usual values from 0 to 12000 from 0 degrees to 90 degrees tilt. 45 corresponds to x axis reading of 1200 so approx 266
  if(rawAccel.XAxis > 400){
    spin(1, speedControl);
  }
  else{
    spin(0, speedControl);
  }
}
void spin(int direction, int speed){
  //control speed 
  analogWrite(ENA, speed);
  analogWrite(ENB, speed); 
//control direction 1 means clockwise in our circuit
  if(direction == 1){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
  else{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }

}


