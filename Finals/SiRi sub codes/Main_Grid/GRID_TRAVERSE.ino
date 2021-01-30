
///////////////////COLOUR DETECTED ---> FILL THESE ARRAYS///////////////////////////
struct cord{
  int x;
  int y;
};

cord redSquares[3]={{0,3},{2,4},{6,5}};  // used in grid calculations
cord greenSquares[3]={{1,1},{6,1},{4,7}};
cord blueSquares[3]={{3,2},{4,4},{2,6}};

int redCount,greenCount,blueCount; // r 0 g 1 b 2
///////////////////////////////////////////////////////////////////////////////////

void detectColours();

bool isJunction();

int gridTraverseDir[9][9]={{0,0,0,0,0,0,0,0,0},
                           {0,3,3,3,3,3,3,3,3},
                           {0,0,0,0,0,0,0,0,0},
                           {1,1,1,1,1,1,1,1,0},
                           {0,0,0,0,0,0,0,0,0},
                           {0,3,3,3,3,3,3,3,3},
                           {0,0,0,0,0,0,0,0,0},
                           {1,1,1,1,1,1,1,1,1}};

void setColourSquare(int detectedCol){

  switch(detectedCol){
    
    case 0:
      //redSquares
      break;  
    
    
  }
  
}

void gridTraverseLoop(){
  
  if(isJunction()){
    stopRobot();
    updateCoordinates();
    buzzer(1);

    Serial.print(curX);
    Serial.print(" ");
    Serial.print(curY);
    Serial.print(" ");
    Serial.println(dir);
    
    
   // if(thisColour<3 && (dir ==1 || dir ==3) && curY>0) // r g b colour detected only set colours when facing east west not first square(entering col)
     // setColourSquare(thisColour);
     
     moveDistance(4,4); // get center of rotation to junction
     if(dir!=gridTraverseDir[curY][curX]) moveDistance(9.5,9.5);
     else lineFollowDistance(15);
     turnToDir(gridTraverseDir[curY][curX]); //color detection should come here

     int thisColour = 4;
     if(dir==3||dir==1) thisColour=detectColour_M(); // R G B values are global variables R0 G1 B2
     if(thisColour==0) indicateLED(RED_LED);
     if(thisColour==1) indicateLED(GREEN_LED);
     if(thisColour==2) indicateLED(BLUE_LED);

  }
  else lineFollow();
    
} 
