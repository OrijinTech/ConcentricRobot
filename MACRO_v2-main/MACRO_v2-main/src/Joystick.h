/*
* Joystick.h
*/

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

class Joystick
{
private:
    // pins
    uint16_t Xpin;
    uint16_t Ypin;

    // consts
    int xmid_val = 520;
    int ymid_val = 520;
    double maxAnalog = 1023;

    // vals 
    double val;
    double out;


public:
    Joystick(uint16_t Xpin, uint16_t Ypin);
    void Init();
    double readX();
    double readY();
    float mapfloat(long x, long in_min, long in_max, long out_min, long out_max);
};

#endif