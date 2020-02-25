struct cord{
  int x;
  int y;  
};
int n=8;
cord redSquares[3];
cord greenSquares[3]={{1,1},{6,1},{4,7}};;
cord blueSquares[3];
int gridNums[8][8];
int gridColours[8][8]; // 0 white 1 red 2 green 3 blue

void setup() {
  

}

void fillGridNums(){
  
 
 int Y=0;
 int val=1;
 int stp =1; // step of value increase
  
 while(Y<n){
  for(int X=n-1;X>=0;X--){
    gridNums[Y][X]=val;
    if(gridColours[Y][X]==1) //red square
      stp=2;
    else if(gridColours[Y][X]==2) //red square
      stp=3;
    else if(gridColours[Y][X]==3) //red square
      stp=4;
    val+=stp;
  }  
  Y++;
  for(int X=0;X<n;X++){
    gridNums[Y][X]=val;
    if(gridColours[Y][X]==1) //red square
      stp=2;
    else if(gridColours[Y][X]==2) //red square
      stp=3;
    else if(gridColours[Y][X]==3) //red square
      stp=4;
    val+=stp;
  }
  Y++;
 }
  
  
}

void loop() {
  

}
