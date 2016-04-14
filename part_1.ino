//CONSTANTS!!!
const int numMotors = 3;

//END OF CONSTANTS

boolean readyForVal = false;
int motorForces[numMotors];
int motorIndex;

void loop() {
  int incomingByte;

  if(Serial.available()>0)
  {
    incomingByte = Serial.read();
    evaluateByte(incomingByte);
  }
}

evaluateByte(int theByte) {
  if (readyForVal) {
    motorForces[motorIndex] = map(theByte, 0, 127, 1100, 1900);
    readyForVal = false;
  }
  else {
    motor = charToIndex(theByte)
    readyForVal = true;
  }
}

int charToIndex(char digit) {
  switch (digit) {
    case 's': return 0;
    case 'w': return 1;
    case 'h': return 2;
    case 'y': return 3;
    default: return -1;
  }
}
