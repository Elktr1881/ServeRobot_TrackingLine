#include "HX711.h"

#define EncoMotor_R 2
#define EncoMotor_L 3

#define EN1 5
#define EN2 6
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define buz 13

//Sensor berat
int HX_SC = 7; 
int HX_DT = 4;

HX711 scale;
float calibration_weight = -202.00;

uint8_t linePin[6] = {A0, A1, A2, A3, A4, A5};
int lineValue[6], detect, noTable;
int flag = 0;
int PWM[2];
float TEMP[2];
bool line[6];

void buzzer()
{
  digitalWrite(buz,HIGH);delay(300);
  digitalWrite(buz,LOW);delay(300);
  digitalWrite(buz,HIGH);delay(300);
  digitalWrite(buz,LOW);
}

void setup() {
 Serial.begin(115200);

  scale.begin(HX_DT, HX_SC);
  scale.set_scale(); scale.tare();
  long zero_factor = scale.read_average();
  
 pinMode(EncoMotor_R,INPUT);
 pinMode(EncoMotor_L,INPUT);

  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(buz,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(EncoMotor_R),EncProcessR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(EncoMotor_L),EncProcessL,CHANGE);

  for(int i=0; i<6; i++)
  {
    pinMode(linePin[i],INPUT);
  }
  buzzer();
}

void loop() {

  EncoderRead();
  getLine();
  
  GetServiceTable(2);
  
//================ Tunning PID :=============//

//  PID(120,120,1.2,0.001,0.1);
//  PID(120,120,0.2,0.0003,0001);
//  tracking_right(120,0.25,0.0005,1.5);
  
  
  Serial.print(" Speed: ");
  Serial.print(TEMP[0]); Serial.print(" ");
  Serial.print(TEMP[1]); Serial.print(" ");
  Serial.print("PWM: ");
  Serial.print(PWM[0]); Serial.print(" ");
  Serial.print(PWM[1]); Serial.print("  ");
//  Serial.print(" Weight: ");
//  Serial.print(weightRead());Serial.print("  ");
  Serial.println();
}
