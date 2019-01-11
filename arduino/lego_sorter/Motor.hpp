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
        digitalWrite(en_pin, LOW);
        digitalWrite(dir_pin, LOW);
        digitalWrite(pulse_pin, LOW);
    }

    ~Motor() { }

    // period is in microseconds
    void set_cycle_period(int period)
    {
        if (period > 0) {
            time_between_steps = period;
        }
    }

    int get_step_period()
    {
        return time_between_steps;
    }

    void step()
    {
        digitalWrite(pulse_pin, ~digitalRead(pulse_pin));
    }

    void enable()
    {
        digitalWrite(enable_pin, HIGH);
        enabled = true;
    }

    void disable()
    {
        digitalWrite(enable_pin, LOW);
        enabled = false;
    }

    bool is_enabled()
    {
        return enabled;
    }

private:
    int time_between_steps; // microseconds
    int enable_pin;
    int direction_pin;
    int pulse_pin;
    bool enabled;
};

#endif //_MOTOR_HPP