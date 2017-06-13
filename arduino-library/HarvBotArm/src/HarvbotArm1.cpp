#include "HarvbotArm.h"
#include "HarvbotArm1.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmConstants.h"

HarvbotArm1::HarvbotArm1(int beadplatePin, int shoulderPin, int elbowPin, int elbowScrewPin, int handPin, int handScrewPin) 
: HarvbotArm(HARVBOT_ARM_TYPE_1) {

	this->nodesCount = 6;
	
	this->nodes = new HarvbotArmNode*[6];

	this->nodes[0] = new HarvbotArmServoNode(HARVBOT_ARM_BEDPLATE_NODE, beadplatePin, 90, 0, 180);
	this->nodes[1] = new HarvbotArmServoNode(HARVBOT_ARM_SHOULDER_NODE, shoulderPin, 150, 5, 180);
	this->nodes[2] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_NODE, elbowPin, 60, 20, 180);
	this->nodes[3] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_SCREW_NODE, elbowScrewPin, 60, 0, 180);
	this->nodes[4] = new HarvbotArmServoNode(HARVBOT_ARM_HAND_NODE, handPin, 90, 0, 180);
	this->nodes[5] = new HarvbotArmServoNode(HARVBOT_ARM_HAND_SCREW_NODE, handScrewPin, 90, 0, 180);

	this->goToStartPosition();
}

HarvbotArm1::~HarvbotArm1() {}

void HarvbotArm1::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->write(90);
	((HarvbotArmCircleNode*)this->nodes[1])->write(150);
	((HarvbotArmCircleNode*)this->nodes[2])->write(60);
	((HarvbotArmCircleNode*)this->nodes[3])->write(60);
	((HarvbotArmCircleNode*)this->nodes[4])->write(90);
	((HarvbotArmCircleNode*)this->nodes[5])->write(90);
}

HarvbotArmCircleNode* HarvbotArm1::getElbowScrew()
{
	return this->getNodeByType(HARVBOT_ARM_ELBOW_SCREW_NODE);
}

HarvbotArmCircleNode* HarvbotArm1::getHand()
{
	return this->getNodeByType(HARVBOT_ARM_HAND_NODE);
}

HarvbotArmCircleNode* HarvbotArm1::getHandScrew()
{
	return this->getNodeByType(HARVBOT_ARM_HAND_SCREW_NODE);
}