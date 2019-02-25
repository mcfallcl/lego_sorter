#include "Sorter.hpp"

SorterController::SorterController(I2cController &i2c, uint8_t component_id) :
        i2c_controller(i2c)
{
    if (component_id > 3) {
        component_id = 3;
    }
    this->component_id = component_id;

    if (i2c_controller.is_connected()) {
        bool home_success = move_to_bin(0);
        if (!home_success) {
            current_bin = 0xFF;
        }
    }
}

bool SorterController::enable()
{
    if (!i2c_controller.is_connected()) {
        // can't set enable if not connected
        return false;
    }

    uint8_t data = (component_id << 5) & I2cCommand::SET_ON;

    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        enabled = true;
        return true;
    } else {
        return false;
    }
}

bool SorterController::disable()
{
    if (!i2c_controller.is_connected()) {
        // can't set disable if not connected
        return false;
    }

    uint8_t data = (component_id << 5) & I2cCommand::SET_OFF;

    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        enabled = false;
        return true;
    } else {
        return false;
    }
}

bool SorterController::move_to_bin(uint8_t bin)
{
    if (!i2c_controller.is_connected()) {
        // can't set disable if not connected
        return false;
    }

    if (bin > 30) {
        // Only 0-30 are supported
        return false;
    }

    uint8_t data = 0x80 & (component_id << 5) & bin;
    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        current_bin = bin;
        return true;
    } else {
        // Arduino failed to acknowledge command.
        return false;
    }
}

bool SorterController::is_enabled()
{
    return enabled;
}

uint8_t SorterController::get_current_bin()
{
    return current_bin;
}