#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"
#include "HarvbotArmScrewNode.h"

HarvbotArm2::HarvbotArm2(HarvbotArmServoNodePins beadplate, 
			HarvbotArmServoNodePins shoulder,
			HarvbotArmServoNodePins elbow,
			HarvbotArmScrewNode* claw) : HarvbotArm(HARVBOT_ARM_TYPE_2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmServoNode(HARVBOT_ARM_BEDPLATE_NODE, beadplate.Pin, beadplate.InitialPos, 0, 180);
	this->nodes[1] = new HarvbotArmServoNode(HARVBOT_ARM_SHOULDER_NODE, shoulder.Pin, shoulder.InitialPos, 5, 180);
	this->nodes[2] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_NODE, elbow.Pin, elbow.InitialPos, 20, 180);
	this->nodes[3] = claw;
}

HarvbotArm2::~HarvbotArm2() {
	
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(HARVBOT_ARM_CLAW_NODE);
}