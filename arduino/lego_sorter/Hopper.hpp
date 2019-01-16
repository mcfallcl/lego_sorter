#ifndef _HOPPER_HPP
#define _HOPPER_HPP

#include "Arduino.h"
#include "Motor.hpp"

class Conveyor
{
public:
    Hopper(Motor &m);
    ~Hopper() { }

    void set_speed(int new_speed);
    int get_speed();
    void enable();
    void disable();
private:
    Motor &motor;
    int speed;
};

#endif //_HOPPER_HPP
