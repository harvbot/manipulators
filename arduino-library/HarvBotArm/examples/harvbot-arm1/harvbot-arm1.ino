#include <HarvbotArm.h>
#include <HarvbotArm1.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArmProtocol.h>
#include <HarvbotArmSerialProtocol.h>

HarvbotArm1* manipulator;
HarvbotArmProtocol* protocol;

void setup() 
{
  Serial.begin(9600);

  HarvbotArmServoNodePins bedplate;
  bedplate.Pin = 2;
  bedplate.Pin = 22;
  bedplate.InitialPos = 90;

  HarvbotArmServoNodePins shoulder;
  shoulder.Pin = 3;
  shoulder.Pin = 23;
  shoulder.InitialPos = 150; 

  HarvbotArmServoNodePins elbow;
  elbow.Pin = 4;
  elbow.Pin = 24;
  elbow.InitialPos = 60;

  HarvbotArmServoNodePins elbowScrew;
  elbowScrew.Pin = 5;
  elbowScrew.InitialPos = 90;

  HarvbotArmServoNodePins hand;
  hand.Pin = 6;
  hand.InitialPos = 90;

  HarvbotArmServoNodePins handScrew;
  handScrew.Pin = 7;
  handScrew.InitialPos = 90;
  
  manipulator = new HarvbotArm1(bedplate, shoulder, elbow, elbowScrew, hand, handScrew);
  protocol = new HarvbotArmSerialProtocol(manipulator);
}

void loop() 
{
    protocol->run();
}
