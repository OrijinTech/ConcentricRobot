#include "Joystick.h"

Joystick::Joystick(uint16_t Xpin, uint16_t Ypin)
{
    this->Xpin = Xpin;
    this->Ypin = Ypin;
}

// Function to run in setup to initialize the input pins
void Joystick::Init(){
    pinMode(this->Xpin, INPUT);
    pinMode(this->Ypin, INPUT);
}

float Joystick::mapfloat(long x, long in_min, long in_max, long out_min, long out_max){
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

// reads x value of joystick and convert on scale of -1 to 1 with a little buffer around 0
double Joystick::readX(){
    this->val = this->mapfloat(analogRead(this->Xpin), 0, 1023, -1, 1);
    return (abs(this->val) <= .1) ? 0 : this->val;
}

// reads y value of joystick and convert on scale of -1 to 1 with a little buffer around 0
double Joystick::readY(){
    this->val = this->mapfloat(analogRead(this->Ypin), 0, 1023, -1, 1);
    return (abs(this->val) <= .1) ? 0 : this->val;
}

