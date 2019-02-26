#ifndef __ARDUINO_CONTROL_HPP
#define __ARDUINO_CONTROL_HPP

#include <string>

#include "i2c_controller.hpp"
#include "Conveyor.hpp"
#include "Sorter.hpp"

class ArduinoController{
public:
    ArduinoController();
    ~ArduinoController() { }

    bool initialize();
    bool send_command(std::string &command);
private:
    I2cController i2c_control;
    ConveyorController slow_conveyor;
    ConveyorController fast_conveyor;
    ConveyorController hopper;
    SorterController sorter;
};

#endif //__ARDUINO_CONTROL_HPP