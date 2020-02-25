int dir=3,
newDir=3;int curX=n+1,curY=0;

const int minPillarDistance =12;

//int pillars[8][2]={{0,1},{1,1},{1,0},{1,0}};
int pillars[8][2]={{1,1},{0,0},{1,1},{1,1}};


struct cord{  //grid traverse
  int x;
  int y;
};

cord redSquares[3]={{0,1},{6,2},{4,6}};
cord greenSquares[3]={{5,0},{3,4},{0,7}};
cord blueSquares[3]={{2,0},{0,3},{7,6}};


int pillarValues[4][2]={{10,20},{20,40},{30,60},{40,80}}; // pillar calculation
int pillarTotal; // pillar value of all pillars
int redIndex,blueIndex=1,greenIndex; // which square among 3 red/.. sqrs should be selected
String fibonacciValue;

int targetX[6] ={1,5,0,8,0,0}, targetY[9]={1,5,3,8,0,0};  // VALUES ARE SET IN GRID CALCULATIONS
int targetCols[3]={1,0,2}; // red green blue
int targetCount=0;

int colDropDir[5]={1,1,0,0};
