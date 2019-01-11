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
        for (int i = 0; i < N; i++) {
            motors[i] = Motor(0, 0, 0);
        }
    }
    ~MotorController() { }

    void registerMotor(&Motor motor)
    {
        if (motor_count < N) {
            motors[motor_count] = motor;
            next_pulse[motor_count] = micros() + motor.get_step_period();
            motor_count += 1;
        }
    }

    int cycle()
    {
        int delay_time = -1;
        for (int i = 0; i < motor_count; i++) {
            Motor m = motors[i];
            if (!m.is_enabled()) {
                continue;
            }
            int cur_time = micros();
            if (next_pulse > cur_time) {
                continue;
            }

            m.step();
            // Should this always incriment by equal amounts? This way may create some lag
            next_pulse[i] = cur_time + m.get_step_period();
        }
        return 0;
    }
private:
    &Motor motors[N];
    int next_pulse[N];
    int motor_count;
};

#endif //_MOTOR_CON_H
