#ifndef _CONVEYOR_HPP
#define _CONVEYOR_HPP

#include "Arduino.h"
#include "Motor.hpp"

class Conveyor
{
public:
    Conveyor(Motor &m);
    ~Conveyor() { }

    void set_speed(int new_speed);
    int get_speed();
private:
    Motor &motor;
    int speed;
};

#endif //_CONVEYOR_HPP
