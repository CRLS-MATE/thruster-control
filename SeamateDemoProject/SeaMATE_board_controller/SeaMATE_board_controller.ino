String[] directions = new String[4];

void setup() {

  pinMode(8, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  directions[0] = "Surge";
  directions[1] = "Sway";
  directions[2] = "Heave";
  directions[3] = "Yaw";
}

const int numMotors = 4;

// initialize motor speeds
int motorVelocity[numMotors] = {
  0, 0, 0, 0};
  
// pin mappings for SeaMate board
int motorPinDigital[numMotors] = {
  2, 4, 7, 8};
int motorPinAnalog[numMotors] = {
  3, 5, 6, 9};


void updateMotorController() {
  // iterate through all motors
  for (int i=0; i < numMotors; i++) {
    // extract speed and direction
    int vel = motorVelocity[i];
    int spd = abs(vel);
    int dir = vel > 0 ? HIGH : LOW;

    // set speed and direction
    analogWrite(motorPinAnalog[i], spd);
    digitalWrite(motorPinDigital[i], dir);
  }
  whereAreWeGoing();
}

void whereAreWeGoing()
{ 
  for (int i=0; i < numMotors; i++)
  {
    motorVelocity[i] > 0 ? 
  }
  if (left > 0 && right > 0)  {
  println( "Forward: " +forward +" Left: " +left +" Right: "
  }
  else
  {}
}

void loop() {

  // set desired motor velocities: allowable range is -255 to 255
  
  // for demo purposes, fade the motor up to full speed forward then to full reverse
  motorVelocity[0] = (sin(millis() / 3000.)) * 254;
  motorVelocity[1] = (sin(millis() / 3000.)) * 254;
  motorVelocity[2] = (sin(millis() / 3000.)) * 254;
  motorVelocity[3] = (sin(millis() / 3000.)) * 254;

  // apply these settings
  updateMotorController();

}


