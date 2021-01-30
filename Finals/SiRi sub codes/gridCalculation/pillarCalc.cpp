#include <iostream>

using namespace std;


bool pillars[4][2]={{1,1},{1,0},{0,1},{1,0}}; // values are true if a pillar is there;
int pillarValues[4][2]={{10,20},{20,40},{30,60},{40,80}};
int pillarTotal; // pillar value of all pillars
int greenIndex,redIndex,blueIndex;
string fiboValue;

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

  int digCount= fiboValue.size();
  greenIndex=fiboValue[digCount-3]-'0' ; // 3rd digit from right
  blueIndex=fiboValue[2];// 3rd digit from left

}
void doCalculations(){

//  stopRobot();
  calculatePillarValue();
//  fiboValue =  fibo(pillarN);;
  setRGBIndex();

}
int main(){

    calculatePillarValue();
    cout<<pillarN<<endl;

}
