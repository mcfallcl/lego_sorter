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
    // i2c responses
    const uint8_t NACK = 0x00;
}

uint8_t handle_i2c(uint8_t in)
{
    uint8_t out = NACK;
}