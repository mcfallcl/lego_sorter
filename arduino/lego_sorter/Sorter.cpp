#include "Sorter.hpp"

void Sorter::set_bin(int bin_num)
{
    current_bin = bin_num;
    // Implement, this is going to be a bear
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