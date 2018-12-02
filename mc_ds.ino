/*WARNING: Some sensors require 2.8 V VCC. Connect a step-down regulator e.g. LM317.
For VOUT 2.8 V use R1 of 220 Ohm and R2 220 Ohm + 47 Ohm, respectively.
Also, a level shifter must be used for sensors driven with 2.8 V VCC!
In addition to SDA/SCL pins, most sensord have IO0 and IO1 pins. IO0 the enable pin.
After reset, an arbitrary I2C address can be configured, which differs from the hard-coded
I2C of the sensor. Thus, it is possible to use multiple sensors without changeing the
hard-coded address of the module.
*/

#include <Wire.h>
#include <VL6180X.h>

#define RANGE 1

/* List of adresses for each sensor - after reset the address can be configured */
#define address0 0x20
#define address1 0x22
// #define address2 0x24
// #define address1 0x26
// #define address1 0x28
// #define address1 0x30
// #define address1 0x32

/* These Arduino pins must be wired to the IO0 pin of VL6180x */
int enablePin0 = 11;
int enablePin1 = 10;

/* Create a new instance for each sensor */
VL6180X sensor0;
VL6180X sensor1;


//wheel 1
const int m1_1 = 7;   // AIN1
const int m1_2 = 8;   // AIN2

//wheel 2
const int m2_1 = 2;   
const int m2_2 = 4;

// 
const int m1_pwm = 3;
const int m2_pwm = 5;

const int ledPin = 13;
//encoder
int val;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALastState = LOW;
int APosition = LOW;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

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

  // Reset all connected sensors
  pinMode(enablePin0,OUTPUT);
  pinMode(enablePin1,OUTPUT);
  
  digitalWrite(enablePin0, LOW);
  digitalWrite(enablePin1, LOW);

  
  delay(1000);
  
  // Sensor0
  Serial.println("Start Sensor 0");
  digitalWrite(enablePin0, HIGH);
  delay(50);
  sensor0.init();
  sensor0.configureDefault();
  sensor0.setAddress(address0);
  Serial.println(sensor0.readReg(0x212),HEX); // read I2C address
  sensor0.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor0.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor0.setTimeout(500);
  sensor0.stopContinuous();
  sensor0.setScaling(RANGE); // configure range or precision 1, 2 oder 3 mm
  delay(300);
  sensor0.startInterleavedContinuous(100);
  delay(100);
  
  // Sensor1
  Serial.println("Start Sensor 1");
  digitalWrite(enablePin1, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setAddress(address1);
  Serial.println(sensor1.readReg(0x212),HEX);
  sensor1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
  sensor1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);
  sensor1.setTimeout(500);
  sensor1.stopContinuous();
  sensor1.setScaling(RANGE);
  delay(300);
  sensor1.startInterleavedContinuous(100);
  delay(100);

  
  // copy & paste as much sensors as you require
  
  delay(1000);
 
  Serial.println("Sensors ready! Start reading sensors in 3 seconds ...!");
  delay(3000);


  
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
void loop()
{
  // Read daylight (LUX)
  //Serial.print("\tDaylight0: ");
  //Serial.print(sensor0.readAmbientContinuous());
  //if (sensor0.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //Serial.print("\tDaylight1: ");
  //Serial.print(sensor1.readAmbientContinuous());
  //if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  //Serial.print("\tDaylight2: ");
  //Serial.print(sensor1.readAmbientContinuous());
  //if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();


  // Abstand in mm
  Serial.print("\tDistance0: ");
  Serial.print(sensor0.readRangeContinuousMillimeters());
  if (sensor0.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.print("\tDistance1: ");
  Serial.print(sensor1.readRangeContinuousMillimeters());
  if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

//  Serial.print("\tDistance2: ");
//  Serial.print(sensor2.readRangeContinuousMillimeters());
//  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

// copy & paste as much sensors as you require

  Serial.println();
  
  delay(100);
}
