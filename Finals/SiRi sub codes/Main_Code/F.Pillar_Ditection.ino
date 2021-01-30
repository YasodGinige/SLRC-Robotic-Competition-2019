#define SENDPULSE_US_L \
    digitalWrite(US_L_TRIG, LOW);delayMicroseconds(5);digitalWrite(US_L_TRIG, HIGH);delayMicroseconds(5);digitalWrite(US_L_TRIG, LOW);
#define SENDPULSE_US_R \
    digitalWrite(US_R_TRIG, LOW);delayMicroseconds(5);digitalWrite(US_R_TRIG, HIGH);delayMicroseconds(5);digitalWrite(US_R_TRIG, LOW);
#define PASS_CROSSLINE \
    moveDistance(3,3);stopRobot();delay(700);

float us_duration, us_distance;
const int minPillarDistance =14;
int curPillar=0;
int pillarState=0;

bool isPillarL(){ // check if there is a pillar to left
  SENDPULSE_US_L; 
  us_duration = pulseIn(US_L_ECO, HIGH);
  us_distance = us_duration/58.2;
  
  //Serial.println(us_distance);
  if(us_distance<minPillarDistance)
    return true;
  return false;
}

bool isPillarR(){
  SENDPULSE_US_R;
  us_duration = pulseIn(US_R_ECO, HIGH);
  us_distance = us_duration/58.2;
    
  if(us_distance<minPillarDistance)
    return true;
  
  
  return false;
}
void printPillarData(){
  for(int i=0;i<4;i++){
    Serial.print(pillars[i][0]);Serial.println(pillars[i][1]);
  }  
  
}
void pillarIdentificationLoop(){

  if(curPillar>3){ 
    lineFollowDistance(12);
    taskCounter++; 
    printPillarData();
    return;
    
  };
  Serial.println(curPillar);
  switch(pillarState){
    
     case 0: // line follow
          if(isJunction()) pillarState++;
          else lineFollow();
          break; 

     case 1:  // pillar indication 
          buzzer(1);
          PASS_CROSSLINE; // leds lit in isPillar()
          
          if(isPillarL()) pillars[curPillar][0] = true;  
          else pillars[curPillar][0] = false;  
          if(isPillarR()) pillars[curPillar][1] = true; 
          else pillars[curPillar][1] = false;  
          
          if(pillars[curPillar][0] && pillars[curPillar][1])  indicateLED(WHITE_L_LED,WHITE_R_LED); 
          else if(pillars[curPillar][0])   indicateLED(WHITE_L_LED);
          else if(pillars[curPillar][1])   indicateLED(WHITE_R_LED);
          
          pillarState--; curPillar++;
          lineFollowDistance(8);
          break;
   }
}
