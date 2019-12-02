#include <SoftwareSerial.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  120 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  595 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz, max = 3500; Datasheet limit is 3052=50MHz/(4*4096)


  pwm.setPWM(6, 0, angleToPulse(45) );    //ra sau, ra ngoai
  pwm.setPWM(14, 0, angleToPulse(135) ); 
  delay(500);
  pwm.setPWM(4, 0, angleToPulse(45) );   //vao trong, toi truoc
  pwm.setPWM(12, 0, angleToPulse(150) );
  delay(500);
  pwm.setPWM(2, 0, angleToPulse(90) );   //ra ngoai, toi truoc
  pwm.setPWM(10, 0, angleToPulse(65) );
  delay(500);
  pwm.setPWM(0, 0, angleToPulse(96) );   //ra truoc, vao trong
  pwm.setPWM(8, 0, angleToPulse(100) );
  pwm.setPWM(15, 0, angleToPulse(98) );
  delay(10);
}

int count = 0;
int angle_i=0;
int angle_ii=0;
void loop() {
  int angle6=45;
  int angle66=150;
  int angle14=135;
  int angle1414=30;
  int angle0=96;
  int angle00=25;
  int angle8=100;
  int angle88=168;
    while (Serial.available()) {
      int dataIn, m;
      int sliderNumber;
      Serial.print("dataIn = ");
      Serial.println(dataIn = (int)Serial.read());  // Read the data
      if (dataIn == 100)
        m = 100;
      if ((dataIn >= 0) && (dataIn <= 95))
        sliderNumber = dataIn;
      if (dataIn == 101)
        m = 101;
      if (dataIn == 102)
        m = 102;
      if (dataIn == 103)
        m = 103;
      if (dataIn == 104)
        m = 104;
      if (dataIn == 105)
        m = 105;
      if (dataIn == 106)
        m = 106;
      if (dataIn == 107)
        m = 107;
      if (dataIn == 108)
        m = 108;
      if (dataIn == 109)
        m = 109;
      if (dataIn == 110)
        m = 110;
    if ((sliderNumber >= 1) && (sliderNumber <= 95)){
      angle_i=sliderNumber;
      Serial.print("both = ");
      Serial.println(angle_i);
      double Angle6=(double)(angle66-(angle66-angle6)/95*angle_ii);
      double Angle66=(double)(angle66-(angle66-angle6)/95*angle_i);
      double Angle14=(double)(angle1414+(angle14-angle1414)/95*angle_ii);
      double Angle1414=(double)(angle1414+(angle14-angle1414)/95*angle_i);
      double Angle0=(double)(angle00+(angle0-angle00)/95*angle_ii);
      double Angle00=(double)(angle00+(angle0-angle00)/95*angle_i);
      double Angle8=(double)(angle88-(angle88-angle8)/95*angle_ii);
      double Angle88=(double)(angle88-(angle88-angle8)/95*angle_i);
      Ultimate4(6,Angle6,Angle66,  14,Angle14,Angle1414,  0,Angle0,Angle00,  8,Angle8,Angle88,  distance(angle_i,angle_ii)*5);
      angle_ii=angle_i;
      sliderNumber=-1;
    }
    if (m == 101){
      Serial.println("Attack");
      Ultimate4(6,angle66,angle6,  14,angle1414,angle14, 0,angle00,angle0,  8,angle88,angle8,  1000);
      delay(50);
      pwm.setPWM(4, 0, angleToPulse(45) );   //vao trong, toi truoc
      pwm.setPWM(12, 0, angleToPulse(150) );
      delay(500);
      pwm.setPWM(2, 0, angleToPulse(90) );   //ra ngoai, toi truoc
      pwm.setPWM(10, 0, angleToPulse(65) );
      delay(500);
      pwm.setPWM(15, 0, angleToPulse(98) );
      delay(10);
      m = -1;
    }
    if (m == 102){
      Serial.println("Defend");
      Ultimate4(6,angle6,angle66,  14,angle14,angle1414, 0,angle0,angle00,  8,angle8,angle88,  1000);
      delay(50);
      pwm.setPWM(4, 0, angleToPulse(45) );   //vao trong, toi truoc
      pwm.setPWM(12, 0, angleToPulse(150) );
      delay(500);
      pwm.setPWM(2, 0, angleToPulse(90) );   //ra ngoai, toi truoc
      pwm.setPWM(10, 0, angleToPulse(65) );
      delay(500);
      pwm.setPWM(15, 0, angleToPulse(98) );
      delay(10);
      m = -1;
    }
      
    if (m == 103) {
      switch (count){
        case 0:
          Forward(count++);
          Forward(count++);
          m = -1;
          break;
        default:
          Forward(count++);
          m = -1;
          break;
      }
    }
    if (m == 104){
       m = -1;
       RightKick(1);
    }
     
    if (m == 105){
       RightKick(2);
       m = -1;
    }
    if (m == 106){
       RightKick(3);
       m =-1;
    }
    if (m == 107){
      GoLeft();
      m =-1;
    }
    if (m == 108){
      GoRight();
      m=-1;
    }
    if (m == 109){
      ForwardStop();
      m=-1;
    }
    if (m == 110){
      LeftTurn();
      m=-1;
    }

    }
}

