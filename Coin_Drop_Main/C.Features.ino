Servo RServo,GServo,BServo,ArmLServo,ArmRServo;
int RGBServoRestAngles[3] ={94,83,98};
int RGBServoDropAngles[3] ={64,53,68};
int armRestAngles[2]={72,139}; // 0 left 1 right
int armDropAngles[2]={160,51};

//Buzzer
void buzzer(int buzCount){
  //Beep....
 for(int i=0;i<buzCount;i++){  
  digitalWrite(BUZZER,HIGH);
  delay(50);
  digitalWrite(BUZZER,LOW);
  delay(50);
 }
}


void indicateLED(int pinNum){
  digitalWrite(pinNum,HIGH);
  delay(1500);
  digitalWrite(pinNum,LOW);  
}

void indicateLED(int pinNum1,int pinNum2){
  digitalWrite(pinNum1,HIGH); digitalWrite(pinNum2,HIGH);
  delay(1500);
  digitalWrite(pinNum1,LOW); digitalWrite(pinNum2,LOW);  
}

void setupServos(){
  RServo.attach(RED_SERVO);  
  GServo.attach(GREEN_SERVO);
  BServo.attach(BLUE_SERVO);
  ArmLServo.attach(ARM_L_SERVO);
  ArmRServo.attach(ARM_R_SERVO);

  RServo.write(RGBServoRestAngles[0]); // coin drop
  GServo.write(RGBServoRestAngles[1]);
  BServo.write(RGBServoRestAngles[2]);

  ArmLServo.write(armRestAngles[0]); // SR drop
  ArmRServo.write(armRestAngles[1]);
}
void dropCoin(int colour){ // R0 G1 B2

  lineFollowDistance(1.5);
  
  stopRobot();
  switch(colour){
    case 0:
        RServo.write(RGBServoDropAngles[colour]);
        //sendSR!(colour);
        buzzer(1);
        delay(1000);
        RServo.write(RGBServoRestAngles[colour]);
        break;
    case 1:
        GServo.write(RGBServoDropAngles[colour]);
        //sendSR!(colour);
        buzzer(1);
        delay(1000);
        GServo.write(RGBServoRestAngles[colour]);
        break;
    case 2:
        BServo.write(RGBServoDropAngles[colour]);
        //sendSR!(colour);
        buzzer(1);
        delay(1000);
        BServo.write(RGBServoRestAngles[colour]);
        break;
  
  }
  delay(1000);
}

void dropSR(){
  
  for(int i=4;i<=88;i+=4){
    ArmLServo.write(armRestAngles[0]+i);
    ArmRServo.write(armRestAngles[1]-i);  
    delay(20);
  }
}

void pickSR(){
  for(int i=88;i>=0;i-=4){
    ArmLServo.write(armRestAngles[0]+i);
    ArmRServo.write(armRestAngles[1]-i);  
    delay(20);
  }
}
void sendSR(){
  int x=1;  
}
