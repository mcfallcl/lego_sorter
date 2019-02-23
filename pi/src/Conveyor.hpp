#ifndef __CONVEYOR_HPP
#define __CONVEYOR_HPP

#include "i2c_controller.hpp"

class ConveyorController
{
public:
    ConveyorController(I2cController &i2c, uint8_t component_id) :
        i2c_controller(i2c),
        component_id(component_id) { }
    ~ConveyorController() { }

    // Access arduino through i2c, returns if successful
    bool set_speed(uint8_t new_speed);
    bool enable();
    bool disable();

    // Returns data stored on pi
    uint8_t get_speed();
    bool is_enabled();
private:
    I2cController &i2c_controller;
    uint8_t component_id;
    uint8_t current_speed=0;
    bool enabled=false;
};

#endif //__CONVEYOR_HPP