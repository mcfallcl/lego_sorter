#include "Conveyor.hpp"

void Conveyor::set_speed(int new_speed)
{
    if (new_speed < 0 || new_speed > 30) return;
    speed = new_speed;

    int step_period = (new_speed == 0) ? 0 : 5000 - 150 * new_speed;
    motor.set_cycle_period(step_period);
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
