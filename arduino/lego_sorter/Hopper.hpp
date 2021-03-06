#ifndef _HOPPER_HPP
#define _HOPPER_HPP

#include "Arduino.h"
#include "Motor.hpp"

class Hopper
{
public:
    Hopper(Motor &m) : motor(m), speed(0) { }
    ~Hopper() { }

    void set_speed(int new_speed);
    int get_speed();
    void enable();
    void disable();
    bool is_enabled();
private:
    Motor &motor;
    int speed;
};

#endif //_HOPPER_HPP
