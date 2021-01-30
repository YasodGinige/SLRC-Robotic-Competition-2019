#define SEL_RED_M  \
   digitalWrite(CS_M_S2,LOW);digitalWrite(CS_M_S3,LOW)
#define SEL_GREEN_M \
   digitalWrite(CS_M_S2,HIGH);digitalWrite(CS_M_S3,HIGH)
#define SEL_BLUE_M \
   digitalWrite(CS_M_S2,LOW);digitalWrite(CS_M_S3,HIGH)
#define SEL_CLEAR_M \
   digitalWrite(CS_M_S2,HIGH);digitalWrite(CS_M_S3,LOW)
#define TWO_PER_M \  
   digitalWrite(CS_M_S0,LOW);digitalWrite(CS_M_S1,HIGH);// reduce the frequency to 2%

#define SEL_RED_R  \
   digitalWrite(CS_R_S2,LOW);digitalWrite(CS_R_S3,LOW)
#define SEL_GREEN_R \
   digitalWrite(CS_R_S2,HIGH);digitalWrite(CS_R_S3,HIGH)
#define SEL_BLUE_R \
   digitalWrite(CS_R_S2,LOW);digitalWrite(CS_R_S3,HIGH)
#define SEL_CLEAR_R \
   digitalWrite(CS_R_S2,HIGH);digitalWrite(CS_R_S3,LOW)
#define TWO_PER_R \  
   digitalWrite(CS_R_S0,LOW);digitalWrite(CS_R_S1,HIGH);// reduce the frequency to 2%

/////////////////////////////TO BE CALLIBERATED FOR BETTER RESULTS/////////////////////////////////

int whiteColourLimit_M =1900;
int blackColourLimit_M = 6400;

int colourLimit_R =1900;
//////////////////////////////////////////////////////////////////////////////////////////////////

//int clrFilterVal,redFilterVal,greenFilterVal,blueFilterVal;

unsigned long get_CS_M_reading() {
  unsigned long colourVal;
  noInterrupts();
  colourVal = pulseIn(CS_M_OUT,HIGH,20000); // 2000us=2ms  2Hz min.
  interrupts();
  return colourVal;
}

static int clrFilterVal,redFilterVal,greenFilterVal,blueFilterVal;

uint16_t getColourReading(void) {
   unsigned long val;

    SEL_RED_M;
    redFilterVal = val = get_CS_M_reading();
    
    Serial.print("RED: "); Serial.print(val);
    
    SEL_GREEN_M;
    greenFilterVal = val = get_CS_M_reading();
    Serial.print(" GREEN: "); Serial.print(val);
    
    SEL_BLUE_M;
    blueFilterVal = val = get_CS_M_reading();

  
    Serial.print(" BLUE: "); Serial.print(val);
    Serial.print(" \n");
    
}
int detectColourOnce(){

  TWO_PER_M;
  getColourReading();
  int totalColourValue = redFilterVal+greenFilterVal+blueFilterVal;

  if(totalColourValue<whiteColourLimit_M)
    return  4; // white colour
  if(totalColourValue>blackColourLimit_M)
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

   // CAN SHORTEN THE CODE while true if >5 return
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
