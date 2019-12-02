#include <Wire.h>
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
SoftwareSerial Bluetooth(10, 11);

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz, max = 3500; Datasheet limit is 3052=50MHz/(4*4096)
}


void loop() {
  while (Bluetooth.available()) {
    char dataIn, m;
    Serial.println(dataIn = (char) Bluetooth.read());  // Read the data
    if (dataIn == 'a') {
      m = 'a';
    }
    if (dataIn == 'b') {
      m = 'b';
    }
    if (dataIn == 'c') {
      m = 'c';
    }
    if (dataIn == 'd') {
      m = 'd';
    }
    if (dataIn == 'e') {
      m = 'e';
    }
    if (dataIn == 'f') {
      m = 'f';
    }
    if (dataIn == 'A') {
      m = 'A';
    }
    if (dataIn == 'B') {
      m = 'B';
    }
    if (dataIn == 'g') {
      m = 'g';
    }
    if (dataIn == 'h') {
      m = 'h';
    }
    if (dataIn == 'i') {
      m = 'i';
    }
int count=0;
  while (m == 'a') {
    Forward(count++);
  }
  while (m == 'b') {
    Backward(count++);
  }
  while (m == 'c') {
    LeftKick();
  }
  while (m == 'd') {
    RightKick();
  }
  while (m == 'e') {
    GoLeft();
  }
  while (m == 'f') {
    GoRight();
  }
  if (m == 'A') {
    ForwardStop();
    count=0;
  }
  if (m == 'B') {
    BackwardStop();
    count=0;
  }
  if (m == 'h') {
    LeftTurn();
  }
  if (m == 'i') {
    RightTurn();
  }

  }

   
  pwm.setPWM(6, 0, angleToPulse(87) );    //ra sau, ra ngoai 
  pwm.setPWM(14, 0, angleToPulse(95) ); 
  delay(500);
  pwm.setPWM(4, 0, angleToPulse(45) );   //vao trong, toi truoc
  pwm.setPWM(12, 0, angleToPulse(145) );
  delay(500);
  pwm.setPWM(2, 0, angleToPulse(95) );   //ra ngoai, toi truoc
  pwm.setPWM(10, 0, angleToPulse(85) );
  delay(500);
  pwm.setPWM(0, 0, angleToPulse(90) );   //ra truoc, vao trong
  pwm.setPWM(8, 0, angleToPulse(97) );
  delay(500);


delay(2000);
Ultimate4(8,97,87,  6,87,97,  0,90,70,  14,95,105,  1000);
delay(10);
Ultimate4(4,45,65,  2,95,115,  0,70,90,  6,97,87,  1000);
delay(10);


Ultimate4(0,90,100,  6,87,77,  8,87,117,  14,105,75,  1000);
delay(10);
Ultimate4(8,117,97,  10,85,55,  12,145,115,  14,75,95,  1000);






delay(5000);
}

int angleToPulse(double ang){
   int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);
   return pulse;
}

void Forward(int count){
   if (count==0){
    // right leg forward from standing
    Ultimate3( 10,85,75, 12,145,130,  0,90,75,   150);
    delay(10);
    Ultimate3(0,65,98,   12,130,120,  10,75,60,  150);
    delay(10);
   } 
   
   else {
    // left leg forward from count = 0, then right leg forward
    Ultimate5(2,95,115,  4,45,70,  12,120,135,  8,97,112,  10,60,68,  150);
    delay(10);
    Ultimate4(8,112,91,  10,68,87,  12,135,140, 0,98,95,  150);
    delay(10);


    Ultimate4(10,87,67,  12,140,120,  0,95,75,  4,70,55, 150);
    delay(10);
    Ultimate3(0,75,95,  4,55,35,  2,115,95, 150);
    delay(10);
    Ultimate4(0,95,98,  4,35,45,  8,91,97,   10,67,60,  150);
    delay(10);
   }
}

void ForwardStop(){
  //left leg forward to standing
  
    Ultimate4(2,95,123,  4,45,75,  12,120,130,  8,97,111,  150);
    delay(10);
    Ultimate6(0,98,90,  2,123,95,  4,75,45,  8,111,97,  10,60,85,  12,130,145, 150);
    delay(10);
}

void Backward(int count){
   if (count==0){
    // right leg backward from standing
   } 
   else {
    // left leg backward from count = 0, then right leg backward
   }
}

void BackwardStop(){
  //left leg backward to standing
}

void LeftKick(){
  //double tap
}

void RightKick(){
  //double tap
}

void GoLeft(){
  Ultimate4( 0,90,75,  6,85,100,  8,97,87, 14,93,103,  200);
  delay(50);                                          
  Ultimate4(0,75,92,   6,100,85,  8,87,120, 14, 103,81, 200);
  delay(50);
  Ultimate4(0,92,67,  6,85,100,  8,120,97,  14,81,93, 200);
  delay(50);
  Ultimate1(6,100,85, 50);
  delay(50);
  Ultimate1(0,67,90, 50);
  delay(50);
}

void GoRight(){
  Ultimate4(0,90,95,  6,85,80,  8,97,107, 14,93,83,  200);
  delay(50); 
  Ultimate4(0,95,75,   6,80,95,  8,107,97, 14, 83,93, 200);
  delay(50);   
  Ultimate4( 0,75,105,  6,95,75,  8,97,117, 14,93,73,  200);
  delay(50);
  Ultimate2(8,117,107,  14,73,83,  50);
  delay(50);
  pwm.setPWM(14, 0, angleToPulse(93) );
  delay(50); 

}

