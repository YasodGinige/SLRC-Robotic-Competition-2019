#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Encoder.h>
#include <Wstring.h>
#include <Servo.h>
#include <SPI.h>

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

//COLOUR SENSOR
#define CS_M_POW 48
#define CS_M_OE 36 // middle colour sensor
#define CS_M_S0 40
#define CS_M_S1 38
#define CS_M_S2 42
#define CS_M_S3 44
#define CS_M_OUT 46

#define CS_R_POW 49
#define CS_R_OE 41 // right colour sensor 49 power 47 out 45s2 43s3 41oe 39s0 37s1
#define CS_R_S0 39
#define CS_R_S1 37
#define CS_R_S2 45
#define CS_R_S3 43
#define CS_R_OUT 47

//ULTRASONIC SENSOR
#define US_L_TRIG 33// left 
#define US_L_ECO 35

#define US_R_TRIG 34//right 
#define US_R_ECO 32

//MOTOR DRIVE
#define EN_L 28 //left
#define PWM_L 6
#define INA_L 26  
#define INB_L 29

#define EN_R 27 //right
#define PWM_R 5
#define INA_R 23  
#define INB_R 25

//ENCODED MOTORS
#define ENCODE_L_A 20
#define ENCODE_L_B 21
#define ENCODE_R_A 18
#define ENCODE_R_B 19

//SERVO MOTORS
#define ARM_L_SERVO 12// forward
#define ARM_R_SERVO 13//rear

#define RED_SERVO 9
#define GREEN_SERVO 11
#define BLUE_SERVO 10

// RADIO SIGNAL MODULE
#define RADIO_CSN 8
#define RADIO_CE 7

//LED
#define RED_LED A15
#define GREEN_LED A14
#define BLUE_LED A13
#define WHITE_L_LED 31
#define WHITE_R_LED 30

//PUSH BUTTONS
#define CALLIBERATE_BUTTON A10
#define ROUND_BUTTON A11
#define DELAY_BUTTON A12

//BUZZER
#define BUZZER 4

const int SPEED=90;

const int n=8; // grid size
int taskCounter=2;

void dropCoin(int colour);
void setupServos();
void pillarIdentificationLoop();
void gridTraverseLoop();

void setup() {
  //  colour sensor
   pinMode(CS_M_POW,OUTPUT);
   pinMode(CS_M_OE,OUTPUT);
   pinMode(CS_M_S0,OUTPUT);
   pinMode(CS_M_S1,OUTPUT);
   pinMode(CS_M_S2,OUTPUT);
   pinMode(CS_M_S3,OUTPUT);
   pinMode(CS_M_OUT,INPUT);

   pinMode(CS_R_POW,OUTPUT);
   pinMode(CS_R_OE,OUTPUT);
   pinMode(CS_R_S0,OUTPUT);
   pinMode(CS_R_S1,OUTPUT);
   pinMode(CS_R_S2,OUTPUT);
   pinMode(CS_R_S3,OUTPUT);
   pinMode(CS_R_OUT,INPUT);

   digitalWrite(CS_M_POW,LOW);
   digitalWrite(CS_R_POW,LOW);

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
   
   pinMode(ENCODE_L_A,INPUT);
   pinMode(ENCODE_L_B,INPUT);
   pinMode(ENCODE_R_A,INPUT);
   pinMode(ENCODE_R_B,INPUT);

   //led
   pinMode(RED_LED,OUTPUT);
   pinMode(GREEN_LED,OUTPUT);
   pinMode(BLUE_LED,OUTPUT);
   pinMode(WHITE_L_LED,OUTPUT);
   pinMode(WHITE_R_LED,OUTPUT);

   //Buzzer
   pinMode(BUZZER,OUTPUT);
   
   //ultrasound
   pinMode(US_L_TRIG,OUTPUT);
   pinMode(US_L_ECO,INPUT);
   pinMode(US_R_TRIG,OUTPUT);
   pinMode(US_R_ECO,INPUT);

   // SERVO motors
   pinMode(ARM_L_SERVO,OUTPUT);
   pinMode(ARM_R_SERVO,OUTPUT);
   pinMode(RED_SERVO,OUTPUT);
   pinMode(GREEN_SERVO,OUTPUT);
   pinMode(BLUE_SERVO,OUTPUT);

   setupServos();
   setupRadio();
   Serial.begin(9600);
   buzzer(1);
   delay(5000);
   
}

void loop(){ 

 dropSR();
 delay(3000);
 pickSR();
 delay(1000);
 //sendSR(1);
}
