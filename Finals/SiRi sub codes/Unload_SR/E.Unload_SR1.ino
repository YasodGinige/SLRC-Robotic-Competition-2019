int unload_sr_state=0;
int unload_sr_dir[6]={3,0,0,2,3};

void dropSRsmoothly(){
  dropSR();
  moveDistance(-6,-6.5);
  pickSR(); 
}

void unloadSRLoop(){
  if (isJunction()){
    moveRobot(15.5,15.5);
    right90();
    
  }
/*
  if(isJunction()) unload_sr_state++;
  if(dir!=unload_sr_dir[unload_sr_state]) turnToDir[unload_sr_state];

  if(unload_sr_state==2){ 
    dropSRsmoothly();
    unload_sr_state++;
  }
  lineFollow();
  Serial.println(unload_sr_state);*/
}
