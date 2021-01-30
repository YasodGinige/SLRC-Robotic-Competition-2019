void C_line_read(){
  turnToDir(3);
  lineFollowDistance(10);
  stopRobot();
  int Fcolour=detectColour_M();
  if(Fcolour==0) indicateLED(RED_LED); // first indicate leds
  if(Fcolour==1) indicateLED(GREEN_LED);
  if(Fcolour==2) indicateLED(BLUE_LED);

  if(Fcolour>0)sendSR(4+Fcolour);
  delay(5000);
  sendSR(7);
  while(!isJunction()) lineFollow();
  
  lineFollowDistance(20);

  stopRobot();
  int Scolour=detectColour_M();
  if(Scolour==0) indicateLED(RED_LED); // first indicate leds
  if(Scolour==1) indicateLED(GREEN_LED);
  if(Scolour==2) indicateLED(BLUE_LED);

  if(Scolour==1)sendSR(9);
  if(Scolour==2)sendSR(8);
  
  delay(5000);
  while(!isJunction()) lineFollow();

  moveDistance(18,18);

  buzzer(5);
  delay(10000);
}
