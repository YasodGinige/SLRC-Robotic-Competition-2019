//
// Detect colors using TCS230.
//

// Arduino uno pins for control of TCS230
#define TCS320_OE 7
#define TCS320_S0 10
#define TCS320_S1 11
#define TCS320_S2 2
#define TCS320_S3 3
#define TCS320_OUT 4

/////////////////////////////TO BE CALLIBERATED FOR BETTER RESULTS/////////////////////////////////
int whiteColourLimit =1900;
int blackColourLimit = 5400;
//////////////////////////////////////////////////////////////////////////////////////////////////

#define SEL_RED  \
   digitalWrite(TCS320_S2,LOW);digitalWrite(TCS320_S3,LOW)
#define SEL_GREEN \
   digitalWrite(TCS320_S2,HIGH);digitalWrite(TCS320_S3,HIGH)
#define SEL_BLUE \
   digitalWrite(TCS320_S2,LOW);digitalWrite(TCS320_S3,HIGH)
#define SEL_CLEAR \
   digitalWrite(TCS320_S2,HIGH);digitalWrite(TCS320_S3,LOW)

#define TWO_PER \  
   digitalWrite(TCS320_S0,LOW);digitalWrite(TCS320_S1,HIGH);// reduce the frequency to 2%


void colourSensorSetup() {

   pinMode(TCS320_OE,OUTPUT);
   pinMode(TCS320_S0,OUTPUT);
   pinMode(TCS320_S1,OUTPUT);
   pinMode(TCS320_S2,OUTPUT);
   pinMode(TCS320_S3,OUTPUT);
   pinMode(TCS320_OUT,INPUT);

   TWO_PER;

   digitalWrite(TCS320_OE,LOW); // On always.

   Serial.begin(9600);
}

unsigned long get_TCS230_reading() {
  unsigned long val;
  noInterrupts();
  val = pulseIn(TCS320_OUT,HIGH,20000); // 2000us=2ms  2Hz min.
  interrupts();
  return val;
}

static int clrFilterVal,redFilterVal,greenFilterVal,blueFilterVal;

uint16_t getColourReading(void) {
   unsigned long val;

    SEL_RED;
    redFilterVal = val = get_TCS230_reading();
    Serial.print("RED: "); Serial.print(val);

    SEL_GREEN;
    greenFilterVal = val = get_TCS230_reading();
    Serial.print(" GREEN: "); Serial.print(val);

    SEL_BLUE;
    blueFilterVal = val = get_TCS230_reading();
    Serial.print(" BLUE: "); Serial.print(val);

    Serial.print(" \n");
    
}
int detectColourOnce(){

  getColourReading();
  int totalColourValue = redFilterVal+greenFilterVal+blueFilterVal;

  if(totalColourValue<whiteColourLimit)
    return  4; // white colour
  if(totalColourValue>blackColourLimit)
    return  5; // white colour
    
  if(redFilterVal < blueFilterVal && redFilterVal < greenFilterVal)
    return 0; // red
  if(greenFilterVal < blueFilterVal && greenFilterVal < redFilterVal)
    return 1; // green
  if(blueFilterVal < redFilterVal && blueFilterVal+230 < greenFilterVal)
    return 2; // blue
  
  return 1; // confusion means green
}

int detectColour() { // 0 red , 1 green , 2 blue , 4 white , 5 black 

   int colourCount[6]={0,0,0,0,0,0};
   
   while(colourCount[0]<5 && colourCount[1]<5 && colourCount[2]<5&& colourCount[4]<5 && colourCount[5]<5){ //  we get average values to make sure accurate reading
      int thisCol =detectColourOnce();
      colourCount[thisCol]++;  
   }

    // we choose a colour only after it is detected 5 times
   if(colourCount[0]>=5) return 0;
   if(colourCount[1]>=5) return 1;
   if(colourCount[2]>=5) return 2;
   if(colourCount[4]>=5) return 4;
   if(colourCount[5]>=5) return 5;
   
   return 5;
}
void loop(){
   Serial.println(detectColour());
   delay(2000);
   
}
