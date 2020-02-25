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

Encoder leftEncoder(ENCODE_L_A,ENCODE_L_B);
Encoder rightEncoder(ENCODE_R_A,ENCODE_R_B);


int l5,l4,l3,l2,l1,r1,r2,r3,r4,r5;

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

bool isJunction(){
  readSensors();
  if((r5 && (r1+r2+r3>=1))|| (l5 && (l1+l2+l3>=1))) return true; // white 1 black 0 // add extra verifications here too
  Serial.println("no junction");
  return false;
}

bool get_digital(int port,int thresshold){
  int value = analogRead(port);
  return value<=thresshold? 1:0;
  //return analogRead(port);
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

float getRotatedDistance(int lrwheel){ //0 left 1 right
  
  long thisPosition;
  if(lrwheel==0)  thisPosition = leftEncoder.read();
  else thisPosition = -1*rightEncoder.read();
  float distance = (thisPosition/2249.0)*2*3.14159*wheel_radius;

  return distance;
}

void moveDistance(float ldistance,float rdistance){

  float distance = (abs(ldistance)+abs(rdistance))/2;
  int signL = ldistance>=0? 1:-1;
  int signR = rdistance>=0? 1:-1;
  
  float startLDistance=getRotatedDistance(0);
  float startRDistance=getRotatedDistance(1);

  float rotatedLDistance=0,rotatedRDistance=0;

  while(rotatedLDistance<distance && rotatedRDistance<distance){
    if(rotatedLDistance>rotatedRDistance) moveRobot(signL*SPEED
    ,signR*(SPEED+5));
    else if(rotatedLDistance<rotatedRDistance) moveRobot(signL*(SPEED+5),signR*SPEED);
    
    else moveRobot(signL*SPEED,signR*SPEED);

    rotatedLDistance = (getRotatedDistance(0)-startLDistance)*signL;
    rotatedRDistance = (getRotatedDistance(1)-startLDistance)*signR;
    //Serial.print(rotatedLDistance);
    //Serial.print('\t');
    //Serial.println(rotatedRDistance);
    
  }

  stopRobot();
}
///////////////////ENCODED MOTOR ENDS HERE ////////////////////////

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
void lineFollowDistance(int distance){
    float startDistance=(getRotatedDistance(0)+getRotatedDistance(1))/2;
    float rotatedDistance=0;

    while(abs(rotatedDistance)<abs(distance)){
      readSensors();
      line = r1+r2+r3+r4-l1-l2-l3-l4;
      if(line>0){
        if(distance>=0) moveRobot(SPEED+10,0);
        else moveRobot(0,-SPEED-10);
      }
      else if(line<0){
        if(distance>=0) moveRobot(0,SPEED+10);
        else moveRobot(-SPEED-10,0);
      }
      else{
       if(distance>=0)  moveRobot(SPEED,SPEED);
       else moveRobot(-SPEED,-SPEED);
      }  
      rotatedDistance = (getRotatedDistance(0)+getRotatedDistance(1))/2 - startDistance;
    }
}
void left90(){ 

 // Serial.println("left");

  moveRobot(-SPEED-5,SPEED+5);
  delay(900);
  readSensors();
  while(l1+r1+r2+l2<3){
    delay(50); readSensors();
  }
  stopRobot();
  delay(1500);
}

void right90(){ 

 // Serial.println("right");
 
  moveRobot(SPEED+5,-SPEED-5);
  delay(900);
  readSensors();

  while(r2+l1+l2+r1<3){
    delay(50);readSensors();
  }
  stopRobot();
  delay(1500);
}

void turn180(){ 

  moveRobot(SPEED+5,-SPEED-5);
  delay(1800);
  readSensors();

  moveRobot(SPEED,-SPEED);
  while(r1+l1+l2+l3<3){
    readSensors();
    delay(50);
  }
  stopRobot();
  delay(1500);
}

void reverse(int timeR){
  moveRobot(-SPEED,-SPEED);
  delay(timeR);  
  stopRobot();
}
