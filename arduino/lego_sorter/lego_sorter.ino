#include "Motor.hpp"
#include "MotorController.hpp"

Motor m1(9, 10, 11);
MotorController<3> mc;

void setup()
{
  Serial.begin(9600);
  Serial.println((unsigned int) &m1, HEX);
  
  //Motor m2(14, 15, 16);
  //Motor m3(17, 18, 19);

  mc.registerMotor(m1);
  //mc.registerMotor(m2);
  //mc.registerMotor(m3);
  
  m1.set_cycle_period(2000);
  m1.enable();
}

void loop()
{
  mc.cycle();
}
