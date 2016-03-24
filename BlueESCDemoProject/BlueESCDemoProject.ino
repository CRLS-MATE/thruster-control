#include <Servo.h>

const byte servoPin = 9;
const byte ledPin = 13;

const int FULL_FORWARD = 1900;
const int FULL_REVERSE = 1100;
const int FULL_STOP    = 1500;

Servo servo;

/************************ 

This is the sample program for the T100 thruster with a BlueESC controller attached.


TO USE THIS

Electrical connections
----------------------

You should see 2 cables: one is the power cable (red and black wires, medium thickness).  
The other is the signal cable (black, white, green, and either red or yellow wires, thin).

1. Connect the black SIGNAL wire from the BlueESC to the negative terminal of the battery
2. Connect the Arduino's GND pin to the negative terminal of the battery
3. Connect pin 9 of the Arduino to the red (or yellow) SIGNAL wire
4. Connect the black POWER wire from the motor to the negative terminal of the battery.
5. Connect the red POWER wire from the motor to the positive terminal of the battery


Setup
-----

According to the BlueESC manual, you should reset the Arduino, THEN connect the red power wire.
This should allow the ESC to initialize.  In my testing, this doesn't seem to matter.  But if all
else fails, do this:

1. Disconnect the red POWER wire
2. Reset the Arduino
3. Wait for the Arduino LED to blink short-short-loooong.
4. Anytime while the LED is blinking, reconnect the red POWER wire


Programming
-----------

Use this: 

    servo.writeMicroseconds(i);

Where the value of i is between FULL_REVERSE and FULL_FORWARD.

****************************/



// Blink the LED short, short and LONG while sending the stop signal to the 
void initializeESC() {
  servo.writeMicroseconds(FULL_STOP); // send "stop" signal to ESC.
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(5000); // delay to allow the ESC to recognize the stopped signal
  digitalWrite(ledPin, LOW);
}

void fadeThrottle(int from, int to) {
  int stepSize = from <= to ? 1 : -1;
  
  for (int i = from; i != to; i = i + stepSize) {
    servo.writeMicroseconds(i);
    delay(60); 
  }
}

// Set up the LED pin and the servo pin, then initialize the ESC
void setup() {
  pinMode(ledPin, OUTPUT);
  servo.attach(servoPin);
  initializeESC();
}


// Throttle up to partial reverse then to zero, then partial forward, then to zero. 
// Then wait 3 seconds.
void loop() {
  fadeThrottle(FULL_STOP, 1400);
  fadeThrottle(1400, FULL_STOP);
  fadeThrottle(FULL_STOP, 1600);
  fadeThrottle(1600, FULL_STOP);
  delay(3000);
}


