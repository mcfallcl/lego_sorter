#include <iostream>
#include <string>

#include "opencv/cv.hpp"
#include "Sorter.hpp"
#include "Conveyor.hpp"
#include "i2c_controller.hpp"


int main()
{
    I2cController i2c_control(0x55);
    i2c_control.initialize();

    SorterController sorter(i2c_control);
    ConveyorController slow_conveyor(i2c_control, 0);
    ConveyorController fast_conveyor(i2c_control, 1);
    ConveyorController hopper(i2c_control, 2);

    // Startup udp socket for gui

    // Begin while loop, waiting for exit code

    bool exit = false;
    std::string input;

    std::cout << "Q: con1 speed up\nZ: con1 speed down\nA: con1 stop\n" <<
            "W: con2 speed up\nX: con2 speed down\nS: con2 stop\n" <<
            "Any number sends bin number to sorter" << std::endl;

    while(!exit) {
        std::cin >> input;
        if (input.compare("e") == 0) {
            exit = true;
        } else if (input.compare("q")) {
            slow_conveyor.set_speed(slow_conveyor.get_speed() + 1);
        } else if (input.compare("z")) {
            slow_conveyor.set_speed(slow_conveyor.get_speed() - 1);
        } else if (input.compare("a")) {
            slow_conveyor.set_speed(0);
        } else if (input.compare("w")) {
            fast_conveyor.set_speed(fast_conveyor.get_speed() + 1);
        } else if (input.compare("x")) {
            fast_conveyor.set_speed(fast_conveyor.get_speed() - 1);
        } else if (input.compare("s")) {
            fast_conveyor.set_speed(0);
        } else if (input.compare("0")) {
            sorter.move_to_bin(0);
        } else if (input.compare("1")) {
            sorter.move_to_bin(1);
        } else if (input.compare("2")) {
            sorter.move_to_bin(2);
        } else if (input.compare("3")) {
            sorter.move_to_bin(3);
        } else if (input.compare("4")) {
            sorter.move_to_bin(4);
        } else if (input.compare("5")) {
            sorter.move_to_bin(5);
        } else if (input.compare("6")) {
            sorter.move_to_bin(6);
        } else if (input.compare("7")) {
            sorter.move_to_bin(7);
        } else if (input.compare("8")) {
            sorter.move_to_bin(8);
        } else if (input.compare("9")) {
            sorter.move_to_bin(9);
        } else {
            // do nothing
            continue;
        }
    }

    return 0;
}
