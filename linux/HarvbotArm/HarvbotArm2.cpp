#include <math.h>
#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmScrewNode.h"
#include "Nodes/HarvbotArmStepperCircleNode.h"
#include "Nodes/HarvbotArmStepperScrewNode.h"
#include "HarvbotArmConstants.h"

HarvbotArm2::HarvbotArm2() 
: HarvbotArm(ArmType2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmStepperCircleNode(Bedplate, HARVBOT_ARM_SX_STEP, HARVBOT_ARM_SX_DIR, HARVBOT_ARM_SX_END, 1000, 0.0f, 0.0f, 360.0, 200, HARVBOT_ARM_SX_RATIO);
	this->nodes[1] = new HarvbotArmStepperCircleNode(Shoulder, HARVBOT_ARM_SY_STEP, HARVBOT_ARM_SY_DIR, HARVBOT_ARM_SY_END, 1000, 0.0f, 0.0f, 180, 200, HARVBOT_ARM_SY_RATIO);
	this->nodes[2] = new HarvbotArmStepperCircleNode(Elbow, HARVBOT_ARM_SZ_STEP, HARVBOT_ARM_SZ_DIR, HARVBOT_ARM_SZ_END, 1000, 45.0f, 0.0f, 180, 200, HARVBOT_ARM_SZ_RATIO);
	this->nodes[3] = new HarvbotArmStepperScrewNode(Claw, HARVBOT_ARM_SJ_STEP, HARVBOT_ARM_SJ_DIR, HARVBOT_ARM_SJ_END, 1600, 0, 200, 8, HARVBOT_ARM_SJ_RATIO);

	//this->goToStartPosition();
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->goToStartPosition();
	((HarvbotArmCircleNode*)this->nodes[0])->move(180);

	((HarvbotArmCircleNode*)this->nodes[1])->goToStartPosition();
	((HarvbotArmCircleNode*)this->nodes[1])->move(60);

	((HarvbotArmCircleNode*)this->nodes[1])->goToStartPosition();
	((HarvbotArmCircleNode*)this->nodes[2])->move(25);

	((HarvbotArmScrewNode*)this->nodes[3])->goToStartPosition();
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(Claw);
}

HarvbotPoint HarvbotArm2::getPointerCoords()
{
	HarvbotPoint pointer;

	float alpha = this->getShoulder()->currentPosition();
	float betta = this->getElbow()->currentPosition();
	float gamma = this->getBedplate()->currentPosition();
	float a = HARVBOT_ARM_2_BEDPLATE;
	float b = HARVBOT_ARM_2_SHOULDER;
	float c = HARVBOT_ARM_2_ELBOW;

	float t = (c*cos(betta) - b) / cos(alpha);
	float m = pow(b, 2) + pow(c, 2) - 2 * b * c * cos(betta);
	float d = 4 * (pow(m, 2) / pow(cos(alpha), 2) - pow(t, 2));

	pointer.x = (-2 * t * tan(alpha) + sqrt(d))*pow(cos(alpha), 2) / 2.0;
	pointer.y = pointer.x * tan(alpha) + a + t;
	pointer.z = pointer.x * sin(gamma);

	return pointer;
}

void HarvbotArm2::printNodesPositions()
{
	printf("Bedplate: %f, Shoulder: %f, Elbow: %f, Claw: %f\n",
		((HarvbotArmCircleNode*)this->nodes[0])->currentPosition(),
		((HarvbotArmCircleNode*)this->nodes[1])->currentPosition(),
		((HarvbotArmCircleNode*)this->nodes[2])->currentPosition(),
		((HarvbotArmScrewNode*)this->nodes[3])->currentPosition());
}

void HarvbotArm2::printPointerPositions()
{
	HarvbotPoint pointer = getPointerCoords();
	printf("z: %f, y: %f, z: %f\n", pointer.x, pointer.y, pointer.z);
}