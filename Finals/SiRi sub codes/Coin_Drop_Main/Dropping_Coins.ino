int coinDropDirection(){
  
  
  if(curX>targetX[targetCount]) return 3;
  if(curX<targetX[targetCount]) return 1;
  if(curY<targetY[targetCount]) return 0;
  if(curY>targetY[targetCount]) return 2;
  
  
}

void coinDropLoop(){
  
  if(isJunction()) {
    buzzer(1);
    updateCoordinates();
    lineFollowDistance(15); // get center of rotation to junction
    turnToDir(coinDropDirection());
  }
  else lineFollow();

  
  if(targetX[targetCount]==curX && targetY[targetCount]==curY){
    stopRobot(); 

    turnToDir(colDropDir[targetCols[targetCount]]);
    dropCoin(targetCols[targetCount]);
    targetCount++;
  }
  
}
