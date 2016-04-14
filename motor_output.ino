//motor output
# include <Servo.h>

const int numberOfMotors = 3;

int motorOutputs[numberOfMotors] = {0,0,0}; // Fake Input For Testing Only

Servo servos[numberOfMotors];
byte servoPins[numberOfMotors] = {1,2,3}; //Assign Pins Here

void setup() {
  for(int i = 0; i < numberOfMotors; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].writeMicroseconds(1500);
  }
  delay(1000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  for(int i = 0; i < numberOfMotors; i++) {
    servos[i].writeMicroseconds(motorOutputs[i]);
  }
}
