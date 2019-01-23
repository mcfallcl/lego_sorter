#include <Wire.h>

#include "MotorController.hpp"
#include "Conveyor.hpp"
#include "Hopper.hpp"

const byte i2c_slave_addr = 0x55;
uint8_t i2c_reg_addr = 0;
uint8_t i2c_response = 0;

MotorController<3> mc;

Conveyor conveyor1(mc.createMotor(9, 10, 11));
Conveyor conveyor2(mc.createMotor(12, 13, 14));
Hopper hopper(mc.createMotor(15, 16, 17));

void setup()
{
    //Serial.begin(9600);

    Wire.begin(i2c_slave_addr);
    Wire.setClock(50000L);
    Wire.onReceive(i2c_recv_int);
    Wire.onRequest(i2c_respond);
}

void loop()
{
    mc.cycle();
}

void i2c_recv_int(int x)
{
    i2c_reg_addr = Wire.read();
    // Do things based on addr
    // make sure to set i2c_response
}

void i2c_respond()
{
    Wire.write(i2c_response);
}

namespace
{
    /*************************** i2c responses **************************/
    const uint8_t ACK = 0x11;
    const uint8_t NACK = 0xAA;

    // STATUS requests
    const uint8_t OFF = 0x00;
    const uint8_t ON = 0x80;
    const uint8_t ERR_IND = 0x40;
    const uint8_t ERR_CODE_MASK = 0x3F;

    /************************** unit identifiers ************************/
    const uint8_t UNIT_MASK = 0xE0;
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
    // for CON1, CON2, and HOPP
    const uint8_t SPEED_MASK = 0x1F;

    // for SORT
    const uint8_t BIN_MASK = 0x1F;
}

uint8_t handle_i2c(uint8_t in)
{
    uint8_t out = NACK;

    uint8_t unit = in & UNIT_MASK;
    bool motor_flag = (in & MOTOR_MASK) == MOTOR_MASK;
    bool get_status_flag = (in & STATUS_REQ) == STATUS_REQ;
    if (motor_flag) {
        if (get_status_flag) {
            // switch statement to get motor status
        } else {
            // switch statement to set motor speed or sort position
        }
    } else {
        if (get_status_flag) {
            // switch statement to get status from system
        } else {
            // switch statement to turn on or off system
        }
    }

    return out;
}