#include "Sorter.hpp"

void Sorter::set_bin(int bin_num)
{
    bin_num = bin_num % 16;
    current_bin = bin_num;
    int new_motor_pos;
    switch (bin_num) {
        case 1:
            new_motor_pos = 14;
            break;
        case 2:
            new_motor_pos = 25;
            break;
        case 3:
            new_motor_pos = 36;
            break;
        case 4:
            new_motor_pos = 64;
            break;
        case 5:
            new_motor_pos = 75;
            break;
        case 6:
            new_motor_pos = 86;
            break;
    }
    int cur_motor_pos = motor.get_step_number();
    int num_steps = new_motor_pos - cur_motor_pos;

    if (num_steps < 0) {
        num_steps = -num_steps;
        if (num_steps > 100) {
            motor.set_num_steps_cw(200 - num_steps);
        } else {
            motor.set_num_steps_couter_cw(num_steps);
        }
    } else if (num_steps > 100) {
        motor.set_num_steps_couter_cw(200 - num_steps);
    } else {
        motor.set_num_steps_cw(num_steps);
    }
}

int Sorter::get_bin()
{
    return current_bin;
}

bool Sorter::is_busy()
{
    return moving;
}

void Sorter::enable()
{
    motor.enable();
}

void Sorter::disable()
{
    motor.disable();
}

bool Sorter::is_enabled()
{
    return motor.is_enabled();
}

void Sorter::go_home()
{
    int step = motor.get_step_number();
    if (step > 200) {
        motor.set_num_steps_cw(200 - step);
    } else {
        motor.set_num_steps_couter_cw(-step);
    }
}

void Sorter::find_home()
{
    motor.reset_step_number();
}