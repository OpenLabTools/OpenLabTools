// Include the required libraries
 #include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Create the motor shield object
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Create the stepper motor object
 Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
 
void setup()
{
// Create the link to the motor shield at the default frequency (1Hz)
AFMS.begin(); 

// Set the speed of the motor in rpm
myMotor->setSpeed(100);
}

void loop()
{
// Run the stepper motor. Parameters are:
// 	#steps – number of steps
//	direction – options are FORWARD or BACKWARD
//	steptype – options are SINGLE, DOUBLE, INTERLEAVE or MICROSTEP
myMotor->step(500, FORWARD, DOUBLE);

// Wait for half a second
delay(500);

// Run the motor in the opposite direction
myMotor->step(500, FORWARD, DOUBLE);

// Wait for half a second
delay(500);
}

