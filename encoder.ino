//wheel 1
const int m1_1 = 7;
const int m1_2 = 8;

//wheel 2
const int m2_1 = 2;
const int m2_2 = 4;

// 
const int m1_pwm = 3;
const int m2_pwm = 5;

const int ledPin = 13;

// encoder
int val;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALastState = LOW;
int APosition = LOW;

void setup() {        // setup runs once
  pinMode(m1_1, OUTPUT);
  pinMode(m1_2, OUTPUT);
  pinMode(m2_2, OUTPUT);
  pinMode(m2_2, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  //encoder
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  Serial.begin (9600);
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
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH);
  int i;
  for (i = 255; i >= -255; i--){
    go(i);                        // spins the motor
    delay(10);                    // break
  }
  go(0);
  digitalWrite(ledPin, LOW);
  delay(1000);
  go(255);
  delay(5000);
  digitalWrite(ledPin, LOW);
  go(0);
  delay(5000);

  //encoder
  APosition = digitalRead(encoder0PinA);
  if ((encoder0PinALastState == LOW) && (APosition == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }
    Serial.print (encoder0Pos);
    Serial.print ("/");
  }
  encoder0PinALastState = APosition;



}
