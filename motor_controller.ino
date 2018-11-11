int Ain1 = 9;    // LED connected to digital pin 9
int Ain2 = 10;

void setup() {
  // nothing happens in setup
}

void l1() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(Ain1, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(Ain1, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}

void l2() {
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(Ain2, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(Ain2, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
}



void loop() {
  l1();
  l2();

}
