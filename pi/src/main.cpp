#include <iostream>
#include <string>

#include "opencv/cv.hpp"
#include "Sorter.hpp"
#include "Conveyor.hpp"
#include "i2c_controller.hpp"


int main()
{
    I2cController i2c_control(0x55);
    bool i2c_good = i2c_control.initialize();

    if (i2c_good) {
	std::cout << "I2C Connection Good" << std::endl;
    } else {
	std::cout << "failed to connect to arduino" << std::endl;
	return 1;
    }

    SorterController sorter(i2c_control);
    ConveyorController slow_conveyor(i2c_control, 0);
    ConveyorController fast_conveyor(i2c_control, 1);
    ConveyorController hopper(i2c_control, 2);

    slow_conveyor.enable();
    fast_conveyor.enable();
    sorter.enable();
    sorter.move_to_bin(0);

    // Startup udp socket for gui

    // Begin while loop, waiting for exit code

    bool exit = false;
    std::string input;

    std::cout << "Q: con1 speed up\nZ: con1 speed down\nA: con1 stop\n" <<
            "W: con2 speed up\nX: con2 speed down\nS: con2 stop\n" <<
            "Any number sends bin number to sorter" << std::endl;

    while(!exit) {
        std::getline(std::cin, input);

        if (input.compare("e") == 0) {
            exit = true;
            break;
        } else if (input.compare("q") == 0) {
            slow_conveyor.set_speed(slow_conveyor.get_speed() + 1);
        } else if (input.compare("z") == 0) {
            slow_conveyor.set_speed(slow_conveyor.get_speed() - 1);
        } else if (input.compare("a") == 0) {
            slow_conveyor.set_speed(0);
        } else if (input.compare("w") == 0) {
            fast_conveyor.set_speed(fast_conveyor.get_speed() + 1);
        } else if (input.compare("x") == 0) {
            fast_conveyor.set_speed(fast_conveyor.get_speed() - 1);
        } else if (input.compare("s") == 0) {
            fast_conveyor.set_speed(0);
        } else if (input.compare("0") == 0) {
            sorter.move_to_bin(0);
        } else if (input.compare("1") == 0) {
            sorter.move_to_bin(1);
        } else if (input.compare("2") == 0) {
            sorter.move_to_bin(2);
        } else if (input.compare("3") == 0) {
            sorter.move_to_bin(3);
        } else if (input.compare("4") == 0) {
            sorter.move_to_bin(4);
        } else if (input.compare("5") == 0) {
            sorter.move_to_bin(5);
        } else if (input.compare("6") == 0) {
            sorter.move_to_bin(6);
        } else if (input.compare("7") == 0) {
            sorter.move_to_bin(7);
        } else if (input.compare("8") == 0) {
            sorter.move_to_bin(8);
        } else if (input.compare("9") == 0) {
            sorter.move_to_bin(9);
        } else if (input.compare("10") == 0) {
            sorter.move_to_bin(10);
        } else if (input.compare("11") == 0) {
            sorter.move_to_bin(11);
        } else if (input.compare("12") == 0) {
            sorter.move_to_bin(12);
        } else if (input.compare("13") == 0) {
            sorter.move_to_bin(13);
        } else if (input.compare("14") == 0) {
            sorter.move_to_bin(14);
        } else if (input.compare("15") == 0) {
            sorter.move_to_bin(15);
        } else {
            // do nothing
            continue;
        }
        std::cout << "Received: " << (int)i2c_control.read_last_response() << std::endl;
    }

    return 0;
}
