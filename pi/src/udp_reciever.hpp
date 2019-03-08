#ifndef __UDP_RECEIVER_HPP
#define __UDP_RECEIVER_HPP

#include <iostream>
#include <string>

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "arduino_control.hpp"

class UDP_Receiver {
public:
    UDP_Receiver(boost::asio::io_service &io_context, ArduinoController &arduino_control, int port);
private:
    void start();
    void handle_receive(const boost::system::error_code &error, std::size_t num_recv);

    boost::asio::ip::udp::socket sock;
    boost::asio::ip::udp::endpoint remote_endpoint;
    boost::array<char, 6> recv_buffer;
    ArduinoController &arduino_controller;
};


#endif //__UDP_RECEIVER_HPP