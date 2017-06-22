#include "HarvbotArm.h"
#include "HarvbotArm1.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmConstants.h"

HarvbotArm1::HarvbotArm1(int beadplatePin, int shoulderPin, int elbowPin, int elbowScrewPin, int handPin, int handScrewPin) 
: HarvbotArm(ArmType1) {

	this->nodesCount = 6;
	
	this->nodes = new HarvbotArmNode*[6];

	this->nodes[0] = new HarvbotArmServoNode(Bedplate, beadplatePin, 90, 0, 180);
	this->nodes[1] = new HarvbotArmServoNode(Shoulder, shoulderPin, 150, 5, 180);
	this->nodes[2] = new HarvbotArmServoNode(Elbow, elbowPin, 60, 20, 180);
	this->nodes[3] = new HarvbotArmServoNode(ElbowScrew, elbowScrewPin, 60, 0, 180);
	this->nodes[4] = new HarvbotArmServoNode(Hand, handPin, 90, 0, 180);
	this->nodes[5] = new HarvbotArmServoNode(HandScrew, handScrewPin, 90, 0, 180);

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
	return this->getNodeByType(ElbowScrew);
}

HarvbotArmCircleNode* HarvbotArm1::getHand()
{
	return this->getNodeByType(Hand);
}

HarvbotArmCircleNode* HarvbotArm1::getHandScrew()
{
	return this->getNodeByType(HandScrew);
}