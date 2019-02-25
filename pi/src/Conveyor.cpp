#include "Conveyor.hpp"

bool ConveyorController::set_speed(uint8_t new_speed)
{
    if (!i2c_controller.is_connected()) {
        // can't set speed if not connected
        return false;
    }
    if (new_speed >= 0x1F) {
        // speed will be outside of range.
        return false;
    }

    uint8_t data = (component_id << 5) | 0x80 | new_speed;
    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        current_speed = new_speed;
        return true;
    } else {
        return false;
    }
}

uint8_t ConveyorController::get_speed()
{
    return current_speed;
}

bool ConveyorController::enable()
{
    if (!i2c_controller.is_connected()) {
        // can't set enable if not connected
        return false;
    }

    uint8_t data = (component_id << 5) | I2cCommand::SET_ON;

    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        enabled = true;
        return true;
    } else {
        return false;
    }
}

bool ConveyorController::disable()
{
    if (!i2c_controller.is_connected()) {
        // can't set disable if not connected
        return false;
    }

    uint8_t data = (component_id << 5) | I2cCommand::SET_OFF;

    uint8_t response = i2c_controller.send_command(data);
    if (response == I2cResponse::ACK) {
        enabled = false;
        return true;
    } else {
        return false;
    }
}

bool ConveyorController::is_enabled()
{
    return enabled;
}
