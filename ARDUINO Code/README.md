# Humanoid Robot 2019 Coding

For the circuit, we used:

Component                                  |  Quantity
-------------------------------------------|------------
Arduino Uno Board                          |     1
XL4015 adjustable Power Supply Module      |     2
LIPO battery 1800mAh 4S 25C                |     1
PCA9685 16-Channel 12-bit PWM/Servo Driver |     1
HC06 Bluetooth Module                      |     1
MG996R Servo                               |     8
Switch                                     |     1

For the libraries, we used:
  * <PWMServoDriver.h>: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
  * <SofwareSerial.h>
  
The codes are separated into 2 rounds, elimination and final, because we did alter the design of the robot, the initial angles of the servos so the functions might as well change.

Here is how to connect them together:

<a href="https://learn.adafruit.com/assets/2221"><img src="https://cdn-learn.adafruit.com/assets/assets/000/002/221/original/adafruit_products_Servo_bb-1024.jpg?1396780604" height="300"/></a>

<a href="http://arduino.vn/bai-viet/333-dieu-khien-arduino-thong-qua-bluetooth-bang-dien-thoai-android"><img src="http://k2.arduino.vn/img/2014/11/14/0/815_882662-1415941869-0-arduino-bluetooth-serial---copy.jpg" height="300"/></a>

With the XL4015, one's outputs will connect to the Arduino Board Power Supply (~8V) and the other one's will be linked with the PCA9685 to power the servos (~6V).

Once you have done with the above steps, it's time to number the servos (8 as a whole), set initial angles and connect them to the PCA (0 to 15), I use 0, 2, 4, ..., 14 as you can see in the codes. Remember to disconnect the RX & TX whenever you upload the code.
