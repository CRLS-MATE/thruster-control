# include <Servo.h>
//Serial to motor
//Input: joystick values as serial
//Output: value sent to motor

//CONSTANTS!!!
const int numForces = 4;
const int numberOfMotors = 3;
const int motorPolarities[numberOfMotors] = {-1, -1, -1}; // 1 for foreward, -1 for reverse
const int maxMotorOutput = 1720;
const int minMotorOutput = 1280;

//END OF CONSTANTS

boolean readyForVal = false;
int joystickForces[numForces]; //array of joystick desired values received
int joystickForceIndex; //stores the joystick number
// {heave, surge, yaw} or {up, foreward, turn right}
int motorOutputs[numberOfMotors]; // Output

Servo servos[numberOfMotors];
byte servoPins[numberOfMotors] = {3, 6, 9}; //Assign Pins Here (Up, Left, Right)


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numberOfMotors; i++) {
    servos[i].attach(servoPins[i]); // attach each motor to an arduino pin
    servos[i].writeMicroseconds(1500);
  }
  delay(1000); // delay to allow the ESC to recognize the stopped signal
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

int charToIndex(char digit) { // gives value corresponding to a motor. This is used to update the spot corresponding to that motor.
  switch (digit) {
    case 's': return 1;
    case 'w': return 3;
    case 'h': return 0;
    case 'y': return 2;
    default: return -1;
  }
}

void loop() {
  int incomingByte; //to store byte
  int motorLevels[numberOfMotors]; // intermediate calculation - -100 to 100

  if (Serial.available() > 0)
  {
    incomingByte = Serial.read(); //stores next serial value
    evaluateByte(incomingByte); //sends to function to read serial value


    motorLevels[0] = motorPolarities[0] * joystickForces[0]; // Vertical Motor
    motorLevels[1] = motorPolarities[1] * (joystickForces[1] - joystickForces[2]); // Left Side Motor
    motorLevels[2] = motorPolarities[2] * (joystickForces[1] + joystickForces[2]); // Right Side Motor
    
    for (int i = 0; i < numberOfMotors; i++) {
      // calculate actual PWM value
      motorOutputs[i] = constrain(map(motorLevels[i], -100, 100, minMotorOutput, maxMotorOutput), minMotorOutput, maxMotorOutput);
    }

    // when running with the joystick, this should always be "if (0)" !
    if (0) {
      for (int i = 0; i < numberOfMotors; i++) {
        Serial.print("Motor:");
        Serial.print(i);
        Serial.print(" ");
        Serial.print(motorLevels[i]);
        Serial.print(" ");
        Serial.print(motorOutputs[i]);
        Serial.print("    ");
      }
      Serial.println("");
    }

    for (int i = 0; i < numberOfMotors; i++) {
      servos[i].writeMicroseconds(motorOutputs[i]);
    }
  }
}
