void updateCoordinates(){ // coordinates initialised in setup
  if(dir==0) curY++;
  if(dir==1) curX++;
  if(dir==2) curY--;
  if(dir==3) curX--;  

  //Serial.print(curX);Serial.println(curY);
  
}



void turnToDir(int newDir){

    stopRobot();
    delay(600);

   // Serial.print(dir); Serial.print("  dir newdir  "); Serial.println(newDir);
    if(newDir==(dir+1)%4)
      right90(); // 90 degrees

    if(newDir==(dir+3)%4)
      left90(); // 90 degrees
      
    if(newDir==(dir+2)%4)
      turn180();
      
    dir= newDir;   
     
}



  
  
  
  
  
  
