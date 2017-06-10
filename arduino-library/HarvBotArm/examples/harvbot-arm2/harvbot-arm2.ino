#include <HarvbotArm.h>
#include <HarvbotArm2.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmAFMotorScrewNode.h>
#include <HarvbotArmProtocol.h>
#include <HarvbotArmSerialProtocol.h>

HarvbotArm2* manipulator;
HarvbotArmProtocol* protocol;

void setup() 
{
  Serial.begin(9600);

  HarvbotArmServoNodePins bedplate;
  bedplate.Pin = 22;
  bedplate.InitialPos = 90;

  HarvbotArmServoNodePins shoulder;
  shoulder.Pin = 23;
  shoulder.InitialPos = 150; 

  HarvbotArmServoNodePins elbow;
  elbow.Pin = 24;
  elbow.InitialPos = 60;

  HarvbotArmAFMotorScrewNode* claw = new HarvbotArmAFMotorScrewNode(HARVBOT_ARM_CLAW_NODE, 2, 0, 200, HARVBOT_ARM_CLAW_MAX_FULL_ROTATION);
  claw->setSpeed(50);
  
  manipulator = new HarvbotArm2(bedplate, shoulder, elbow, claw);
  protocol = new HarvbotArmSerialProtocol(manipulator);
}

void loop() 
{
  protocol->run();
}
