#ifndef __SORTER_HPP
#define __SORTER_HPP

#include "i2c_controller.hpp"

class SorterController
{
public:
    SorterController(I2cController &i2c, uint8_t component_id=3);
    ~SorterController() { }

    // Access i2c, returns if communication was sucessful
    bool enable();
    bool disable();
    bool move_to_bin(uint8_t bin);

    // Returns from internally stored data
    bool is_enabled();
    uint8_t get_current_bin();
private:
    I2cController &i2c_controller;
    uint8_t component_id;
    uint8_t current_bin=0;
    bool enabled=false;
};

#endif //__SORTER_HPP