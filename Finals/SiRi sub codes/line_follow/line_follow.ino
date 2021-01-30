#include <Encoder.h>

//MOTOR DRIVE
#define EN_L 28 //left
#define PWM_L 6
#define INA_L 26  
#define INB_L 29//previous pin as 26

#define EN_R 27 //right
#define PWM_R 5
#define INA_R 23  
#define INB_R 25

//ENCODED MOTORS
#define ENCODE_L_A 20
#define ENCODE_L_B 21
#define ENCODE_R_A 18
#define ENCODE_R_B 19

//LEFT RIGHT IR SENSORS
#define l5_PORT A9
#define r5_PORT A8

//REYKHA SENSOR
#define l4_PORT A7
#define l3_PORT A6
#define l2_PORT A5
#define l1_PORT A4
#define r1_PORT A3
#define r2_PORT A2
#define r3_PORT A1
#define r4_PORT A0

void readSensors();
void printSensorData();

const int  SPEED =90;

#define MOTORS_ON \
    digitalWrite(EN_L,HIGH);digitalWrite(EN_R,HIGH);
#define MOTORS_OFF \
    digitalWrite(EN_L,LOW);digitalWrite(EN_R,LOW);
#define MOTOR_L_FORWARD \
    digitalWrite(INA_L,HIGH);digitalWrite(INB_L,LOW);
#define MOTOR_R_FORWARD \
    digitalWrite(INA_R,HIGH);digitalWrite(INB_R,LOW);
#define MOTOR_L_BACKWARD \
    digitalWrite(INA_L,LOW);digitalWrite(INB_L,HIGH);
#define MOTOR_R_BACKWARD \
    digitalWrite(INA_R,LOW);digitalWrite(INB_R,HIGH);

void setup() {
   // motor driver
   
   pinMode(EN_L,OUTPUT);
   pinMode(PWM_L,OUTPUT);
   pinMode(INA_L,OUTPUT);
   pinMode(INB_L,OUTPUT);
   
   pinMode(EN_R,OUTPUT);
   pinMode(PWM_R,OUTPUT);
   pinMode(INA_R,OUTPUT);
   pinMode(INB_R,OUTPUT);  

  Serial.begin(9600);
  delay(5000);
}


int rekhaThress=70,IRThress=70; // thresshold values
int line;

int l5,l4,l3,l2,l1,r1,r2,r3,r4,r5;

void printSensorData(){
  Serial.print(l5);Serial.print('\t');
  Serial.print(l4);Serial.print('\t');
  Serial.print(l3);Serial.print('\t');
  Serial.print(l2);Serial.print('\t');
  Serial.print(l1);Serial.print('\t');
  Serial.print(r1);Serial.print('\t');
  Serial.print(r2);Serial.print('\t');
  Serial.print(r3);Serial.print('\t');
  Serial.print(r4);Serial.print('\t');
  Serial.print(r5);Serial.print('\t');
  Serial.println();
}
int get_digital(int port,int thresshold){
  int value = analogRead(port);
  return value<=thresshold? 1:0;
  //return analogRead(port);
}
void readSensors(){
  l5=get_digital(l5_PORT,IRThress);// 0 White
  r5=get_digital(r5_PORT,IRThress);
  l4=get_digital(l4_PORT,rekhaThress);//0 Black
  l3=get_digital(l3_PORT,rekhaThress);
  l2=get_digital(l2_PORT,rekhaThress);
  l1=get_digital(l1_PORT,rekhaThress);
  r1=get_digital(r1_PORT,rekhaThress);
  r2=get_digital(r2_PORT,rekhaThress);
  r3=get_digital(r3_PORT,rekhaThress);
  r4=get_digital(r4_PORT,rekhaThress);
}

void moveRobot(int leftVal, int rightVal){

  MOTORS_ON;

  if(leftVal>=0){ MOTOR_L_FORWARD; }
  else {MOTOR_L_BACKWARD;}

  if(rightVal>=0){ MOTOR_R_FORWARD;}
  else {MOTOR_R_BACKWARD;}

  analogWrite(PWM_L,abs(leftVal));
  analogWrite(PWM_R,abs(rightVal));
}
void stopRobot(){
  MOTORS_OFF;
}
void lineFollow(){
    readSensors();
    line = r1+r2+r3+r4-l1-l2-l3-l4;
    if(line>0){
      moveRobot(SPEED+10,0);
    }
    else if(line<0){
      moveRobot(0,SPEED+10);
    }
    else{
      moveRobot(SPEED,SPEED);
    }  
}

void loop() {
  lineFollow();
  readSensors();
  printSensorData();
}
