#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

RF24 radio(7,8);
const byte address[8]="#SiRi++";

char character;
int state=0,dig;

Servo midServo; // 165 - 80 - 10
Servo leftServo; // 80(low) - 40(high)
Servo rightServo; // 110(low) - 150(high)

int ver = 0;
int hor = 80;

void setup() {
  midServo.attach(5);
  leftServo.attach(6);
  rightServo.attach(3);
  leftServo.write(90);
  rightServo.write(100);
  midServo.write(80);
  
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.begin(9600);
}

void liftArm(){
  for (ver;ver<40;ver++){
    leftServo.write(90-ver);
    rightServo.write(100+ver);
    delay(15);
  }
}

void downArm(){
  for (ver;ver>=0;ver--){
    leftServo.write(90-ver);
    rightServo.write(100+ver);
    delay(15);
  }
}

void dragBox1(int text){
  if (text==0){
        for (hor;hor<165;hor++){
          midServo.write(hor);
          delay(15);
        }
    }
    else if (text==1){
        if (hor==80){
          delay(100);
        }
        else if (hor==165){
          for (hor;hor>80;hor--){
            midServo.write(hor);
            delay(15);
          }
        }
        else if (hor==10){
          for (hor;hor<80;hor++){
            midServo.write(hor);
            delay(15);
          }
        }
    }
    else if (text==2){
        for (hor;hor>10;hor--){
          midServo.write(hor);
          delay(15);
        }
    }
}

// Area 2: 0 = lRed, 1 = lGreen, 2 = lBlue, 3 = rBlue, 4 = rGreen, 5 = rRed
void dragBox2(int color){
  switch (color){
  case 0:
    for (hor;hor<165;hor++){
      midServo.write(hor);
      delay(15);
    }
    break;
  case 1:
    if (hor<131){
      for(hor;hor<131;hor++){
        midServo.write(hor);
        delay(15);
      }
    }
    else{
      for(hor;hor>=131;hor--){
        midServo.write(hor);
        delay(15);
      }
    }
    break;
  case 2:
    if (hor<97){
      for(hor;hor<97;hor++){
        midServo.write(hor);
        delay(15);
      }
    }
    else{
      for(hor;hor>=97;hor--){
        midServo.write(hor);
        delay(15);
      }
    }
    break;
  case 3:
    if (hor>66){
      for(hor;hor>66;hor--){
        midServo.write(hor);
        delay(15);
      }
    }
    else {
      for(hor;hor<=66;hor++){
        midServo.write(hor);
        delay(15);
    }
    break;
  case 4:
    if (hor>38){
      for(hor;hor>38;hor--){
        midServo.write(hor);
        delay(15);
      }
    }
    else{
      for(hor;hor<=38;hor++){
        midServo.write(hor);
        delay(15);
      }
    }
    break;
  case 5:
    for(hor;hor>=10;hor--){
      midServo.write(hor);
      delay(15);
    }
    break;
    }
  }
}

// 0 = Red, 1 = Green, 2 = Blue, 3 = Dropped, 4 = Lift arm, 5 = 2nd left green, 6 = 2nd left blue, 7 = 2nd change to right, 8 = 2nd right green, 9 = 2nd right blue
void loop() {
  if (radio.available()){
    radio.read(&character, sizeof(character));
    dig= character-'0';
    Serial.println(character);
    /*if ((state==1) && (dig==0 || dig==1 || dig==2)){
      dragBox1(dig);
    }
    else if (dig==3){
      state++;
    }
    else if ((state==1 || state==3) && dig==4){
      liftArm();
      dragBox1(1);
      downArm();
    }
    else if (state==2){
      liftArm();
      dragBox2(0);
      downArm();
      state++;
    }
    else if (state==3){
      switch (dig){
        case 5:
          //Green left
          dragBox2(1);
          break;
        case 6:
          //Blue left
          dragBox2(2);
          break;
        case 7:
          //Change to right
          liftArm();
          dragBox2(5);
          downArm();
          break;
        case 8:
          //Green right
          dragBox2(4);
          break;
        case 9:
          //Blue right
          dragBox2(3);
          break;
      }
    }*/
  }
}
