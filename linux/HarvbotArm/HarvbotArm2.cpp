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

	this->nodes[0] = new HarvbotArmStepperCircleNode(Bedplate, HARVBOT_ARM_SX_STEP, HARVBOT_ARM_SX_DIR, HARVBOT_ARM_SX_END, 3200, 45.0f, 0.0f, 360.0, 200, HARVBOT_ARM_SX_RATIO);
	this->nodes[1] = new HarvbotArmStepperCircleNode(Shoulder, HARVBOT_ARM_SY_STEP, HARVBOT_ARM_SY_DIR, HARVBOT_ARM_SY_END, 2400, 45.0f, 0.0f, 180, 200, HARVBOT_ARM_SY_RATIO);
	this->nodes[2] = new HarvbotArmStepperCircleNode(Elbow, HARVBOT_ARM_SZ_STEP, HARVBOT_ARM_SZ_DIR, HARVBOT_ARM_SZ_END, 800, 45.0f, 0.0f, 180, 200, HARVBOT_ARM_SZ_RATIO);
	this->nodes[3] = new HarvbotArmStepperScrewNode(Claw, HARVBOT_ARM_SJ_STEP, HARVBOT_ARM_SJ_DIR, HARVBOT_ARM_SJ_END, 1600, 0, 200, 8, HARVBOT_ARM_SJ_RATIO);
	//this->goToStartPosition();
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->goToStartPosition();
	((HarvbotArmCircleNode*)this->nodes[2])->goToStartPosition();
	((HarvbotArmCircleNode*)this->nodes[1])->goToStartPosition();
	((HarvbotArmScrewNode*)this->nodes[3])->goToStartPosition();

	((HarvbotArmCircleNode*)this->nodes[0])->move(180);
	((HarvbotArmCircleNode*)this->nodes[1])->move(60);
	((HarvbotArmCircleNode*)this->nodes[2])->move(25);

	runToPosition();
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(Claw);
}

HarvbotPoint HarvbotArm2::getPointerCoords()
{
	HarvbotPoint pointer;

	float q1 = this->getBedplate()->currentPosition();
	float q2 = this->getShoulder()->currentPosition();
	float q3 = PI - this->getElbow()->currentPosition();

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	pointer.x = (a2*cos(q2) + a3*cos(q2-q3))*cos(q1);
	pointer.y = (a2*sin(q2) + a3*sin(q2-q3))*sin(q1);
	pointer.z = a2*sin(q2) + a3*sin(q2-q3) + a1;

	return pointer;
}

bool HarvbotArm2::setPointerCoords(HarvbotPoint point)
{
	float x = point.x;
	float y = point.y;
	float z = point.z;

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	z = z - a1;

	float q1 = asin(y / z);

	x = x / cos(q1);

	float b = sqrt(x*x + z * z);
	float q2 = PI - asin(x/b) - asin((a2*a2 + b*b - a3*a3) / (2 * b*a2));
	float q3 = PI / 2.0 + asin(((a2*a2) + (a3*a3) - (b*b)) / (2 * a2*a3));

	this->getBedplate()->move(q1);
	this->getShoulder()->move(q2);
	this->getElbow()->move(PI-q3);

	runToPosition();
}

bool HarvbotArm2::pickObject(float distanceToObject)
{
	if (distanceToObject == 0) return false;

	float alpha = this->getShoulder()->currentPosition();
	float betta = this->getElbow()->currentPosition();
	float a = HARVBOT_ARM_2_BEDPLATE;
	float b = HARVBOT_ARM_2_SHOULDER;
	float c = HARVBOT_ARM_2_ELBOW;

	float xShoulder, zShoulder;
	xShoulder = b * cos(alpha + betta);
	zShoulder = b * sin(alpha + betta);

	HarvbotPoint currentPos = getPointerCoords();

	float xElbow = currentPos.x;
	float zElbow = currentPos.y;

	float xClaw, zClaw;

	if (zElbow == zShoulder)
	{
		xClaw = xElbow + distanceToObject;
	}
	else
	{
		float cost = c / (xElbow - xShoulder);
		float sint = c / (zElbow - zShoulder);

		// target position of claw
		xClaw = xElbow + distanceToObject * cost;
		zClaw = zElbow + distanceToObject * sint;

		HarvbotPoint p;
		p.x = xClaw;
		p.y = currentPos.y;
		p.z = zClaw;

		setPointerCoords(p);
	}
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