#define ON_CS_R digitalWrite(CS_R_POW,HIGH);
#define OFF_CS_R digitalWrite(CS_R_POW,LOW);

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

#define SEL_CLEAR_R \
   digitalWrite(CS_R_S2,HIGH);digitalWrite(CS_R_S3,LOW)
/////////////////////////////TO BE CALLIBERATED FOR BETTER RESULTS/////////////////////////////////

int whiteColourLimit_R =1900;
int blackColourLimit_R = 6300;

//////////////////////////////////////////////////////////////////////////////////////////////////


unsigned long get_CS_R_reading() {
  unsigned long colourVal;
  noInterrupts();
  colourVal = pulseIn(CS_R_OUT,HIGH,20000); // 2000us=2ms  2Hz min.
  interrupts();
  return colourVal;
}


uint16_t getColourReading_R(void) {
   unsigned long val;

    SEL_RED_R;
    redFilterVal = val = get_CS_R_reading();
    
    SEL_GREEN_R;
    greenFilterVal = val = get_CS_R_reading();
    
    SEL_BLUE_R;
    blueFilterVal = val = get_CS_R_reading();

    //Serial.print("RED: "); Serial.print(redFilterVal);
    //Serial.print(" GREEN: "); Serial.print(greenFilterVal);
    //Serial.print(" BLUE: "); Serial.print(blueFilterVal);
    //Serial.print(" \n");
    
}
int detectColourOnce_R(){

 
  TWO_PER_R;
  getColourReading_R();
  int totalColourValue = redFilterVal+greenFilterVal+blueFilterVal;

  if(totalColourValue<whiteColourLimit_R)
    return  4; // white colour
  if(totalColourValue>blackColourLimit_R)
    return  5; // white colour
    
  if(redFilterVal < blueFilterVal && redFilterVal < greenFilterVal)
    return 0; // red
  if(greenFilterVal < blueFilterVal && greenFilterVal < redFilterVal)
    return 1; // green
  if(blueFilterVal < redFilterVal && blueFilterVal+230 < greenFilterVal)
    return 2; // blue
  
  return 1; // confusion means green

}

int detectColour_R() { // 0 red , 1 green , 2 blue , 4 white , 5 black 
   ON_CS_R;
   delay(300);
   digitalWrite(CS_R_POW,HIGH);
   int colourCount[6]={0,0,0,0,0,0};

   // CAN SHORTEN THE CODE while true if >5 return
   while(true){ //  we get average values to make sure accurate reading
      int thisCol =detectColourOnce_R();
      colourCount[thisCol]++;  
      if(colourCount[thisCol]>=5){
        OFF_CS_R;
        return thisCol;
      }
   }

   OFF_CS_R;
   return 5;
}
