#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArm1.h>

HarvbotArm1* manipulator;
bool signal;
void setup() 
{
  manipulator = new HarvbotArm1();
  signal=false;
}

void loop() {

  if(!signal)
  {
    manipulator->getBedplate()->write(180);
    delay(25); 
    manipulator->getShoulder()->write(90);
    delay(25); 
    manipulator->getElbow()->write(80);
    delay(25); 
    manipulator->getElbowScrew()->write(180);
    delay(25); 
    manipulator->getHand()->write(180);
    delay(25); 
    manipulator->getHandScrew()->write(180);
  }
  else
  {
    manipulator->getBedplate()->write(0);
    delay(25); 
    manipulator->getShoulder()->write(45);
    delay(25); 
    manipulator->getElbow()->write(0);
    delay(25); 
    manipulator->getElbowScrew()->write(0);
    delay(25); 
    manipulator->getHand()->write(180);
    delay(25); 
    manipulator->getHandScrew()->write(30);
  }

  signal = !signal;

  delay(5000); 
}
