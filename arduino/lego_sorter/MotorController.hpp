#ifndef _MOTOR_CON_H
#define _MOTOR_CON_H

#include "Motor.hpp"

template <int N>
class MotorController
{
public:
    MotorController()
    {
        motor_count = 0;
    }
    ~MotorController() { }

    Motor &createMotor(int en_pin, int dir_pin, int pul_pin)
    {
        if (motor_count < N) {
            Motor new_motor(en_pin, dir_pin, pul_pin);
            motors[motor_count] = new_motor;
            Motor &ret = motors[motor_count];
            motor_count += 1;
            return ret;
        }
    }

    int cycle()
    {
        int delay_time = -1;
        for (int i = 0; i < motor_count; i++) {
            Motor &m = motors[i];
            if (!m.is_enabled()) {
                continue;
            }
            unsigned long cur_time = micros();
            if (next_pulse[i] > cur_time) {
                continue;
            }

            m.step();
            // Should this always incriment by equal amounts? This way may create some lag
            next_pulse[i] = cur_time + m.get_step_period();
        }
        return 0;
    }
private:
    Motor motors[N];
    unsigned long next_pulse[N];
    int motor_count;
};

#endif //_MOTOR_CON_H
