void Area2_Drop(){
  while(!isSquare()) lineFollow();

  reverse(400);
    
  dropSRsmoothly();

  sendSR(3);
  turnToDir(1);
  while(!isJunction()) lineFollow();

  moveDistance(15,15);
  turnToDir(2);
  
  while(!isJunction()) lineFollow();

  moveDistance(15,15);
  turnToDir(3);

  taskCounter++;

  

}
