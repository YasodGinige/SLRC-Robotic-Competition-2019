#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

RF24 radio(7,8);
const byte address[8]="#SiRi++";

char character;
int state=0;

Servo midServo; // 150 - 80 - 30
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

  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void dragBox(int text){
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
        else if (hor==0){
          for (hor;hor<90;hor++){
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
 
void loop() {
  if (radio.available()){
    radio.read(&character, sizeof(character));
    int dig= character-'0';
    if ((state==1) && (dig==0 || dig==1 || dig==2)){
      dragBox(dig);
    }
    else if (dig==3){
      state=1;
    }
  }
}
