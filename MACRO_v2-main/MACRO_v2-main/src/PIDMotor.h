/* 
    PIDMotor.h
 */

#ifndef PIDMOTOR_H
#define PIDMOTOR_H

#include "Arduino.h"
#include "Motor.h"
#include "Encoder.h"

class PIDMotor{
private:
    // PID gains
    double kp = 1;
    double ki = 0;
    double kd = 0;
    double ff_plus = 0;
    double ff_minus = 0;

    // PID vars
    double setpoint = 0;

    double curr_time = 0;
    double last_time = 0;

    double last_error = 0;
    double sum_error = 0;
    double curr_error = 0;

    double curr_pos = 0;
    double curr_vel = 0;
    double tolerance = 50; // passable error within the setpoint of ~10 um

    int home = 0;

    // Objects
    Motor* motor;
    Encoder* enc;

    // Consts
    double ticksPerRev = 464.64;
    double gearRatio = 20;
    double mmPerRev = 2.54;
    double degPerRev = 360;

    // Motor Type: 0 = translation, 1 = rotation
    uint8_t type;

public:
    // constructor that sets everything
    PIDMotor(double kp, double ki, double kd, double ff_plus, double ff_minus, Motor* motor, Encoder* enc, uint8_t type);

    // constructor for just motor and encoder
    PIDMotor(Motor* motor, Encoder* enc);

    // initialize motors
    void Init();

    // set the setpoint and drive motors
    void calculate();

    // set motor value directly
    void runMotor(double desired_accel);
    
    // stop all motors
    void stop();

    // check if pid is done interpolating
    bool setpointReached();


    // --------- Helpers
    // convert ticks to mm translation
    double ticksToMM(long ticks);

    // convert ticks to deg
    double ticksToDeg(long ticks);


    // ---------- Setters
    // set pid values
    void setConstants(double kp, double ki, double kd);
    
    // set initial encoder value as 0
    void setHomePosition();
    
    // change the setpoint for PID
    void setSetpoint(double setpoint);


    // ----------- Getters ------------
    // return current encoder value
    double getPos();

    // return current dist from setpoint
    double getCurrError();

    // return current position
    double getCurrPos();

    // return current velocity
    double getCurrVel();

    // return current setpoint
    double getSetpoint();

    // return home position
    double getHome();

};

#endif // PIDMOTOR_H