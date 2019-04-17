#include <iostream>
#include <string>
#include <thread>

#include "opencv/cv.hpp"
#include "opencv2/dnn.hpp"

#include "arduino_control.hpp"
#include "udp_reciever.hpp"

int main()
{
    ArduinoController arduino_controller;

    // TODO test that works asynchonoously
    // start udp socket to listen for gui command
    std::cout << "Starting UDP listener" << std::endl;
    boost::asio::io_service io_service;
    UDP_Receiver udp_receiver(io_service, arduino_controller, 5008);
    std::thread udp_thread{[&io_service](){io_service.run();}};

    bool init_success = arduino_controller.initialize();
    if (!init_success) {
        std::cerr << "Failed to connect to arduino" << std::endl;
        // TEMP remove below comment when arduino is connected
        return 1;
    }

    // Begin while loop, waiting for exit code

    bool exit = false;
    std::string input;

    std::cout << "Q: con1 speed up\nZ: con1 speed down\nA: con1 stop\n" <<
            "W: con2 speed up\nX: con2 speed down\nS: con2 stop\n" <<
            "Any number sends bin number to sorter" << std::endl;

    while(!exit) {
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            exit = true;
            break;
        } else {
            bool success = arduino_controller.send_command(input);
        }
    }

    std::cout << "Finished Sucessfully" << std::endl;
    return 0;
}
