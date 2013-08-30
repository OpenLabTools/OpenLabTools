// Include the required libraries
 #include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

// Define constants for the input pins
#define UP_BUTTON 0
#define DOWN_BUTTON 1
#define TOP_ENDSTOP 2
#define BOTTOM_ENDSTOP 3

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

// Set up inputs
pinMode(UP_BUTTON, INPUT);
pinMode(DOWN_BUTTON, INPUT);
pinMode(TOP_ENDSTOP, INPUT);
pinMode(BOTTOM_ENDSTOP, INPUT);

}

void loop()
{
  // Get the current states of the buttons
  bool up_pressed = digitalRead(UP_BUTTON);
  bool down_pressed = digitalRead(DOWN_BUTTON);
  
  // If both buttons are pressed, do nothing
  if(up_pressed && down_pressed) 
    return;
    
  // If the up button is pressed and the stage hasn't 
  // reached the endstop, go up
  if(up_pressed && !digitalRead(TOP_ENDSTOP))
    myMotor->step(1, FORWARD, DOUBLE);
    
  // If the down button is pressed and the stage hasn't 
  // reached the endstop, go up
  if(down_pressed && !digitalRead(TOP_ENDSTOP))
    myMotor->step(1, BACKWARD, DOUBLE);
}