int angleToPulse(double ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);
  return pulse;
}

int distance(int x,int y){
  int z = (y>x)? (y-x):(x-y);
  return z;
}

void Forward(int count){
   if (count==0){
    // right leg forward from standing
    Serial.println("Forward(0)");
    Ultimate3(10,97,87,  12,170,155,  0,93,62,  200);
    delay(1);
    Ultimate4(0,62,100,   12,155,145,  10,87,72,  8,93,106,  200);
    delay(1);
     
   } 
   else {
    // left leg forward from count = 0, then right leg forward
    Serial.println("Forward(1)");
    Ultimate6(0,100,97,  2,95,115,  4,25,50,  12,145,160,  8,106,145,  10,72,80,  200);
    delay(1);
    Ultimate4(8,145,87,  10,80,99,  12,160,175, 0,97,93,  200);
    delay(1);


    Ultimate4(10,99,79,  12,175,155,  0,93,65,  4,50,35,  200);
    delay(1);
    Ultimate4(0,65,97,  4,35,20,  2,115,95,  8,87,102, 200);
    delay(1);
    Ultimate4(0,97,100,  4,20,25,  8,102,106,   10,79,72,  200);
    delay(1);
    
   }
}

void ForwardStop(){
  //left leg forward to standing
    Serial.println("ForwardStop()");
    Ultimate6(0,100,103,  2,95,123,  4,25,70,  6,93,88,  12,155,145,  8,106,137,  300);
    delay(1);
    Ultimate7(0,103,93,  2,123,95,  4,70,25,  6,88,93,  8,137,93,  10,72,97,  12,145,170,  300);
    delay(1);
   
}

void Backward(){
  //Ultimate8(6,93,85,  14,79,71,  2,95,85,  4,25,30,  0,93,85,  10,97,75,  12,170,160,  8,93,108,  1000);
//  Ultimate();
//  delay(1);
//  Ultimate5(4,30,45,  2,85,80,  6,85,93,  14,71,79,  12,160,160,  1000);
//  delay(1);
//  Ultimate5(0,85,88,   4,45,65,   2,80,130,   6,93,103,   12,160,155,  1000);
//  delay(1);
//  Ultimate6(0,88,90,  6,103,105,  4,65,85,  12,155,145,  14,79,85,  8,93,135,  1000);
//  delay(1);
//  Ultimate7(2,130,110,  4,85,60,  10,75,65,  12,145,143,  8,135,110,  6,105,91,  14,85,79,  1000);
//  delay(1);
//  Ultimate6(0,90,93,  2,110,95,  4,60,25,  8,110,93,  10,65,97,  12,143,170,  1000);
}

void BackwardStop() {
  //left leg backward to standing
}

void LeftKick() {
  //double tap
}

