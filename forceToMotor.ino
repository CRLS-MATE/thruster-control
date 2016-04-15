// Force to Motor

const int numberOfMotors = 3;

int joystickForces[4] = {0, 0, 0, 0}; // Fake Input For Testing Only

const int numberOfMotors = 3;
const int motorPolarities[numberOfMotors] = {1, 1, 1}; // 1 for foreward, -1 for reverse
const int maxMotorOutput = 1900;
const int minMotorOutput = 1100;

// {heave, surge, yaw} or {up, foreward, turn right}
int joystickForces[3] = {0, 0, 0}; // Fake Input For Testing Only
int motorOutputs[numberOfMotors]; // Output

void setup() {};

void loop()
{
  motorOutputs[0] = motorPolarities[0] * joystickForces[0]; // Vertical Motor
  motorOutputs[1] = motorPolarities[1] * (joystickForces[1] + joystickForces[2]); // Left Side Motor
  motorOutputs[2] = motorPolarities[2] * (joystickForces[1] - joystickForces[2]); // Right Side Motor
  
  for (int i = 0; i < numberOfMotors; i++) {
    motorOutputs[i] = constrain(map(motorOutputs[i], -100, 100, minMotorOutput, maxMotorOutput), minMotorOutput, maxMotorOutput);
  }
}
