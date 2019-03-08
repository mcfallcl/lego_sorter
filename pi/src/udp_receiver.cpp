#include "udp_reciever.hpp"

using boost::asio::ip::udp;

UDP_Receiver::UDP_Receiver(boost::asio::io_service &io_context, ArduinoController &arduino_controller, int port)
        : sock(io_context, udp::endpoint(udp::v4(), port)),
          arduino_controller(arduino_controller)
{
    start();
}

void UDP_Receiver::start()
{
    sock.async_receive_from(
        boost::asio::buffer(recv_buffer), remote_endpoint,
        boost::bind(&UDP_Receiver::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void UDP_Receiver::handle_receive(const boost::system::error_code &error, std::size_t num_recv)
{
    if (!error || error == boost::asio::error::message_size) {
        // Only work if num_recv is correct, otherwise do nothing
        if (num_recv == 6) {
            std::string command(recv_buffer.begin(), recv_buffer.end());
        }

        // Get ready for next message
        start();
    }
}