void RightKick(int type) {
  //double tap
  switch(type){
    case 1:
      Serial.println("RightKick(1)");
       
      break;
    case 2:
      Serial.println("RightKick(2)");
       
      break;
    case 3:
      Serial.println("RightKick(3)");
       
      break;
  }


  
}

void GoLeft() {
  Serial.println("GoLeft()");
  //Ultimate4(0,93,78,  6,93,108,  8,93,83,   14,79,89,  300);
  // delay(1);
  // pwm.setPWM(0, 0, angleToPulse(92) );
  Ultimate6(0, 93, 103, 4, 25, 21, 12, 170, 174,   6, 93, 85,  8, 93, 130, 14, 79, 50,  300);
  delay(100);
  Ultimate4(0, 103, 63,  6, 85, 108,  8, 130, 93,  14, 50, 79, 300);
  delay(1);
  pwm.setPWM(6, 0, angleToPulse(93) );
  delay(1);
  Ultimate3(0, 63, 93, 4, 21, 25, 12, 170, 174, 100);
  
}

void GoRight() {
  Serial.println("GoRight()");
  Ultimate6(0, 93, 83, 4, 25, 21, 12, 170, 174, 6, 93, 100, 8, 93, 88, 14, 79, 87, 175);
  delay(1);
  Ultimate4(0, 83, 65, 6, 100, 118, 8, 88, 90, 14, 87, 80, 175);
  delay(1);
  Ultimate4(0, 65, 105, 6, 118, 90, 8, 90, 130, 14, 80, 65, 175);
  delay(1);
  pwm.setPWM(14, 0, angleToPulse(79) );
  pwm.setPWM(0, 0, angleToPulse(120) );
  pwm.setPWM(8, 0, angleToPulse(125) );
  delay(350);
  Ultimate6(0, 120, 93, 4, 21, 25, 12, 174, 170, 6, 90, 93, 8, 125, 93, 14, 65, 79,  200);
  delay(200);
 
}

void LeftTurn() {

    Serial.println("LeftTurn()");
    Ultimate6(6,93,83, 14,79,69, 4,25,65, 2,95,130, 10,97,110, 12,170,180, 200);
    delay(50);
    Ultimate6(10,110,100, 12,180,160,6,83,89, 14,69,80, 8,93,84, 4,65,60 ,200 );
    delay(50);
    Ultimate5(0,93,75, 6,89,97, 4,60,45, 12, 160,175, 2,130,115, 200);
    delay(50);
    Ultimate7(4,45,38, 2,115,110, 6,97,93, 0,80,77, 8, 84,82, 12,175,180,10,100,105,  200);
    delay(10);
    
    pwm.setPWM(2, 0, angleToPulse(80) );    //ra sau, ra ngoai 87
    pwm.setPWM(14, 0, angleToPulse(79) );
    pwm.setPWM(4, 0, angleToPulse(5) );
    delay(300);
    Ultimate3(0,77,93, 8,82,93, 6,93,100, 300);
    delay(200);
    Ultimate5(2,80,95, 4,5,25,  6,100,93, 10,105,97, 12,180,170, 500);
    delay(100);
   
}

void RightTurn() {
  //single tap
}

void Ultimate1(int Number, int Start, int End, int Time ) {
  if (End > Start) {
    int timeStep1 = Time / (End - Start);
    for (; Start <= End; Start += 2) {
      pwm.setPWM(Number, 0, angleToPulse(Start) );
      delay(timeStep1);
    }
  }
  if (End < Start) {
    int timeStep2 = Time / (Start - End);
    for (; Start >= End; Start -= 2) {
      pwm.setPWM(Number, 0, angleToPulse(Start) );
      delay(timeStep2);
    }
  }
}


void Ultimate2(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  for (int m = 0; m <= 45; m += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(difference1 * m + Start1)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(difference2 * m + Start2)) );
    delay(Time / 45);
  }
}
void Ultimate3(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(difference1 * a + Start1)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(difference2 * a + Start2)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(difference3 * a + Start3)) );
    delay(Time / 45);
  }
}

