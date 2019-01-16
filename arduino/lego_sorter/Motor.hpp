#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include "Arduino.h"

// Header only class to inline the method calls
class Motor
{
public:
    Motor(int en_pin=0, int dir_pin=0, int pul_pin=0)
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
        pinMode(enable_pin, OUTPUT);
        pinMode(direction_pin, OUTPUT);
        pinMode(pulse_pin, OUTPUT);
        cur_position = false;
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
        cur_position = !cur_position;
        digitalWrite(pulse_pin, cur_position ? HIGH : LOW);
        //Serial.println(cur_position);
    }

    void enable()
    {
        digitalWrite(enable_pin, LOW);
        enabled = true;
    }

    void disable()
    {
        digitalWrite(enable_pin, HIGH);
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
    bool cur_position;
};

#endif //_MOTOR_HPP
