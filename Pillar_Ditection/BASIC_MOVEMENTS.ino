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

const float wheel_radius=2.14;
const float wheel_distance=21.6;
int rekhaThress=70,IRThress=70; // thresshold values
int line;

int l5,l4,l3,l2,l1,r1,r2,r3,r4,r5;

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
bool isJunction(){
  readSensors();
  if((r5 && (r1+r2+r3>=1))|| (l5 && (l1+l2+l3>=1))) return true; // white 1 black 0 // add extra verifications here too
  //Serial.println("no junction");
  return false;
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

//////////////////////ENCODED MOTOR USED HERE/////////////////////
/*float ENL_Start_ditance,ENR_Start_distance; // to reset
float ENL_distance,ENR_distance; // distance traveled after reset,should call EN_UPDATE

#define EN_RESET \ // ENCODED MOTOR READING
    ENL_Start_ditance=getRotatedDistance(0);ENR_Start_distance=getRotatedDistance(1);
#define EN_UPDATE \
    EN_L_distance=getRotatedDistance(0)-ENL_Start_distance;EN_R_distance=getRotatedDistance(1)-ENR_Start_distance;
*/

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

    rotatedLDistance = abs(getRotatedDistance(0)-startLDistance);
    rotatedRDistance = abs(getRotatedDistance(1)-startLDistance);
 //   Serial.print(rotatedLDistance);
   // Serial.print('\t');
   // Serial.println(rotatedRDistance);
    
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
       else moveRobot(-SPEED,SPEED);
      }  
      rotatedDistance = (getRotatedDistance(0)+getRotatedDistance(1))/2 - startDistance;
    }
}

void left90(){ 

  float quarter_circle = 3.14159*wheel_distance/4;
  moveDistance(-quarter_circle+2,quarter_circle-2);
 // delay(1000);
  readSensors();

  moveRobot(-SPEED,SPEED);
  while(l1+r1+r2+r3<3){
    delay(50); readSensors();
  }
  stopRobot();
  delay(2000);
}

void right90(){ 

  float quarter_circle = 3.14159*wheel_distance/4;
  moveDistance(quarter_circle-2,-quarter_circle+2);
  //delay(1000);
  readSensors();

  moveRobot(SPEED,-SPEED);
  while(l1+l2+l3+r1<3){
    delay(50);readSensors();
  }
  stopRobot();
  delay(2000);
}

void turn180(){ 

  float half_circle = 3.14159*wheel_distance/2;
  moveDistance(half_circle-2,-half_circle+2);
  delay(1000);
  readSensors();

  moveRobot(SPEED,-SPEED);
  while(r1+l1+l2+l3<3){
    readSensors();
    delay(50);
  }
  stopRobot();
  delay(2000);
}
