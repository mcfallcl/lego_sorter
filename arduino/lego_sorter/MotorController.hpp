#ifndef _MOTOR_CON_H
#define _MOTOR_CON_H

#include "Motor.hpp"

template <std::size_t N>
class MotorController
{
public:
    MotorController();
    ~MotorController() { }

    void registerMotor(Motor);
    int cycle();
private:
    std::array<Motor, N> motors;
};

#endif //_MOTOR_CON_H