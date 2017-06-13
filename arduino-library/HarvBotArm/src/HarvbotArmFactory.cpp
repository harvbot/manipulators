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
	return new HarvbotArm1(2, 3, 4, 5, 6, 7);
}

HarvbotArm2* HarvbotArmFactory::CreateAFMotorArm2()
{
	HarvbotArmAFMotorScrewNode* claw = new HarvbotArmAFMotorScrewNode(HARVBOT_ARM_CLAW_NODE, 2, 0, 200, HARVBOT_ARM_CLAW_MAX_FULL_ROTATION);
	claw->setSpeed(50);
	
	return new HarvbotArm2(22, 23, 24, claw);
}