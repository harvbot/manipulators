#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"
#include "HarvbotArm1.h"

HarvbotArm1::HarvbotArm1() {
	this->bedplateNode = new HarvbotArmServoNode(SERVO_BEDPLATE_PIN, 90, 0, 180);
	this->shoulderNode = new HarvbotArmServoNode(SERVO_SHOULDER_PIN, 5, 5, 180);
	this->elbowNode = new HarvbotArmServoNode(SERVO_ELBOW_PIN, 20, 20, 180);
	this->elbowScrewNode = new HarvbotArmServoNode(SERVO_ELBOW_SCREW_PIN, 90, 0, 180);
	this->handNode = new HarvbotArmServoNode(SERVO_HAND_PIN, 90, 0, 180);
	this->handScrewNode = new HarvbotArmServoNode(SERVO_HAND_SCREW_PIN, 90, 0, 180);
}

HarvbotArm1::~HarvbotArm1() {
	delete this->bedplateNode;
	delete this->shoulderNode;
	delete this->elbowNode;
	delete this->elbowScrewNode;
	delete this->handNode;
	delete this->handScrewNode;
}

void HarvbotArm1::setup() {
}

HarvbotArmServoNode* HarvbotArm1::getBedplate()
{
	return this->bedplateNode;
}

HarvbotArmServoNode* HarvbotArm1::getShoulder()
{
	return this->shoulderNode;
}

HarvbotArmServoNode* HarvbotArm1::getElbow()
{
	return this->elbowNode;
}

HarvbotArmServoNode* HarvbotArm1::getElbowScrew()
{
	return this->elbowScrewNode;
}

HarvbotArmServoNode* HarvbotArm1::getHand()
{
	return this->handNode;
}

HarvbotArmServoNode* HarvbotArm1::getHandScrew()
{
	return this->handScrewNode;
}