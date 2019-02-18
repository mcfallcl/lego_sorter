#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include "Arduino.h"

// Header only class to inline the method calls
class Motor
{
public:
    Motor(int en_pin=0, int dir_pin=0, int pul_pin=0, bool cont=true)
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
        continuous = cont;
        pinMode(enable_pin, OUTPUT);
        pinMode(direction_pin, OUTPUT);
        pinMode(pulse_pin, OUTPUT);
        cur_position = false;
        digitalWrite(en_pin, HIGH);
        digitalWrite(dir_pin, HIGH);
        digitalWrite(pulse_pin, LOW);
    }

    ~Motor() { }

    // period is in microseconds
    void set_cycle_period(int period)
    {
        if (period > 0) {
            time_between_steps = period;
        } else {
            time_between_steps = 1000000;
        }
    }

    int get_step_period()
    {
        return time_between_steps;
    }

    void step()
    {
        if (!enabled) return;

        if (continuous) {
            cur_position = !cur_position;
            if (cur_position) {
                digitalWrite(pulse_pin, HIGH);
                if (cw_direction) {
                    step_number += 1;
                } else {
                    step_number -= 1;
                }
                if (step_number >= 200) step_number = 0;
                if (step_number < 0) step_number = 200 + step_number;
            } else {
                digitalWrite(pulse_pin, LOW);
            }
        } else {
            if (num_steps > 0) {
                cur_position = !cur_position;
                if (cur_position) {
                    digitalWrite(pulse_pin, HIGH);
                    num_steps -= 1;
                    if (cw_direction) {
                        step_number += 1;
                    } else {
                        step_number -= 1;
                    }
                    if (step_number >= 200) step_number = 0;
                    if (step_number < 0) step_number = 200 + step_number;
                } else {
                    digitalWrite(pulse_pin, LOW);
                }
            }
        }
    }

    int get_step_number()
    {
        return step_number;
    }

    int step_until_step_number(int new_step_number)
    {
        num_steps = (new_step_number - step_number) % 100;
    }

    void set_continuous()
    {
        continuous = true;
    }

    void set_step_controlled()
    {
        continuous = false;
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

    void set_num_steps_cw(int n_steps)
    {
        digitalWrite(direction_pin, HIGH);
        cw_direction = true;
        num_steps = n_steps;
    }

    void set_num_steps_couter_cw(int n_steps)
    {
        digitalWrite(direction_pin, LOW);
        cw_direction = false;
        num_steps = n_steps;
    }

private:
    int time_between_steps; // microseconds
    int step_number;
    int num_steps;
    int enable_pin;
    int direction_pin;
    int pulse_pin;
    bool enabled;
    bool cur_position;
    bool cw_direction;
    bool continuous;
};

#endif //_MOTOR_HPP
