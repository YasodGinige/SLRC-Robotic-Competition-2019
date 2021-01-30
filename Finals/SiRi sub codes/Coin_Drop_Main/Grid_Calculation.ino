
//*************************************^^^private variables^^^************************************************************

int gridNums[8][8];
int gridColours[8][8]; // 0 white 1 red 2 green 3 blue
long redPowerValue,greenPowerValue,bluePowerValue; // red[0]^3+ red[1]^2 +red[0]

int greenOrder,blueOrder,redOrder;// 0 1 2 when to put red/green/blue coins(which one first..)
long powerValues[3];

void fillGridNums(){


 int Y=0;
 int val=1;
 int stp =1; // step of value increase

 while(Y<n){
  for(int X=n-1;X>=0;X--){
    gridNums[Y][X]=val;
    if(gridColours[Y][X]==1) //red square
      stp=2;
    else if(gridColours[Y][X]==2) //green square
      stp=3;
    else if(gridColours[Y][X]==3) //blue square
      stp=4;
    val+=stp;
  }
  Y++;
  for(int X=0;X<n;X++){
    gridNums[Y][X]=val;
    if(gridColours[Y][X]==1) //red square
      stp=2;
    else if(gridColours[Y][X]==2) //green square
      stp=3;
    else if(gridColours[Y][X]==3) //blue square
      stp=4;
    val+=stp;
  }
  Y++;
 }

}

void setColourSquares(){

    for (int i=0;i<3;i++){
        int X= redSquares[i].x;
        int Y= redSquares[i].y;
        gridColours[Y][X]=1;
    }


    for (int i=0;i<3;i++){
        int X= greenSquares[i].x;
        int Y= greenSquares[i].y;
        gridColours[Y][X]=2;
    }

    for (int i=0;i<3;i++){
        int X= blueSquares[i].x;
        int Y= blueSquares[i].y;
        gridColours[Y][X]=3;
    }
}
long power(int num,int poww){
    long ret=1;
    for(int i=0;i<poww;i++)  ret*=num;
    return ret;
}
int calculatePowerValues(){

    for (int i=0;i<3;i++){
     redPowerValue+= power(gridNums[redSquares[i].y][redSquares[i].x],(3-i));
    // Serial.println(gridNums[redSquares[i].y][redSquares[i].x]);
    }

    for (int i=0;i<3;i++)
     greenPowerValue+= power(gridNums[greenSquares[i].y][greenSquares[i].x],(3-i));

    for (int i=0;i<3;i++)
     bluePowerValue+= power(gridNums[blueSquares[i].y][blueSquares[i].x],(3-i));

}
int getOrder(long val){

    for(int i=0;i<3;i++)
        if(val==powerValues[i]) return i;

}

void bubbleSort(){
  for(int i=0;i<2;i++) for(int j=0; j<2;j++)
      if(powerValues[j]>powerValues[j+1]){ 
        long tmp=powerValues[j];
        powerValues[j]=powerValues[j+1];
        powerValues[j+1]=tmp;
      } 
  
}

void setCoinDropOrder(){


    powerValues[0]= redPowerValue;
    powerValues[1]= greenPowerValue;
    powerValues[2]= bluePowerValue;

    bubbleSort();
    for(int i=0;i<3;i++)
      Serial.println(powerValues[i]);

    // set red position
    redOrder = getOrder(redPowerValue);
    targetX[redOrder] = redSquares[redIndex].x;
    Serial.println(redOrder);
    targetY[redOrder] = redSquares[redIndex].y;
    targetCols[redOrder] = 0;

    //green
    greenOrder = getOrder(greenPowerValue);
    targetX[greenOrder] = greenSquares[greenIndex].x;
    targetY[greenOrder] = greenSquares[greenIndex].y;
    targetCols[greenOrder] = 1;

    //blue
    blueOrder = getOrder(bluePowerValue);
    targetX[blueOrder] = blueSquares[blueIndex].x;
    targetY[blueOrder] = blueSquares[blueIndex].y;
    targetCols[blueOrder] = 2;
}
void printGrid(){
  
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){ Serial.print(gridNums[7-i][j]); Serial.print('\t');}  
    Serial.println();
  }  
  
}
void printCoinDropSquares(){
  
  for(int i=0;i<3;i++){
    Serial.print(targetX[i]);Serial.print(targetY[i]);Serial.println(targetCols[i])  ;
  }
}

int calculateCoinDrop(){

    stopRobot();

    doPillarCalculations(); // other tab Red Green and Blue indices will be set Ex: coin drop to second blue - blueIndex =1
    
    setColourSquares();

    fillGridNums();

    printGrid();

    calculatePowerValues();

    setCoinDropOrder();

    taskCounter++;
    
    printCoinDropSquares();
    
}
