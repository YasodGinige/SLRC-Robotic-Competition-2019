#include <Wstring.h>

String add(String a, String b){

  int sizea = a.length();
  int sizeb = b.length();

  if(sizeb>sizea){ // swap them first one big one
    String c=b; b=a; a=c;
    int sizec=sizeb; sizeb=sizea; sizea=sizec;
  }

  int fromRight=0; // 1 or 0, integer getting added from the right , initially 0
  String newNum;

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

String fibonacci(int n){
  String a="0";
  String b="1";
  String c;

  for(int i=2;i<=n;i++){
    c=add(a,b);
    a=b;
    b=c;
  }
  return c;
}
////////////////////////////////////////////////////
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
void printPillarData(){
  Serial.println(pillarTotal); 
  Serial.println(fibonacciValue);
   
  
}
void doPillarCalculations(){

  calculatePillarValue();
  
  fibonacciValue =  fibonacci(pillarTotal);
  
  setRGBIndex();

  printPillarData();
}
