/*
    Stage.h
*/
#ifndef STAGE_H
#define STAGE_H

#include "Arduino.h"
#include "PIDMotor.h"
#include "Joystick.h"

class Stage
{
private:
    // Parameters
    
    // Objects
    PIDMotor* transMotor;
    PIDMotor* rotMotor; 
    Joystick* js;

    char txt[50];
public:
    Stage(PIDMotor* trans, PIDMotor* rot, Joystick* js);

    // initialize all pins for joystick and motors
    void Init();

    // run pid on all motors
    void calculatePID();

    // use joystick to drive motors
    void manualDrive();
    
    // set setpoint as home position
    void goHome();

    // ---------- Cascaded Functions
    // set current position as home posistion for PID motors
    void setHomePosition();

    // pid setpoints for both motors
    void setSetpoints(double transSP, double rotSP);

    // checks if both setpoints have been reached
    bool setpointReached();

    // ------------ Prints
    void printJoystick();
    void printPos();
    void printPID();
    
};

#endif