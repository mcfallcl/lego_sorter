#include <iostream>

#include "arduino_control.hpp"

namespace {
    const uint8_t I2C_ADDR = 0x55;
}

ArduinoController::ArduinoController() :
    i2c_control(I2C_ADDR),
    slow_conveyor(i2c_control, 0),
    fast_conveyor(i2c_control, 1),
    hopper(i2c_control, 2),
    sorter(i2c_control)
{

}

bool ArduinoController::initialize()
{
    return i2c_control.initialize();
}

bool ArduinoController::send_command(std::string &command)
{
    if (command.length() != 6) return false;
    std::string unit = command.substr(0, 4);
    std::string val = command.substr(4, 5);

    if (val == "en") {
        if (unit == "slow") {
            return slow_conveyor.enable();
        } else if (unit == "fast") {
            return fast_conveyor.enable();
        } else if (unit == "hopp") {
            return hopper.enable();
        } else if (unit == "sort") {
            return sorter.enable();
        } else {
            return false;
        }
    } else if (val == "ds") {
        if (unit == "slow") {
            return slow_conveyor.disable();
        } else if (unit == "fast") {
            return fast_conveyor.disable();
        } else if (unit == "hopp") {
            return hopper.disable();
        } else if (unit == "sort") {
            return sorter.disable();
        } else {
            return false;
        }
    } else {
        int speed_or_bin;
        try{
            speed_or_bin = std::stoi(val);
        } catch (...) {
            return false;
        }

        if (unit == "slow") {
            return slow_conveyor.set_speed(speed_or_bin);
        } else if (unit == "fast") {
            return fast_conveyor.set_speed(speed_or_bin);
        } else if (unit == "hopp") {
            return hopper.set_speed(speed_or_bin);
        } else if (unit == "sort") {
            return sorter.move_to_bin(speed_or_bin);
        } else {
            return false;
        }
    }


    return true;
}
