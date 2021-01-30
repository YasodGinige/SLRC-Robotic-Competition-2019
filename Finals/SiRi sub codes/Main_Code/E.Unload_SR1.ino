int unload_sr_state=0;
int unload_sr_dir[6]={3,0,0,2,3};

bool isSquare(){
  readSensors();
  int lineSquare = r1+r2+r3+r4+l1+l2+l3+l4;
  if (lineSquare>=7){
     return true;
  }
  else return false;
}

void dropSRsmoothly(){
  buzzer(1);
  dropArm();
  delay(1000);
  reverse(920);
  buzzer(1);
  pickArm(); 

  sendSR(3); // tell him that we have unloaded it
}

void unloadSRLoop(){
  Serial.println(dir);
  
  if (isJunction()){
    buzzer(1);
    moveDistance(15,15);
    turnToDir(0);
    unload_sr_state++;
  }
  
  if (unload_sr_state==1 && isSquare()){
    stopRobot();

    reverse(400);
    
    dropSRsmoothly();

    turnToDir(3);

    unload_sr_state++;
  }
  
  if (unload_sr_state>1){

    lineFollowDistance(10);
    taskCounter++;
  }
  lineFollow();
}
