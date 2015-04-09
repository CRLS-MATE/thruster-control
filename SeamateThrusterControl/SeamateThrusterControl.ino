#include <Servo.h> 

int serialState;
const int numMotors = 4;

String directionName[numMotors];
int directionVal[numMotors];

// initialize motor speeds
int motorVelocity[numMotors] = {
  0, 0, 0, 0};
// pin mappings for SeaMate board
int motorPinDigital[numMotors] = {
  2, 4, 7, 8};
int motorPinAnalog[numMotors] = {
  3, 5, 6, 9};

void setup() 
{ 
  pinMode(8, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  directionName[0] = "Surge";
  directionName[1] = "Sway";
  directionName[2] = "Heave";
  directionName[3] = "Yaw";
} 

void updateMotorController() {
  // iterate through all motors
  for (int i=0; i < numMotors; i++) {
    // extract speed and direction
    int vel = motorVelocity[i];
    int spd = abs(vel);
    int dir = vel > 0 ? HIGH : LOW;

    // set speed and direction
    
   for ( int i = 0 ; i < numMotors ; i++ )  {
    int maxVarForMotor[numMotors] = {255, 255, 255, 255};
    directionVal[ i ] = map(motorVelocity[ i ], 0, 127, -maxVarForMotor[i], maxVarForMotor[i]);
   }
    
    analogWrite(motorPinAnalog[i], spd);
    digitalWrite(motorPinDigital[i], dir);
  }
}

int forceOfChar(char digit) {
 switch (digit) {
  case 's': return 0;
  case 'w': return 1;
  case 'h': return 2;
  case 'y': return 3;
  default: return -1;
 } 
}

void printDirections()  {
  for ( int i = 0 ; i < numMotors ; i++ )  {
    Serial.print( directionName[i] +": " +directionVal[i] );
    Serial.print( "\t\t" );
  }
  Serial.println();
}

void loop() 
{ 
  char incomingByte;
  
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (serialState == -1) {
      serialState = forceOfChar(incomingByte);
    } else {
      motorVelocity[serialState] = incomingByte;
      serialState = -1;
    }
  }
  
  updateMotorController();
  printDirections();
}
