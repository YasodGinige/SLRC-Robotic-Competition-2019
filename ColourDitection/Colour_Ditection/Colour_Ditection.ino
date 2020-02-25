#include <Encoder.h>
#include <Wstring.h>
#include <Servo.h>

//LEFT RIGHT IR SENSORS
#define l5_PORT A9
#define r5_PORT A8

//REYKHA SENSOR
#define l4_PORT A0
#define l3_PORT A1
#define l2_PORT A2
#define l1_PORT A3
#define r1_PORT A4
#define r2_PORT A5
#define r3_PORT A6
#define r4_PORT A7

//COLOUR SENSOR
#define CS_M_POW 48
#define CS_M_OE 36 // middle colour sensor
#define CS_M_S0 40
#define CS_M_S1 38
#define CS_M_S2 42
#define CS_M_S3 44
#define CS_M_OUT 46

#define CS_R_OE 7 // right colour sensor
#define CS_R_S0 10
#define CS_R_S1 11
#define CS_R_S2 2
#define CS_R_S3 3
#define CS_R_OUT 4

//ULTRASONIC SENSOR
#define US_L_TRIG // left 
#define US_L_ECO

#define US_R_TRIG//right 
#define US_R_ECO

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
#define ARM_F_SERVO // forward
#define ARM_R_SERVO //rear

#define RED_SERVO 
#define GREEN_SERVO 
#define BLUE_SERVO
Servo redServo,blueServo,greenServo;

// RADIO SIGNAL MODULE
#define RADIO_CSN 8
#define RADIO_CE 7
#define RADIO_SCK 52
#define RADIO_MOST 51
#define RADIO_MISO 50

//LED
#define RED_LED
#define GREEN_LED
#define BLUE_LED
#define WHITE_L_LED
#define WHITE_R_LED

//PUSH BUTTONS
#define CALLIBERATE_BUTTON
#define ROUND_BUTTON
#define DELAY_BUTTON

//BUZZER
#define BUZZER 

const int n=8; // grid size
int taskCounter=3;

void setup() {
  //  colour sensor
   pinMode(CS_M_POW,OUTPUT);
   pinMode(CS_M_OE,OUTPUT);
   pinMode(CS_M_S0,OUTPUT);
   pinMode(CS_M_S1,OUTPUT);
   pinMode(CS_M_S2,OUTPUT);
   pinMode(CS_M_S3,OUTPUT);
   pinMode(CS_M_OUT,INPUT);

   pinMode(CS_R_OE,OUTPUT);
   pinMode(CS_R_S0,OUTPUT);
   pinMode(CS_R_S1,OUTPUT);
   pinMode(CS_R_S2,OUTPUT);
   pinMode(CS_R_S3,OUTPUT);
   pinMode(CS_R_OUT,INPUT);

   digitalWrite(CS_M_POW,HIGH);
     Serial.begin(9600);
   
}

void loop() {
  Serial.println(detectColour());
  delay(1000);
  
}
