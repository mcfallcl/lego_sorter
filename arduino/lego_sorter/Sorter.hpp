#ifndef _SORTER_HPP
#define _SORTER_HPP

#include "Motor.hpp"

class Sorter
{
public:
    Sorter(Motor &m);
    ~Sorter() { }

    void set_bin(int bin_num);
    int get_bin();
    bool is_busy();
private:
    Motor &motor;
    int current_bin;
    bool moving;
};

#endif //_SORTER_HPP
