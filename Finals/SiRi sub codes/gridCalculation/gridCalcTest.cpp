#include <string.h>
#include <iostream>

using namespace std;
struct cord{
  int x;
  int y;
};

////////////////////////////////////
bool pillars[4][2]={{1,0},{1,1},{0,1},{1,0}}; // values are true if a pillar is there;

cord redSquares[3]={{0,3},{2,4},{6,5}};
cord greenSquares[3]={{1,1},{6,1},{4,7}};
cord blueSquares[3]={{3,2},{4,4},{2,6}};


/////////////////INPUT HERE ^////////////////////


int pillarValues[4][2]={{10,20},{20,40},{30,60},{40,80}};
int pillarTotal; // pillar value of all pillars
int greenIndex,redIndex,blueIndex;
string fibonacciValue;

string add(string a, string b){

  int sizea = a.length();
  int sizeb = b.length();

  if(sizeb>sizea){ // swap them first one big one
    string c=b; b=a; a=c;
    int sizec=sizeb; sizeb=sizea; sizea=sizec;
  }

  int fromRight=0; // 1 or 0, integer getting added from the right , initially 0
  string newNum;

  for(int i=0;i<sizea;i++){ // gp through the size of longer string from right most digit to left
    int aDig=a[sizea-1-i]-'0';
    int bDig=sizeb-1-i>=0? b[sizeb-1-i]-'0':0;

    int thisDig=(aDig+bDig+fromRight);

    if(thisDig>=10) fromRight=1;
    else fromRight=0;

    char dig = (thisDig%10)+'0';
    newNum=dig+newNum;
  }
  if(fromRight==1)
    newNum='1'+newNum; // if there is a 1 at the beginning


  return newNum;

}

string fibonacci(int n){
  string a="0";
  string b="1";
  string c;

  for(int i=2;i<=n;i++){
    c=add(a,b);
    a=b;
    b=c;
  }
  return c;
}


void calculatePillarValue(){

  pillarTotal=0;

  for(int i=0;i<4;i++)
    for(int j=0;j<2;j++) if(pillars[i][j]) // if the boolean value is true add the pillar value
      pillarTotal+=pillarValues[i][j];

}
void setRGBIndex(){
  if(pillarTotal<=166) redIndex=0;
  else if(pillarTotal<=233) redIndex=1;
  else redIndex=2;

  int digCount= fibonacciValue.length();
  int rightThird=fibonacciValue[digCount-3]-'0' ; // 3rd digit from right green
  int leftThird=fibonacciValue[2]-'0';// 3rd digit from left  blue

  if(rightThird<=2) greenIndex=0;
  else if(rightThird<=6) greenIndex=1;
  else greenIndex=2;


  if(leftThird<=2) blueIndex=0;
  else if(leftThird<=6) blueIndex=1;
  else blueIndex=2;

}
void doPillarCalculations(){

//  stopRobot();
  calculatePillarValue();
  fibonacciValue =  fibonacci(pillarTotal);
  setRGBIndex();

}

/////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include<bits/stdc++.h>

using namespace std;

int n=8;

int targetX[3],targetY[3];int targetCols[3];
//int redIndex,blueIndex=1,greenIndex; // which square among 3 red/.. sqrs should be selected

//*************************************^^^common/public variables^^^************************************************************

int gridNums[8][8];
int gridColours[8][8]; // 0 white 1 red 2 green 3 blue
int redPowerValue,greenPowerValue,bluePowerValue; // red[0]^3+ red[1]^2 +red[0]

int greenOrder,blueOrder,redOrder;// 0 1 2 when to put red/green/blue coins(which one first..)
int powerValues[3];

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
void printGrid(){
    for(int i=n-1;i>=0;i--){

        for (int j=0;j<n;j++)
            cout<<gridNums[i][j]<<" ";

        cout<<endl;
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
int pow(int numX,int powY){
    int ret=1;
    for(int i=0;i<powY;i++)  ret*=numX;
    return ret;
}
int calculatePowerValues(){

    for (int i=0;i<3;i++)
     redPowerValue+= pow(gridNums[redSquares[i].y][redSquares[i].x],(3-i));

    for (int i=0;i<3;i++)
     greenPowerValue+= pow(gridNums[greenSquares[i].y][greenSquares[i].x],(3-i));

    for (int i=0;i<3;i++)
     bluePowerValue+= pow(gridNums[blueSquares[i].y][blueSquares[i].x],(3-i));

}
int getOrder(int val){

    for(int i=0;i<3;i++)
        if(val==powerValues[i]) return i;

}
void setCoinDropOrder(){


    powerValues[0]= redPowerValue;
    powerValues[1]= greenPowerValue;
    powerValues[2]= bluePowerValue;

    sort(powerValues,powerValues+3);

    // set red position
    redOrder = getOrder(redPowerValue);
    targetX[redOrder] = redSquares[redIndex].x;
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
void printCoinDropOrder(){

    for(int i=0;i<3;i++)
        cout<<powerValues[i]<<endl;

    cout<<"colour order r0 g1 b2"<<endl;
    for(int i=0;i<3;i++)
        cout<<targetCols[i]<<"col\t"<<targetX[i]<<"x \t y"<<targetY[i]<<endl;
}
void printDetails(){
    cout<<"Pillar Total is "<<pillarTotal<<endl;
    cout<<"Fibonacci Value "<<fibonacciValue<<endl<<endl;
    cout<<"Drop coins to following red square "<<endl;
    cout<<"Red "<<redIndex<<"  Green "<<greenIndex<< "  Blue "<<blueIndex<<endl<<endl;

    printGrid();
    printCoinDropOrder();
}
int main(){

    doPillarCalculations();
    setColourSquares();
    fillGridNums();
    calculatePowerValues();
    setCoinDropOrder();

    printDetails();
}

