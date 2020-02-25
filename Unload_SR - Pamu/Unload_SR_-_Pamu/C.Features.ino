Servo RServo,GServo,BServo,ArmLServo,ArmRServo;
int RGBServoRestAngles[3] ={94,83,98};
int RGBServoDropAngles[3] ={64,53,68};
int armRestAngles[2]={143,57}; // 0 left 1 right
//armDropAngles[2]={43,157};

const byte address[8]="#SiRi++";
RF24 radio(7,8);

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
  pickArm();
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

void setupRadio(){
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void sendSR(int dig){
  char charDig= dig+'0';
  Serial.println(dig);
  for(int i=0;i<20;i++)
    radio.write(&charDig,sizeof(charDig));
  
}

void dropArm(){
  
  for(int i=0;i<=100;i++){
    ArmLServo.write(armRestAngles[0]-i);
    ArmRServo.write(armRestAngles[1]+i);  
    delay(20);
  }
}

void pickArm(){
  for(int i=100;i>=0;i--){
    ArmLServo.write(armRestAngles[0]-i);
    ArmRServo.write(armRestAngles[1]+i);  
    delay(20);
  }
}
