#include <Servo.h> 

const int numMotors = 4;

Servo myservo[numMotors];  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

// initialize motor positions
int motorPosition[numMotors] = {128, 128, 128, 128};

int serialState;

void setup() 
{ 
  Serial.begin(9600);
  serialState = -1;
  myservo[0].attach(3);  // attaches the servo on pin 3 to the servo object 
  myservo[1].attach(5);  
  myservo[2].attach(6);  
  myservo[3].attach(9);  
} 


void updateMotorController() {
  // iterate through all motors
  for (int i=0; i < numMotors; i++) {
    myservo[i].write(motorPosition[i]);
  }
}

int intOfDigitChar(char digit) {
 switch (digit) {
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  case '3': return 3;
  default: return -1;
 } 
}

void loop() 
{ 
  char incomingByte;
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (serialState == -1) {
      serialState = intOfDigitChar(incomingByte);
    } else {
      motorPosition[serialState] = incomingByte;
      serialState = -1;
    }
  }
  
  updateMotorController();
}
