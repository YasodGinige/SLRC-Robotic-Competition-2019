int redCount,greenCount,blueCount;

int gridTraverseDir[9][9]={{0,0,0,0,0,0,0,0,0},
                           {0,3,3,3,3,3,3,3,3},
                           {0,0,0,0,0,0,0,0,0},
                           {1,1,1,1,1,1,1,1,0},
                           {0,0,0,0,0,0,0,0,0},
                           {0,3,3,3,3,3,3,3,3},
                           {0,0,0,0,0,0,0,0,0},
                           {1,1,1,1,1,1,1,1,3}};
                           
void printPositionData(){
    Serial.print(curX);
    Serial.print(" ");
    Serial.print(curY);
    Serial.print(" ");
    Serial.println(dir);
  
  
}
void saveColourSquares(){
    stopRobot();
    
    int thisColour = 4;
    if(dir==3||dir==1) thisColour=detectColour_M(); // R G B values are global variables R0 G1 B2
    
    if(thisColour==0) indicateLED(RED_LED); // first indicate leds
    if(thisColour==1) indicateLED(GREEN_LED);
    if(thisColour==2) indicateLED(BLUE_LED);

    moveDistance(4.1,4.1); // get the colour center to the middle

    if(curY==0 || thisColour>3) return;
    
    int rightColour = detectColour_R();
    Serial.print("right col sensor ");Serial.println(rightColour);

    int colX=curX;
    int colY=curY;
    if( (dir==3 && rightColour>3) || (dir==1 && rightColour<3) )  colY--; // right side white
    if( dir==1)  colX--; // going east side right white
    
    Serial.print(colX);Serial.print("  colX  colY  ");Serial.println(colY);
      switch(thisColour){
        
        case 0:
             redSquares[redCount++]={colX,colY};
             break;
        case 1:
             greenSquares[greenCount++]={colX,colY};  
             break;
        case 2:
             blueSquares[blueCount++]={colX,colY};  
             break;
        
       }  
}

void printColSquares(){
  
  Serial.println("RED");

  for(int i=0;i<3;i++){
    Serial.print(redSquares[i].x);Serial.println(redSquares[i].y);
  }

  Serial.println("GREEN");

  for(int i=0;i<3;i++){
    Serial.print(greenSquares[i].x);Serial.println(greenSquares[i].y);
  }

  Serial.println("BLUE");

  for(int i=0;i<3;i++){
    Serial.print(blueSquares[i].x);Serial.println(blueSquares[i].y);
  }
  buzzer(4);
}

void gridTraverseLoop(){
  if (curX==8 and curY==7){
    stopRobot();
    printColSquares();
    calculateCoinDrop();
    taskCounter++;
  }
  else if(isJunction()){
    stopRobot();
    updateCoordinates();
    buzzer(1);
    
    saveColourSquares();
    
    if(dir!=gridTraverseDir[curY][curX]) moveDistance(8.5,8.5);
    else lineFollowDistance(15);
    
    turnToDir(gridTraverseDir[curY][curX]); //color detection should come here

  }
  else lineFollow();

 // if(curY>6) printColSquares();//taskCounter++;
} 
