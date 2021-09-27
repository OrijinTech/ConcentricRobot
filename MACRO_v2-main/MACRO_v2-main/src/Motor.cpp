#include "Motor.h"

/**
 * Constructor for Motor class
 * 
 * @param enablePin analog enable pin to h-bridge
 * @param _in1 digital in1 h-bridge pin
 * @param _in2 digital in2 h-bridge pin 
*/
Motor::Motor(uint8_t enablePin, uint8_t _in1, uint8_t _in2, bool reverse = false){
    this->enablePin = enablePin;
    this->in1 = _in1;
    this->in2 = _in2;
    this->reverse = reverse;
}


/**
 * Init
 * 
 * declare pintouts for the motor pins
 *
*/
void Motor::Init(){
  pinMode(this->enablePin, OUTPUT);
    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
}


/**
 * Sends command to h-bridge to drive motor
 * 
 * @param speed value between -1 and 1 for percentage of full speed to drive, where
 *              -1 is full reverse, 1 is full forward, and 0 is stopped
*/
void Motor::drive(double speed){
  // check if motor should be stopped
  if (speed == 0){
    digitalWrite(this->in1, 0);
    digitalWrite(this->in2, 0);
    analogWrite(this->enablePin, 0);
    return;
  }

  // Check direction
  bool isForward = true;
  if (speed < 0){
    isForward = false;
  }

  // cap speed at max speed
  speed = abs(speed);
  if (speed >= 1){
    speed = 1;
  }

  if (reverse) isForward = !isForward;
  // Serial.println(isForward);

  // Set direction of motor
  float writeSpeed;
  if (isForward){
    digitalWrite(this->in1, 1);
    digitalWrite(this->in2, 0);
    writeSpeed = speed * (this->maxSpeed - this->for_deadzone) + this->for_deadzone;
  }
  else {
    digitalWrite(this->in1, 0);
    digitalWrite(this->in2, 1);
    writeSpeed = speed * (this->maxSpeed - this->rev_deadzone) + this->rev_deadzone;
  }
  
  // Set speed of motor
  analogWrite(this->enablePin, writeSpeed);
}

void Motor::stop(){
  this->drive(0);
}

/**
 * Sets the deadband for the motor, the minimum voltage that it takes for the motor
 * move both forwards and backwards.
 * Measured experimentally using a power supply.
 * 
 * @param for_deadzone (VOLTS) min value to drive forward  
 * @param rev_deadzone (VOLTS) min value to drive backwards
*/
void Motor::setDeadzones(double for_deadzone, double rev_deadzone){
  //takes in a voltage that the motors start moving at 
  this->for_deadzone = (for_deadzone / this->maxVolts) * maxSpeed;
  this->rev_deadzone = (rev_deadzone / this->maxVolts) * maxSpeed;
}


void Motor::setMaxSpeed(uint16_t max){
  this->maxSpeed = max;
}