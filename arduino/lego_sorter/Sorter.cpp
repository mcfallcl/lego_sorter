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