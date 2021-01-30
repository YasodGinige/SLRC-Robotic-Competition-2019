#define SENDPULSE_US_L \
    digitalWrite(US_L_TRIG, LOW);delayMicroseconds(5);digitalWrite(US_L_TRIG, HIGH);delayMicroseconds(5);digitalWrite(US_L_TRIG, LOW);
#define SENDPULSE_US_R \
    digitalWrite(US_R_TRIG, LOW);delayMicroseconds(5);digitalWrite(US_R_TRIG, HIGH);delayMicroseconds(5);digitalWrite(US_R_TRIG, LOW);
#define BLINK_WHITELED_L \
    digitalWrite(WHITE_L_LED,HIGH);delay(3000);digitalWrite(WHITE_L_LED,LOW);
#define BLINK_WHITELED_R \
    digitalWrite(WHITE_R_LED,HIGH);delay(3000);digitalWrite(WHITE_R_LED,LOW);
#define PASS_CROSSLINE \
    moveDistance(3.5,3.5);stopRobot();delay(1000);

float us_duration, us_distance;
int minPillarDistance= 10;

bool pillars[8][2];
int curPillar=0;
int pillarState=0;

bool isPillarL(){ // check if there is a pillar to left
  SENDPULSE_US_L; 
  us_duration = pulseIn(US_L_ECO, HIGH);
  us_distance = us_duration/58.2;
  
  Serial.println(us_distance);
  if(us_distance<minPillarDistance){
    BLINK_WHITELED_L;  
    return true;
  }
  return false;
}

bool isPillarR(){
  SENDPULSE_US_R;
  us_duration = pulseIn(US_R_ECO, HIGH);
  us_distance = us_duration/58.2;

  Serial.println(us_distance);
  if(us_distance<minPillarDistance){
    BLINK_WHITELED_R;  
    return true;
  }
  return false;
}

void pillarIdentificationLoop(){
  
  switch(pillarState){
    
     case 0: // line follow
          if(isJunction()) pillarState++;
          else lineFollow();
          break; 

     case 1:  // pillar indication 
          PASS_CROSSLINE; // leds lit in isPillar()
          pillars[curPillar][0] = isPillarL();  
          pillars[curPillar][1] = isPillarR();
          pillarState--;
          break;
   }
}
