        #include <Servo.h> 
        
        int nextDesireForce; //index of next desire value
        const int numMotors = 4;
        const int numForces = 4;
        
        String directionName[numMotors];
        int directionVal[numMotors];
        int desireForce [numForces];
    
        // initialize motor speeds
        int motorVelocity[numMotors] = {
          0, 0, 0, 0};
        const int leftMotor = 0;
        const int rightMotor = 1;
        const int backMotor = 2;
        const int cornerMotor = 3;
        
        int desireForcce[numForces] = { 
          0 , 0 , 0, 0};
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
          nextDesireForce = -1;
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
            int maxValForMotor[numMotors] = {255, 255, 255, 255};
            spd = min (maxValForMotor[i], spd); //saftey line for the max value 
      //      directionVal[ i ] = map(motorVelocity[ i ], 0, 127, -maxValForMotor[i], maxValForMotor[i]);
           }
            
            analogWrite(motorPinAnalog[i], spd);
            digitalWrite(motorPinDigital[i], dir);
          }
        }
        
        void desireToVelocity(){
          const float k = 1; 
          const float a = 1; 
          const float b = 1; 
          const float c = 1; 
          const float d = 1;
          
          int s = desireForce[0];
          int w = desireForce[1];
          int h = desireForce[2];
          int y = desireForce[3];
          
          motorVelocity[leftMotor] = k * s - a * y + b * w;
          motorVelocity[rightMotor] = k * s + a * y - b * w;
          motorVelocity[backMotor] = c * y + d * w;
          motorVelocity[cornerMotor] = h;
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
          
          if (Serial.available() > 0) { // get the number if how many char to read from the serial port
            incomingByte = Serial.read();
            if (nextDesireForce == -1) {
              nextDesireForce = forceOfChar(incomingByte);
            } else {
              //double the range of the income byte and make it from -127 - 127
              desireForce[nextDesireForce] = 2*(incomingByte) - 127;
              nextDesireForce = -1;
            }
          }
          
          desireToVelocity();    
          updateMotorController(); //
          //printDirections(); //Only use during debugging
        }
