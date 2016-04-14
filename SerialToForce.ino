//Serial to force
//Input: joystick values as serial
//Output: array of joystick forces (called joystickForces) on a -100 to 100 scale

//CONSTANTS!!!
const int numForces = 4;

//END OF CONSTANTS

boolean readyForVal = false;
int joystickForces[numForces];
int joystickForceIndex;

void setup(){
  Serial.begin(9600);
}

void loop() {
  int incomingByte;

  if(Serial.available()>0)
  {
    incomingByte = Serial.read();
    evaluateByte(incomingByte);
  }
}

void evaluateByte(int theByte) {
  if (readyForVal) {
    joystickForces[joystickForceIndex] = map(theByte, 0, 127, -1.0, 1.0);
    readyForVal = false;
  }
  else {
    joystickForceIndex = charToIndex(theByte);
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
