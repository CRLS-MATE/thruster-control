          #include <Servo.h>

          Servo servo0; // name servos
          Servo servo1;
          Servo servo2;
          Servo servo3;
          
          const byte ServoPin0 = 6; // assign pin numbers
          const byte ServoPin1 = 7;
          const byte ServoPin2 = 8;
        
          int nextDesireForce; //index of next desire value
          const int numMotors = 3;
          const int numForces = 3;
          String directionName[numMotors];
          String motorName[numMotors];
          int desireForce [numForces]; // initialize motor speeds
          int motorVelocity[numMotors] = {
            0, 0, 0};
          int motorPolarity[numMotors] = {true, false, false};
          // 0 = MTR1
          // 1 = MTR2
          // 2 = MTR3

          const int leftMotor = 1; 
          const int rightMotor = 3; 
          const int backMotor = 0; 
          const int cornerMotor = 2; 
          int desireForcce[numForces] = { 
            0 , 0 , 0, 0};
          // pin mappings for SeaMate board


void setup() {
  initializeESC();
  servo0.attach(ServoPin0);
  servo0.writeMicroseconds(1500);
  servo1.attach(ServoPin1);
  servo1.writeMicroseconds(1500);
  servo2.attach(ServoPin2);
  servo2.writeMicroseconds(1500);
  delay(1000); // delay to allow the ESC to recognize the stopped signal
  
            Serial.begin(9600);
            directionName[0] = "Surge";
            directionName[1] = "Sway";
            directionName[2] = "Heave";
            directionName[3] = "Yaw";
            
            motorName[leftMotor] = "left";
            motorName[rightMotor] = "right";
            motorName[topMotor] = "top";
            nextDesireForce = -1; 
}

          void updateMotorController() {
  
            int maxValForMotor[numMotors]; 
            maxValForMotor[leftMotor] = 1900;
            maxValForMotor[rightMotor] = 1900;
            maxValForMotor[topMotor] = 1900;
  
            // iterate through all motors
            for (int i=0; i < numMotors; i++) {
              // extract speed and direction
              int vel = motorVelocity[i];
              if (!motorPolarity[i]) vel = vel * -1;
              int spd = abs(vel);
              int dir = vel > 0 ? HIGH : LOW;
              
              //prevent the motor from buzzing by changing the speed value at low thrust to zero
              if  (spd <= 40){
                spd = 0;
              }
              // set speed and direction
              
             for ( int i = 0 ; i < numMotors ; i++ )  {
              spd = min (maxValForMotor[i], spd); //saftey line for the max value 
        //      directionVal[ i ] = map(motorVelocity[ i ], 0, 127, -maxValForMotor[i], maxValForMotor[i]);
             }
              
              Servo[i].writeMicroseconds(spd);
            }
          }

 void desireToVelocity(){
            const float k = 1; // surge coff 
            //const float a = 1; // yaw coff
            const float b = 1; // sway coff
            //const float c = 1; // yaw coff for the back
            const float d = -1; // sway coff for the back
            
            int s = desireForce[0];
            int w = desireForce[1];
            int h = desireForce[2];
            int y = desireForce[3];
            
            motorVelocity[leftMotor] = k * s - a * y + b * w;
            motorVelocity[rightMotor] = k * s + a * y - b * w;
            //motorVelocity[backMotor] = c * y + d * w;
            motorVelocity[topMotor] = h;
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

          
          void loop() 
          { 
            char incomingByte;
            bool gotData = false;
            
            if (Serial.available() > 0) { // get the number if how many char to read from the serial port
              incomingByte = Serial.read();
              if (nextDesireForce == -1) {
                nextDesireForce = forceOfChar(incomingByte);
              } else {
                //income byte 0 -127 and it is mapped with -255 to 255
                desireForce[nextDesireForce] = map(incomingByte, 0, 127, 1100, 1900);// 4*(incomingByte) - 127;
                nextDesireForce = -1;
                gotData = true;
              }
            }
            

            if (gotData) {
              desireToVelocity();    
              updateMotorController(); //
              //printDirections(); //Only use during debugging 
              gotData = false;
            }
            
          }
