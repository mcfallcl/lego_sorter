#include "Conveyor.hpp"

void Conveyor::set_speed(int new_speed)
{
    speed = new_speed;

    // implement
}

int Conveyor::get_speed()
{
    return speed;
}

void Conveyor::enable()
{
    motor.enable();
}

void Conveyor::disable()
{
    motor.disable();
}

bool Conveyor::is_enabled()
{
    return motor.is_enabled();
}