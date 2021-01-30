const int LL = 31;
const int LR = 30;
const int TR = 34;
const int ER = 32;
const int TL = 33;
const int EL = 35;

float durationL, distanceL, durationR, distanceR;

bool pillars[8][2];

void setup() {
  pinMode(TL, OUTPUT);
  pinMode(EL, INPUT);
  pinMode(TR, OUTPUT);
  pinMode(ER, INPUT);
  pinMode(LL, OUTPUT);
  pinMode(LR, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TR,LOW);
  digitalWrite(TL,LOW);
  delayMicroseconds(5);
  digitalWrite(TR,HIGH);
  delayMicroseconds(5);
  digitalWrite(TR,LOW);
  durationR=pulseIn(ER, HIGH);
  distanceR = durationR/58.2;
  delayMicroseconds(5);
  digitalWrite(TL,HIGH);
  delayMicroseconds(5);
  digitalWrite(TL,LOW);
  durationL=pulseIn(EL,HIGH);
  distanceL = durationL/58.2;
  Serial.print(distanceL);Serial.print("\t");Serial.println(distanceR);
  if (distanceL<12.0){
    digitalWrite(LL,HIGH);
  }
  if (distanceR<12.0){
    digitalWrite(LR,HIGH);
  }
  delay(1000);
  digitalWrite(LL,LOW);
  digitalWrite(LR,LOW);  
  delay(100);
}
