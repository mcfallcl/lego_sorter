#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include "Arduino.h"

// Header only class to inline the method calls
class Motor
{
public:
    Motor(int en_pin, int dir_pin, int pul_pin)
    {
        if (en_pin < 1 || en_pin > 53) {
            // do something
        }
        if (dir_pin < 1 || dir_pin > 53) {
            // do something
        }
        if (pulse_pin < 1 || pulse_pin > 53) {
            // do something
        }
        enable_pin = en_pin;
        direction_pin = dir_pin;
        pulse_pin = pul_pin;
    }

    ~Motor() { }

    // period is in microseconds
    void set_pulse_period(int period)
    {
        if (period > 0) {
            time_between_steps = period;
        }
    }
    int get_pulse_period()
    {
        return time_between_steps;
    }

private:
    int time_between_steps; // microseconds
    int enable_pin;
    int direction_pin;
    int pulse_pin;
};

#endif //_MOTOR_HPP