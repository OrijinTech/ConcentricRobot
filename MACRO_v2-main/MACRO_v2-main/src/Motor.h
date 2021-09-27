/* 
    Motor.h
 */

#ifndef MOTOR_H
#define MOTOR_H


#include <Arduino.h>

class Motor
{

private:
    // Control Pins
    uint8_t enablePin;
    uint8_t in1;
    uint8_t in2;

    // const
    uint16_t maxSpeed = 255; // analog value of max speed

    // Motor Properties
    uint8_t maxVolts = 12;          // full voltage motor runs at
    double for_deadzone = 0.0;
    double rev_deadzone = 0.0;
    bool reverse = false;

public:

    // constructor
    Motor(uint8_t enablePin, uint8_t in1, uint8_t in2, bool reverse = false);

    // sets all the pinModes to be run in setup 
    void Init();

    // drive set speed with negative being reverse
    void drive(double speed);

    // Stops the motor
    void stop();

    // sets deadband values where motor is stopped
    // TIP: when choosing values, give a little wiggle room so there is some extra space motor is stopped 
    void setDeadzones(double for_deadzone, double rev_deadzone);

    // set the new max speed in terms of analog value 
    // TODO: get max in pid motor
    void setMaxSpeed(uint16_t max);
};

#endif // MOTOR_H