void Ultimate4(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Number4, int Start4, int End4, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  double difference4 = (double)(End4 - Start4) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(Start1 + difference1 * a)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(Start2 + difference2 * a)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(Start3 + difference3 * a)) );
    pwm.setPWM(Number4, 0, angleToPulse((double)(Start4 + difference4 * a)) );
    delay(Time / 45);
  }
}

void Ultimate5(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  double difference4 = (double)(End4 - Start4) / 45;
  double difference5 = (double)(End5 - Start5) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(Start1 + difference1 * a)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(Start2 + difference2 * a)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(Start3 + difference3 * a)) );
    pwm.setPWM(Number4, 0, angleToPulse((double)(Start4 + difference4 * a)) );
    pwm.setPWM(Number5, 0, angleToPulse((double)(Start5 + difference5 * a)) );
    delay(Time / 45);
  }
}

void Ultimate6(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  double difference4 = (double)(End4 - Start4) / 45;
  double difference5 = (double)(End5 - Start5) / 45;
  double difference6 = (double)(End6 - Start6) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(Start1 + difference1 * a)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(Start2 + difference2 * a)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(Start3 + difference3 * a)) );
    pwm.setPWM(Number4, 0, angleToPulse((double)(Start4 + difference4 * a)) );
    pwm.setPWM(Number5, 0, angleToPulse((double)(Start5 + difference5 * a)) );
    pwm.setPWM(Number6, 0, angleToPulse((double)(Start6 + difference6 * a)) );
    delay(Time / 45);
  }
}

void Ultimate7(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Number7, int Start7, int End7, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  double difference4 = (double)(End4 - Start4) / 45;
  double difference5 = (double)(End5 - Start5) / 45;
  double difference6 = (double)(End6 - Start6) / 45;
  double difference7 = (double)(End7 - Start7) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(Start1 + difference1 * a)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(Start2 + difference2 * a)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(Start3 + difference3 * a)) );
    pwm.setPWM(Number4, 0, angleToPulse((double)(Start4 + difference4 * a)) );
    pwm.setPWM(Number5, 0, angleToPulse((double)(Start5 + difference5 * a)) );
    pwm.setPWM(Number6, 0, angleToPulse((double)(Start6 + difference6 * a)) );
    pwm.setPWM(Number7, 0, angleToPulse((double)(Start7 + difference7 * a)) );
    delay(Time / 45);
  }
}

void Ultimate8(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Number7, int Start7, int End7, int Number8, int Start8, int End8, int Time ) {
  double difference1 = (double)(End1 - Start1) / 45;
  double difference2 = (double)(End2 - Start2) / 45;
  double difference3 = (double)(End3 - Start3) / 45;
  double difference4 = (double)(End4 - Start4) / 45;
  double difference5 = (double)(End5 - Start5) / 45;
  double difference6 = (double)(End6 - Start6) / 45;
  double difference7 = (double)(End7 - Start7) / 45;
  double difference8 = (double)(End8 - Start8) / 45;
  for (int a = 0; a <= 45; a += 1) {
    pwm.setPWM(Number1, 0, angleToPulse((double)(Start1 + difference1 * a)) );
    pwm.setPWM(Number2, 0, angleToPulse((double)(Start2 + difference2 * a)) );
    pwm.setPWM(Number3, 0, angleToPulse((double)(Start3 + difference3 * a)) );
    pwm.setPWM(Number4, 0, angleToPulse((double)(Start4 + difference4 * a)) );
    pwm.setPWM(Number5, 0, angleToPulse((double)(Start5 + difference5 * a)) );
    pwm.setPWM(Number6, 0, angleToPulse((double)(Start6 + difference6 * a)) );
    pwm.setPWM(Number7, 0, angleToPulse((double)(Start7 + difference7 * a)) );
    pwm.setPWM(Number8, 0, angleToPulse((double)(Start8 + difference8 * a)) );
    delay(Time / 45);
  }
}
