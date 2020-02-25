void PickUp(){
  sendSR(4);
  dropArm();
  lineFollowDistance(14);


  stopRobot();
  delay(3000);
  pickArm();
  delay(3000);

  turnToDir(2);
  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  turnToDir(1);

  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  turnToDir(0);
  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  

  while(!isJunction()) lineFollow();

  moveDistance(15,15);
  turnToDir(3);

  while(!isJunction()) lineFollow();

  moveDistance(15,15);
  turnToDir(2);

  taskCounter++;
}
