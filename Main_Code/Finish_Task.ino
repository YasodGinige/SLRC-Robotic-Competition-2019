void finishTask(){
  
  turnToDir(1);  
  while(!isJunction()) lineFollow();
  
  turnToDir(1);
  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  
  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  turnToDir(2);
  
  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  

  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  turnToDir(3);

  while(!isJunction()) lineFollow();
  
  moveDistance(15,15);
  turnToDir(0);

  taskCounter++;

} 
  //buzzer(5);
  
  /*for(int i=0;i<100;i++)
    delay(10000);
}*/
