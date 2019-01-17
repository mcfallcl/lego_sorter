#ifndef _SORTER_HPP
#define _SORTER_HPP

#include "Motor.hpp"

class Sorter
{
public:
    Sorter(Motor &m) : motor(m), current_bin(0), moving(false) { }
    ~Sorter() { }

    void set_bin(int bin_num);
    int get_bin();
    bool is_busy();
    void enable();
    void disable();
    bool is_enabled();
private:
    Motor &motor;
    int current_bin;
    bool moving;
};

#endif //_SORTER_HPP
