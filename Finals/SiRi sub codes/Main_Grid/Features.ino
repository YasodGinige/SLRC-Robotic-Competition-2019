Servo RServo,GServo,BServo,ArmFServo,ArmRServp;
int RGBServoRestAngles[3] ={94,83,98};
int RGBServoDropAngles[3] ={64,53,68};

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

void setupServos(){
  RServo.attach(RED_SERVO);  
  GServo.attach(GREEN_SERVO);
  BServo.attach(BLUE_SERVO);

  RServo.write(RGBServoRestAngles[0]);
  GServo.write(RGBServoRestAngles[1]);
  BServo.write(RGBServoRestAngles[2]);
  
}
void dropCoin(int colour){ // R0 G1 B2
  
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
}