void LeftTurn(){
  //single tap
}

void RightTurn(){
  //single tap
}

void Ultimate1(int Number, int Start, int End, int Time){
  if (End > Start){
    int timeStep1 = Time/(End-Start);
    for(; Start<=End;Start +=2){
    pwm.setPWM(Number, 0, angleToPulse(Start) );
    delay(timeStep1);
    }
  }
  if (End < Start){
    int timeStep2 = Time/(Start-End);
    for(; Start>=End;Start -=2){
    pwm.setPWM(Number, 0, angleToPulse(Start) );
    delay(timeStep2);
    }
  }
}

  
void Ultimate2(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45;
    for(int m=0; m<=45; m +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(difference1*m+Start1)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(difference2*m+Start2)) );
      delay(Time/45);
    }
}
void Ultimate3(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(difference1*a+Start1)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(difference2*a+Start2)) );
      pwm.setPWM(Number3, 0, angleToPulse((double)(difference3*a+Start3)) );
      delay(Time/45);
    }
}

void Ultimate4(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3,int Number4, int Start4, int End4, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
  double difference4 = (double)(End4-Start4)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(Start1+difference1*a)) ); 
      pwm.setPWM(Number2, 0, angleToPulse((double)(Start2+difference2*a)) ); 
      pwm.setPWM(Number3, 0, angleToPulse((double)(Start3+difference3*a)) ); 
      pwm.setPWM(Number4, 0, angleToPulse((double)(Start4+difference4*a)) ); 
      delay(Time/45);
    }
}

void Ultimate5(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3,int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
  double difference4 = (double)(End4-Start4)/45; 
  double difference5 = (double)(End5-Start5)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(Start1+difference1*a)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(Start2+difference2*a)) );
      pwm.setPWM(Number3, 0, angleToPulse((double)(Start3+difference3*a)) );
      pwm.setPWM(Number4, 0, angleToPulse((double)(Start4+difference4*a)) );
      pwm.setPWM(Number5, 0, angleToPulse((double)(Start5+difference5*a)) );
      delay(Time/45);
    }
}

void Ultimate6(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3,int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
  double difference4 = (double)(End4-Start4)/45; 
  double difference5 = (double)(End5-Start5)/45; 
  double difference6 = (double)(End6-Start6)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(Start1+difference1*a)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(Start2+difference2*a)) );
      pwm.setPWM(Number3, 0, angleToPulse((double)(Start3+difference3*a)) );
      pwm.setPWM(Number4, 0, angleToPulse((double)(Start4+difference4*a)) );
      pwm.setPWM(Number5, 0, angleToPulse((double)(Start5+difference5*a)) );
      pwm.setPWM(Number6, 0, angleToPulse((double)(Start6+difference6*a)) );
      delay(Time/45);
    }
}

void Ultimate7(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3,int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Number7, int Start7, int End7, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
  double difference4 = (double)(End4-Start4)/45; 
  double difference5 = (double)(End5-Start5)/45; 
  double difference6 = (double)(End6-Start6)/45; 
  double difference7 = (double)(End7-Start7)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(Start1+difference1*a)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(Start2+difference2*a)) );
      pwm.setPWM(Number3, 0, angleToPulse((double)(Start3+difference3*a)) );
      pwm.setPWM(Number4, 0, angleToPulse((double)(Start4+difference4*a)) );
      pwm.setPWM(Number5, 0, angleToPulse((double)(Start5+difference5*a)) );
      pwm.setPWM(Number6, 0, angleToPulse((double)(Start6+difference6*a)) );
      pwm.setPWM(Number7, 0, angleToPulse((double)(Start7+difference7*a)) );
      delay(Time/45);
    }
}

void Ultimate8(int Number1, int Start1, int End1, int Number2, int Start2, int End2, int Number3, int Start3, int End3,int Number4, int Start4, int End4, int Number5, int Start5, int End5, int Number6, int Start6, int End6, int Number7, int Start7, int End7, int Number8, int Start8, int End8, int Time ){
  double difference1 = (double)(End1-Start1)/45; 
  double difference2 = (double)(End2-Start2)/45; 
  double difference3 = (double)(End3-Start3)/45; 
  double difference4 = (double)(End4-Start4)/45; 
  double difference5 = (double)(End5-Start5)/45; 
  double difference6 = (double)(End6-Start6)/45; 
  double difference7 = (double)(End7-Start7)/45; 
  double difference8 = (double)(End8-Start8)/45; 
    for(int a=0; a<=45; a +=1){
      pwm.setPWM(Number1, 0, angleToPulse((double)(Start1+difference1*a)) );
      pwm.setPWM(Number2, 0, angleToPulse((double)(Start2+difference2*a)) );
      pwm.setPWM(Number3, 0, angleToPulse((double)(Start3+difference3*a)) );
      pwm.setPWM(Number4, 0, angleToPulse((double)(Start4+difference4*a)) );
      pwm.setPWM(Number5, 0, angleToPulse((double)(Start5+difference5*a)) );
      pwm.setPWM(Number6, 0, angleToPulse((double)(Start6+difference6*a)) );
      pwm.setPWM(Number7, 0, angleToPulse((double)(Start7+difference7*a)) );
      pwm.setPWM(Number8, 0, angleToPulse((double)(Start8+difference8*a)) );
      delay(Time/45);
    }
}
