#ifndef __I2C_HPP
#define __I2C_HPP

#include <cstdint>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

class I2cController
{
public:
    I2cController(uint8_t addr) : dest_address(addr) { }
    ~I2cController();

    bool send_command(uint8_t command);
    uint8_t read_last_response();
    bool initialize();
private:
    bool connected=false;
    uint8_t dest_address;
    uint8_t last_response;
    int i2c_file_handle;
};

#endif //__I2C_HPP