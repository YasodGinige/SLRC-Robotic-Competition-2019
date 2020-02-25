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

const int  SPEED =80;

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

   // encoded motors read
   
/*   pinMode(ENCODE_L_A,INPUT);
   pinMode(ENCODE_L_B,INPUT);
   pinMode(ENCODE_R_A,INPUT);
   pinMode(ENCODE_R_B,INPUT);
*/
  Serial.begin(9600);
  delay(5000);
}

void loop() {
 //lineFollow();
 //stopRobot();
 // moveRobot(SPEED,SPEED);
// moveDistance(14,-102);
  right90();
 delay(10000);
}
