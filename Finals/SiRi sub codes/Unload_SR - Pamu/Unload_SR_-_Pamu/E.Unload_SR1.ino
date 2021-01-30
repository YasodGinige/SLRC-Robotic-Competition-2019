int unload_sr_state=0;
int unload_sr_dir[6]={3,0,0,2,3};

bool isSquare(){
  readSensors();
  int lineSquare = r1+r2+r3+r4+l1+l2+l3+l4;
  if (lineSquare>=7){
    Serial.println("Square");
    return true;
  }
  else return false;
}

void dropSRsmoothly(){
  buzzer(1);
  dropArm();
  delay(1000);
  reverse(1000);
  buzzer(1);
  pickArm(); 
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

    reverse(300);
    
    dropSRsmoothly();

    turnToDir(3);

    unload_sr_state++;
  }
  
  if (unload_sr_state>1){

    stopRobot();
    taskCounter++;
  }
  lineFollow();
}
