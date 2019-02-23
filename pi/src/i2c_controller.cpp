#include "i2c_controller.hpp"

const char *i2c_filename = "/dev/i2c-1";

I2cController::~I2cController()
{
    close(i2c_file_handle);
}

bool I2cController::initialize()
{
    // if connected, return true without attempting to reopen file.
    if (connected) {
        std::cerr << "Already connected." << std::endl;
        return true;
    }

    // Attempt to open i2c handle, return false if fails
    i2c_file_handle = open(i2c_filename, O_RDWR);
    if (i2c_file_handle < 0) {
        std::cerr << "Failed to open " << i2c_filename << ". Error Code: " <<
                     i2c_file_handle << std::endl;

        return false;
    }

    // Attempt to connect to slave, return false if fails
    int ioctl_code = ioctl(i2c_file_handle, I2C_SLAVE, dest_address);
    if (ioctl_code < 0) {
        std::cerr << "Failed to connect to Adruino. Error Code: " <<
                     ioctl_code << std::endl;

        return false;
    }

    connected = true;
    // Sucess
    return true;
}

uint8_t I2cController::send_command(uint8_t command)
{
    if (!connected) {
        std::cerr << "I2C not connected. Call initialize method." << std::endl;
        return I2cResponse::NACK;
    }
    // Write command to i2c slave, always size 1
    int result = write(i2c_file_handle, &command, 1);
    if (result != 1) {
        std::cerr << "Failed to send data to arduino. Result: " <<
                     result << std::endl;

        return I2cResponse::NACK;
    }

    // Read response, always size 1
    result = read(i2c_file_handle, &last_response, 1);
    if (result != 1) {
        if (result > 1) {
            std::cerr << "Read too many bytes, response may be innacurate" <<
                        std::endl;
        } else {
            std::cerr << "Failed to read i2c response." << std::endl;

            return I2cResponse::NACK;
        }
    }

    return last_response;
}

uint8_t I2cController::read_last_response()
{
    return last_response;
}