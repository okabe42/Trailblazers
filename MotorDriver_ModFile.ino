// ENCODER AND MOTOR MOVEMENT //
#include <Encoder.h>
long oldPosition1  = -999;

//wheel 1
const int m1_1 = 7;   // AIN1
const int m1_2 = 8;   // AIN2

//wheel 2
const int m2_1 = 2;
const int m2_2 = 4;

// 
const int m1_pwm = 3; //A
const int m2_pwm = 5; //B

const int ledPin = 13;

// encoder for motor1
/*
int val1;
int encoder0PinA1 = 6;
int encoder0PinB1 = 9;
int encoder0Pos = 0;
int encoder0PinALastState = LOW;
int APosition = LOW;
// encoder for motor2
int val2;
int encoder0PinA2 = 12;
int encoder0PinB2 = 13;
int encoder0Pos = 0;
int encoder0PinALastState = LOW;
int APosition = LOW;
*/

Encoder myEnc1(6, 9);
//Encoder myEnc2(11, 12);

void setupmotorencoder() {        // setup runs once
  pinMode(m1_1, OUTPUT);
  pinMode(m1_2, OUTPUT);
  pinMode(m2_1, OUTPUT);
  pinMode(m2_2, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //encoder
 // pinMode (encoder0PinA, INPUT);
  //pinMode (encoder0PinB, INPUT);
  //Serial.begin (9600);

  // encoder
  Serial.begin(9600);
  Serial.print("Basic Encoder1 Test:");
  //Serial.println("\tBasic Encoder2 Test:");
}

void forward(int spd) {
  digitalWrite(m1_1, LOW);
  digitalWrite(m1_2, HIGH);
  digitalWrite(m2_1, LOW);
  digitalWrite(m2_2, HIGH);
  analogWrite(m1_pwm, spd);
  analogWrite(m2_pwm, spd);
}

void backward(int spd) {
  digitalWrite(m1_1, HIGH);
  digitalWrite(m1_2, LOW);
  digitalWrite(m2_1, HIGH);
  digitalWrite(m2_2, LOW);
  analogWrite(m1_pwm, spd);
  analogWrite(m2_pwm, spd);
}
void go(int spd){
  if (spd > 0){
    forward(spd);
  }
  else if (spd < 0){
    backward(-spd);
  }
  else {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_2, LOW);
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_2, LOW);
    analogWrite(m1_pwm, 0);
    analogWrite(m2_pwm, 0);
  }
}
void rotate(int counter, int spd)
{
  // to turn left
  if (counter == 1)
  {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_2, HIGH);
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_2, LOW);
    analogWrite(m1_pwm, spd);
    analogWrite(m2_pwm, 0);
  }

  // to turn right
  else if (counter == 2)
  {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_2, LOW);
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_2, HIGH);
    analogWrite(m1_pwm, 0);
    analogWrite(m2_pwm, spd);
  }

  // to stop
  else if (counter == 0)
  {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_2, LOW);
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_2, LOW);
    analogWrite(m1_pwm, 0);
    analogWrite(m2_pwm, 0);
  }
}

void turn (int spd, int secs, int counter)
{
  rotate(counter, spd);
  sleep(secs);
  rotate(0, spd);
}
}
