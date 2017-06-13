#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmConstants.h"

HarvbotArm2::HarvbotArm2(int beadplatePin, int shoulderPin, int elbowPin, HarvbotArmScrewNode* claw) 
: HarvbotArm(HARVBOT_ARM_TYPE_2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmServoNode(HARVBOT_ARM_BEDPLATE_NODE, beadplatePin, 90, 0, 180);
	this->nodes[1] = new HarvbotArmServoNode(HARVBOT_ARM_SHOULDER_NODE, shoulderPin, 150, 5, 180);
	this->nodes[2] = new HarvbotArmServoNode(HARVBOT_ARM_ELBOW_NODE, elbowPin, 60, 20, 180);
	this->nodes[3] = claw;

	this->goToStartPosition();
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->write(90);
	((HarvbotArmCircleNode*)this->nodes[1])->write(150);
	((HarvbotArmCircleNode*)this->nodes[2])->write(60);
	((HarvbotArmScrewNode*)this->nodes[3])->goToStartPosition();
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(HARVBOT_ARM_CLAW_NODE);
}