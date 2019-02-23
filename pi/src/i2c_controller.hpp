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

namespace I2cResponse
{
    const uint8_t ACK = 0x11;
    const uint8_t NACK = 0xAA;

    // STATUS requests
    const uint8_t OFF = 0x00;
    const uint8_t ON = 0x80;
    const uint8_t BUSY = 0x40;
    const uint8_t ERR_IND = 0x20;
    const uint8_t ERR_CODE_MASK = 0x1F;
}

namespace I2cCommand
{
    const uint8_t UNIT_MASK = 0x60;
    const uint8_t MOTOR_MASK = 0x80;
    const uint8_t CON1 = 0x00;
    const uint8_t CON2 = 0x20;
    const uint8_t HOPP = 0x40;
    const uint8_t SORT = 0x60;

    // command codes MOTOR_FLAG = 0
    const uint8_t SET_OFF = 0x00;
    const uint8_t SET_ON = 0x01;
    const uint8_t STATUS_REQ = 0x10;

    // command codes MOTOR_FLAG = 1
    const uint8_t BIN_OR_SPEED_MASK = 0x1F;
}

class I2cController
{
public:
    I2cController(uint8_t addr) : dest_address(addr) { }
    ~I2cController();

    uint8_t send_command(uint8_t command);
    uint8_t read_last_response();
    bool initialize();
    bool is_connected()
    {
        return connected;
    }
private:
    bool connected=false;
    uint8_t dest_address;
    uint8_t last_response;
    int i2c_file_handle;
};

#endif //__I2C_HPP