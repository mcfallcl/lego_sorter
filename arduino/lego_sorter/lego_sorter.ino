#include "Motor.hpp"
#include "MotorController.hpp"

MotorController<3> mc;

void setup()
{
  //Serial.begin(9600);

  Motor *m1 = mc.createMotor(9, 10, 11);

  m1->set_cycle_period(500);
  m1->enable();
}

void loop()
{
  mc.cycle();
}
