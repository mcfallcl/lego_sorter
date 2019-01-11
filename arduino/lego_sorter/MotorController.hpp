#ifndef _MOTOR_CON_H
#define _MOTOR_CON_H

#include "Motor.hpp"

template <std::size_t N>
class MotorController
{
public:
    MotorController() : motor_count(0) { };
    ~MotorController() { }

    void registerMotor(Motor);
    int cycle();
private:
    std::array<Motor, N> motors;
    motor_count;
};

#endif //_MOTOR_CON_H