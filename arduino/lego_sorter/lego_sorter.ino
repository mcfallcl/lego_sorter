#include "Motor.hpp"
#include "MotorController.hpp"

void setup()
{
  Motor m1(11, 12, 13);
  Motor m2(14, 15, 16);
  Motor m3(17, 18, 19);
  MotorController<3> mc;
  mc.registerMotor(m1);
  mc.registerMotor(m2);
  mc.registerMotor(m3);
}

void loop()
{

}
