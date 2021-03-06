# include <Servo.h>
//Serial to motor
//Input: joystick values as serial
//Output: value sent to motor

//CONSTANTS!!!
const int numForces = 4;
const int numberOfMotors = 3;
const int motorPolarities[numberOfMotors] = {1, 1, 1}; // 1 for foreward, -1 for reverse
const int maxMotorOutput = 1900;
const int minMotorOutput = 1100;

//END OF CONSTANTS

boolean readyForVal = false;
int joystickForces[numForces]; //array of joystick desired values received
int joystickForceIndex; //stores the joystick number
// {heave, surge, yaw} or {up, foreward, turn right}
int motorOutputs[numberOfMotors]; // Output

Servo servos[numberOfMotors];
byte servoPins[numberOfMotors] = {9, 10, 11}; //Assign Pins Here


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numberOfMotors; i++) {
    servos[i].attach(servoPins[i]); // attach each motor to an arduino pin
    servos[i].writeMicroseconds(1500);
  }
  delay(1000); // delay to allow the ESC to recognize the stopped signal
}
int charToIndex(char digit) { // gives value corresponding to a motor. This is used to update the spot corresponding to that motor.
  switch (digit) {
    case 's': return 0; //surge
    case 'w': return 1;//sway
    case 'h': return 2;//heave
    case 'y': return 3;//yaw
    default: return -1;
  }
}
void evaluateByte(int theByte) {
  if (readyForVal) {
    joystickForces[joystickForceIndex] = map(theByte, 0, 127, -100, 100); //change the value to between -100 and 100 and put it in the correct spot in the array.
    readyForVal = false;
  }
  else {
    joystickForceIndex = charToIndex(theByte);
    readyForVal = true;
  }
}

void loop() {
  int incomingByte; //to store byte

  if (Serial.available() > 0)
  {
    incomingByte = Serial.read(); //stores next serial value
    evaluateByte(incomingByte); //sends to function to read serial value
  }

  motorOutputs[0] = motorPolarities[0] * joystickForces[0]; // Vertical Motor
  motorOutputs[1] = motorPolarities[1] * (joystickForces[1] + joystickForces[2]); // Left Side Motor
  motorOutputs[2] = motorPolarities[2] * (joystickForces[1] - joystickForces[2]); // Right Side Motor
  for (int i = 0; i < numberOfMotors; i++) {
    motorOutputs[i] = constrain(map(motorOutputs[i], -100, 100, minMotorOutput, maxMotorOutput), minMotorOutput, maxMotorOutput);

    for (int i = 0; i < numberOfMotors; i++) {
      servos[i].writeMicroseconds(motorOutputs[i]);
    }
  }
}

