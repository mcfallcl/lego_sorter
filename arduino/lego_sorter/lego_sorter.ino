#include <Wire.h>

#include "MotorController.hpp"
#include "Conveyor.hpp"
#include "Hopper.hpp"
#include "Sorter.hpp"

const byte i2c_slave_addr = 0x55;
uint8_t i2c_reg_addr = 0;
uint8_t i2c_response = 0;
int bin = 0;

MotorController<4> mc;

unsigned long t;
unsigned long next_t;

Conveyor conveyor1(mc.createMotor(9, 10, 11));
Conveyor conveyor2(mc.createMotor(48, 50, 52));
Hopper hopper(mc.createMotor(0,0,0));
Sorter sorter(mc.createMotor(40, 42, 44, false));

int ctr = 1;

bool cw = true;

void setup()
{
    Wire.begin(i2c_slave_addr);
    Wire.setClock(50000L);
    Wire.onReceive(i2c_recv_int);
    Wire.onRequest(i2c_respond);

    t = millis();
    next_t = t + 5000;

    conveyor1.enable();
    conveyor1.set_speed(0);
    conveyor2.enable();
    conveyor2.set_speed(0);
    sorter.enable();
    sorter.find_home();
}

void loop()
{
    mc.cycle();
}

void i2c_recv_int(int x)
{
    i2c_reg_addr = Wire.read();
    i2c_response = handle_i2c(i2c_reg_addr);
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
    const uint8_t BUSY = 0x40;
    const uint8_t ERR_IND = 0x20;
    const uint8_t ERR_CODE_MASK = 0x1F;

    /************************** unit identifiers ************************/
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

uint8_t handle_i2c(uint8_t in)
{
    uint8_t out = NACK;

    uint8_t unit = in & UNIT_MASK;
    bool motor_flag = (in & MOTOR_MASK) == MOTOR_MASK;
    bool get_status_flag = (in & STATUS_REQ) == STATUS_REQ;
    if (motor_flag) {
        uint8_t bin_or_speed = in & BIN_OR_SPEED_MASK;
        if (bin_or_speed == BIN_OR_SPEED_MASK) {
            out = (unit == CON1) ? conveyor1.get_speed() :
                  (unit == CON2) ? conveyor2.get_speed() :
                  (unit == HOPP) ? hopper.get_speed() :
                  (unit == SORT) ? sorter.get_bin() : NACK;
        } else {
            switch (unit) {
                case CON1:
                    conveyor1.set_speed(bin_or_speed);
                    out = ACK;
                    break;
                case CON2:
                    conveyor2.set_speed(bin_or_speed);
                    out = ACK;
                    break;
                case HOPP:
                    hopper.set_speed(bin_or_speed);
                    out = ACK;
                    break;
                case SORT:
                    sorter.set_bin(bin_or_speed);
                    out = ACK;
                    break;
                default:
                    out = NACK;
                    break;
            }
        }
    } else {
        if (get_status_flag) {
            switch (unit) {
                case CON1:
                    if (conveyor1.is_enabled()) {
                        out = ON;
                    } else {
                        out = OFF;
                    }
                    break;
                case CON2:
                    if (conveyor2.is_enabled()) {
                        out = ON;
                    } else {
                        out = OFF;
                    }
                    break;
                case HOPP:
                    if (hopper.is_enabled()) {
                        out = ON;
                    } else {
                        out = OFF;
                    }
                    break;
                case SORT:
                    if (sorter.is_enabled()) {
                        if (sorter.is_busy()) {
                            out = BUSY;
                        } else {
                            out = ON;
                        }
                    } else {
                        out = OFF;
                    }
                    break;
                default:
                    out = NACK;
                    break;
            }
        } else {
            if ((0x0F & in) == 0x01) {
                switch (unit) {
                    case CON1:
                        conveyor1.enable();
                        out = ACK;
                        break;
                    case CON2:
                        conveyor2.enable();
                        out = ACK;
                        break;
                    case HOPP:
                        hopper.enable();
                        out = ACK;
                        break;
                    case SORT:
                        sorter.enable();
                        out = ACK;
                        break;
                    default:
                        out = NACK;
                        break;
                }
            } else if ((0x0F & in) == 0x00) {
                switch (unit) {
                    case CON1:
                        conveyor1.disable();
                        out = ACK;
                        break;
                    case CON2:
                        conveyor2.disable();
                        out = ACK;
                        break;
                    case HOPP:
                        hopper.disable();
                        out = ACK;
                        break;
                    case SORT:
                        sorter.disable();
                        out = ACK;
                        break;
                    default:
                        out = NACK;
                        break;
                }
            }
        }
    }

    return out;
}
