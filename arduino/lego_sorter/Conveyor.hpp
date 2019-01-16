#ifndef _CONVEYOR_HPP
#define _CONVEYOR_HPP

#include "Arduino.h"
#include "Motor.hpp"

class Conveyor
{
public:
    Conveyor(Motor &m) : motor(m), speed(0) { }
    ~Conveyor() { }

    void set_speed(int new_speed);
    int get_speed();
    void enable();
    void disable();
private:
    Motor &motor;
    int speed;
};

#endif //_CONVEYOR_HPP
