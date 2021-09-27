#include "PIDMotor.h"

PIDMotor::PIDMotor(double kp, double ki, double kd, double ff_plus, double ff_minus, Motor *motor, Encoder* enc, uint8_t type)
{
    /* creates a PIDMotor object by receiving a motor and initializing constants*/
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->ff_plus = ff_plus;
    this->ff_minus = ff_minus;
    this->motor = motor;
    this->enc = enc;
    this->type = type;

    this->motor->setDeadzones(ff_plus, ff_minus);
}

PIDMotor::PIDMotor(Motor* motor, Encoder* enc){
    this->motor = motor;
    this->enc = enc;
}

void PIDMotor::Init(){
    this->motor->Init();
}

void PIDMotor::calculate()
{
    /* Figure out the desired acceleration for the motor and then call drive motor*/
    double now = micros()/pow(10,6);
    double time_step = now - this->last_time; //time is in micro seconds so this converts it to seconds
    
    double current_pos = this->getPos();
    this->curr_pos = current_pos;

    double curr_error = current_pos - this->setpoint;
    this->curr_error = curr_error;

    // creating integral term
    if (curr_error*sum_error >= 0 && abs(curr_error) < 5)
    { //have not crossed the setpoint
        this->sum_error += curr_error * time_step; // multiply by the dt (make sure its in terms of seconds)
    } else
    { // have crossed the setpoint so we want to reset the summation
        this->sum_error = 0;
    }

    // creating derivative term
    double change_error = (curr_error - this->last_error)/time_step;
    this->curr_vel = -change_error;
    this->last_error = curr_error;

    //Currently only using integral and proportional control
    double desired_accel = this->ki * this->sum_error + this->kp * curr_error + this->kd * change_error;

    this->runMotor(desired_accel);
    this->last_time = now;
}

void PIDMotor::runMotor(double desired_accel)
{   
    /* Drive the motor */
    double torque = desired_accel; //change if we find a dynamic model of system
    this->motor->drive(torque);
}

void PIDMotor::stop(){
    this->motor->stop();
}

bool PIDMotor::setpointReached()
{   
    // check if motor is within acceptable tolerance of setpoint
    // pc.printf("SP Reached %d\n", (abs(this->curr_error) <= this->tolerance));
    return (abs(this->curr_error) <= this->tolerance);
}

// ---------------- HELPERS ------------

double PIDMotor::ticksToMM(long ticks){
    return ticks * this->mmPerRev / (this->ticksPerRev * this->gearRatio);
}

double PIDMotor::ticksToDeg(long ticks){
    return ticks * this->degPerRev / (this->ticksPerRev * this->gearRatio);
}

// ---------------- SETTERS ------------

void PIDMotor::setConstants(double kp, double ki, double kd)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

void PIDMotor::setHomePosition(){
    this->home = this->enc->read();
}

void PIDMotor::setSetpoint(double setpoint)
{
    /* Assumes the setpoint passed in is in encoder ticks
    */
    this->setpoint = setpoint;
    this->sum_error = 0;
    this->last_error = 0;
    this->calculate();
}

// ---------------- GETTERS
double PIDMotor::getPos(){
    if (this->type == 0){
        return this->ticksToMM(this->enc->read());
    }
    else if (this->type == 1)
    {
        return this->ticksToDeg(this->enc->read());
    }
    return this->enc->read();
}

double PIDMotor::getCurrError(){
    return this->curr_error;
}

double PIDMotor::getCurrPos(){
    return this->curr_pos;
}

double PIDMotor::getCurrVel(){
    return this->curr_vel;
}

double PIDMotor::getSetpoint(){
    return this->setpoint;
}

double PIDMotor::getHome(){
    return this->home;
}