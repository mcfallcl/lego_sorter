#include <iostream>
#include <string>

#include "opencv/cv.hpp"

#include "arduino_control.hpp"
#include "udp_reciever.hpp"

int main()
{
    ArduinoController arduino_controller;
    bool init_success = arduino_controller.initialize();
    if (!init_success) {
        std::cerr << "Failed to connect to arduino" << std::endl;
        return 1;
    }

    // start udp socket to listen for gui command
    try {
        boost::asio::io_service io_service;
        UDP_Receiver udp_receiver(io_service, arduino_controller, 5008);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // Begin while loop, waiting for exit code

    //bool exit = false;
    //std::string input;

    //std::cout << "Q: con1 speed up\nZ: con1 speed down\nA: con1 stop\n" <<
    //        "W: con2 speed up\nX: con2 speed down\nS: con2 stop\n" <<
    //        "Any number sends bin number to sorter" << std::endl;

    //while(!exit) {
    //    std::getline(std::cin, input);

    //    if (input == "exit" || input == "quit") {
    //        exit = true;
    //        break;
    //    } else {
    //        bool success = arduino_controller.send_command(input);
    //    }
    //}

    return 0;
}
