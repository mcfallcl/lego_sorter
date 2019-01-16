#include "Hopper.hpp"

void Hopper::set_speed(int new_speed)
{
    speed = new_speed > 0 ? new_speed : 0;
    // implement
}

int Hopper::get_speed()
{
    return speed;
}

void Hopper::enable()
{
    motor.enable();
}

void Hopper::disable()
{
    motor.disable();
}