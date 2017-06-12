#include "HarvbotArm.h"
#include "HarvbotArm1.h"
#include "HarvbotArm2.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmAFMotorScrewNode.h"
#include "HarvbotArmFactory.h"

HarvbotArmFactory::HarvbotArmFactory() {
}

HarvbotArm1* HarvbotArmFactory::CreateServoArm1()
{
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
	
	return new HarvbotArm1(bedplate, shoulder, elbow, elbowScrew, hand, handScrew);
}

HarvbotArm2* HarvbotArmFactory::CreateAFMotorArm2()
{
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
	
	return new HarvbotArm2(bedplate, shoulder, elbow, claw);
}