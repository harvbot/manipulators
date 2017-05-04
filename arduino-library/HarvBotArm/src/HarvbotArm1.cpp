#include "HarvbotArm.h"
#include "HarvbotArm1.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"

HarvbotArm1::HarvbotArm1(HarvbotArmServoNodePins beadplate, 
			HarvbotArmServoNodePins shoulder,
			HarvbotArmServoNodePins elbow,
			HarvbotArmServoNodePins elbowScrew,
			HarvbotArmServoNodePins hand,
			HarvbotArmServoNodePins handScrew) : HarvbotArm(HARVBOT_ARM_TYPE_1) {

	this->nodesCount = 6;
	
	this->nodes = new HarvbotArmNode*[6];

	this->nodes[0] = new HarvbotArmServoNode(HARVBOT_ARM_BEDPLATE_NODE, beadplate.Pin, beadplate.InitialPos, 0, 180);
	this->nodes[1] = new HarvbotArmServoNode(HARVBOT_ARM_SHOULDER_NODE, shoulder.Pin, shoulder.InitialPos, 5, 180);
	this->nodes[2] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_NODE, elbow.Pin, elbow.InitialPos, 20, 180);
	this->nodes[3] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_SCREW_NODE, elbowScrew.Pin, elbowScrew.InitialPos, 0, 180);
	this->nodes[4] = new HarvbotArmServoNode(HARVBOT_ARM_HAND_NODE, hand.Pin, hand.InitialPos, 0, 180);
	this->nodes[5] = new HarvbotArmServoNode(HARVBOT_ARM_HAND_SCREW_NODE, handScrew.Pin, handScrew.InitialPos, 0, 180);
}

HarvbotArm1::~HarvbotArm1() {
	
}

HarvbotArmNode* HarvbotArm1::getElbowScrew()
{
	return this->getNodeByType(HARVBOT_ARM_ELBOW_SCREW_NODE);
}

HarvbotArmNode* HarvbotArm1::getHand()
{
	return this->getNodeByType(HARVBOT_ARM_HAND_NODE);
}

HarvbotArmNode* HarvbotArm1::getHandScrew()
{
	return this->getNodeByType(HARVBOT_ARM_HAND_SCREW_NODE);
}