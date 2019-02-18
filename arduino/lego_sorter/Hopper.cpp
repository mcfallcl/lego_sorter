#include "Hopper.hpp"

void Hopper::set_speed(int new_speed)
{
    if (new_speed < 0 || new_speed > 30) return;
    speed = new_speed;

    int step_period = (new_speed == 0) ? 0 : 5000 - 150 * (30 - new_speed);
    motor.set_cycle_period(step_period);
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

bool Hopper::is_enabled()
{
    return motor.is_enabled();
}