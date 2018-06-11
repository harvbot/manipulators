#include <math.h>
#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmLinearNode.h"
#include "Nodes/HarvbotArmStepperCircleNode.h"
#include "Nodes/HarvbotArmStepperLinearNode.h"
#include "HarvbotArmConstants.h"

HarvbotArm2::HarvbotArm2() 
: HarvbotArm(ArmType2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmStepperCircleNode(Bedplate, 
		HARVBOT_ARM_SX_STEP, 
		HARVBOT_ARM_SX_DIR, 
		HARVBOT_ARM_SX_END, 
		HARVBOT_ARM_SX_FR, 
		radians(0), 
		radians(-180), 
		radians(180), 
		HARVBOT_ARM_SX_MAX_STEPS,
		HARVBOT_ARM_SX_RATIO);

	this->nodes[1] = new HarvbotArmStepperCircleNode(Shoulder, 
		HARVBOT_ARM_SY_STEP, 
		HARVBOT_ARM_SY_DIR, 
		HARVBOT_ARM_SY_END, 
		HARVBOT_ARM_SY_FR, 
		radians(90),
		radians(30), 
		radians(180), 
		HARVBOT_ARM_SY_MAX_STEPS,
		HARVBOT_ARM_SY_RATIO);
	this->nodes[2] = new HarvbotArmStepperCircleNode(Elbow, 
		HARVBOT_ARM_SZ_STEP, 
		HARVBOT_ARM_SZ_DIR, 
		HARVBOT_ARM_SZ_END, 
		HARVBOT_ARM_SZ_FR, 
		radians(0), 
		radians(0), 
		radians(80), 
		HARVBOT_ARM_SZ_MAX_STEPS,
		HARVBOT_ARM_SZ_RATIO);
	this->nodes[3] = new HarvbotArmStepperLinearNode(Claw, 
		HARVBOT_ARM_SJ_STEP, 
		HARVBOT_ARM_SJ_DIR, 
		HARVBOT_ARM_SJ_END, 
		HARVBOT_ARM_SJ_FR, 
		0, 
		HARVBOT_ARM_SJ_MAX_STEPS,
		7, 
		HARVBOT_ARM_SJ_RATIO);

	((HarvbotArmStepperCircleNode*)this->getBedplate())->setAccelerationPercent(25);
	((HarvbotArmStepperCircleNode*)this->getShoulder())->setAccelerationPercent(25);
	((HarvbotArmStepperCircleNode*)this->getElbow())->setAccelerationPercent(25);
	((HarvbotArmStepperLinearNode*)this->getClaw())->setAccelerationPercent(40);
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	getClaw()->goToStartPosition();
	getClaw()->close();
	runToPosition();

	//getBedplate()->goToStartPosition();
	getElbow()->goToStartPosition();
	getShoulder()->goToStartPosition();

	//getBedplate()->moveTo(radians(0.0f));
	getShoulder()->moveTo(radians(90.0f));
	getElbow()->moveTo(radians(0.0f));
	runToPosition();

	getClaw()->goToStartPosition();
	runToPosition();
}

bool HarvbotArm2::run()
{
	bool result = getBedplate()->run();
	float shoulderPos = getShoulder()->currentPosition();
	float elbowPos = getElbow()->currentPosition();

	// If sholder and elbow angle difference is less the 10 degrees than wait for elbow movement and then run it.
	if (getShoulder()->distranceToGo() > 0 && getElbow()->distranceToGo() > 0)
	{
		if (elbowPos - shoulderPos + M_PI_2 > radians(0) || getElbow()->getStatus() == Ready)
		{
			result = getShoulder()->run() || result;
		}
		else
		{
			result = getShoulder()->getStatus() == InProcess || result;
		}
		result = getElbow()->run() || result;
	}
	else if (getShoulder()->distranceToGo() < 0 && getElbow()->distranceToGo() < 0)
	{
		if (elbowPos - shoulderPos - M_PI_2 < radians(45) || getElbow()->getStatus() == Ready)
		{
			result = getElbow()->run() || result;
		}
		else
		{
			result = getElbow()->getStatus() == InProcess || result;
		}
		result = getShoulder()->run() || result;
	}
	else
	{
		result = getShoulder()->run() || result;
		result = getElbow()->run() || result;
	}

	result = getClaw()->run() || result;

	return result;
}

HarvbotArmLinearNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmLinearNode*)this->getNodeByType(Claw);
}

HarvbotPoint HarvbotArm2::getPointerCoords()
{
	HarvbotPoint pointer;

	float q1 = this->getBedplate()->currentPosition();
	float q2 = M_PI - this->getShoulder()->currentPosition();
	float q3 = M_PI - (M_PI_2 - this->getElbow()->currentPosition());

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	pointer.x = (a2*cosf(q2) + a3*cosf(q2-q3))*cosf(q1);
	pointer.y = (a2*sinf(q2) + a3*sinf(q2-q3))*sinf(q1);
	pointer.z = a2*sinf(q2) + a3*sinf(q2-q3) + a1;

	return pointer;
}

bool HarvbotArm2::setPointerCoords(HarvbotPoint point)
{
	HarvbotPoint currentPos = getPointerCoords();

	float x = point.x;
	float y = point.y;
	float z = point.z;

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	z = z - a1;

	float q1 = round4(currentPos.y != point.y ? asin(y / z) : getBedplate()->currentPosition());

	x = x / cos(q1);

	float b = sqrt(x*x + z * z);
	float q2 = round4(M_PI - asin(x/b) - asin((a2*a2 + b*b - a3*a3) / (2 * b*a2)));
	float q3 = round4(M_PI_2 + asin(((a2*a2) + (a3*a3) - (b*b)) / (2 * a2*a3)));
	if (q2 - q3 < M_PI_2)
	{
		q2 = round4(asin(x / b) - asin((a2*a2 + b * b - a3 * a3) / (2 * b*a2)));
	}

	if (isnan(q2) || isnan(q3))
	{
		return false;
	}

	printPointerPositions();
	printf("x: %f, y: %f, z: %f\n", x, y, z);
	printf("q1=%q1 q2=%f q3=%f\n", degrees(q1), degrees(q2), degrees(q3));

	this->getBedplate()->moveTo(q1);
	this->getShoulder()->moveTo(M_PI - q2);
	this->getElbow()->moveTo(q3 - M_PI_2);

	return true;
}

bool HarvbotArm2::pickObject(float distanceToObject)
{
	if (distanceToObject == 0) return false;

	float q1 = this->getBedplate()->currentPosition();
	float q2 = M_PI - this->getShoulder()->currentPosition();
	float q3 = M_PI - (M_PI / 2 - this->getElbow()->currentPosition());

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	float xShoulder = 0, zShoulder = 0;
	xShoulder = a2 * cosf(q2);
	zShoulder = a2 * sinf(q2) + a1;

	HarvbotPoint currentPos = getPointerCoords();

	float xElbow = currentPos.x;
	float zElbow = currentPos.z;

	float xClaw, zClaw;

	if (zElbow == zShoulder)
	{
		xClaw = xElbow + distanceToObject;
		zClaw = zElbow;
	}
	else
	{
		float cost = 0;
		if (round(xElbow - xShoulder) != 0)
		{
			cost = a3 / (xElbow - xShoulder);
		}

		float sint = 0;
		if(round(zElbow - zShoulder) != 0)
		{ 
			sint = a3 / (zElbow - zShoulder);
		}
		
		// target position of claw
		xClaw = xElbow + distanceToObject * cost;
		zClaw = zElbow + distanceToObject * sint;
	}

	HarvbotPoint p;
	p.x = xClaw;
	p.y = currentPos.y;
	p.z = zClaw;

	if (setPointerCoords(p))
	{
		runToPosition();

		getClaw()->close();

		runToPosition();

		return true;
	}

	return false;
}

void HarvbotArm2::printNodesPositions()
{
	printf("Bedplate: %f, Shoulder: %f, Elbow: %f, Claw: %f\n",
		degrees(((HarvbotArmCircleNode*)this->nodes[0])->currentPosition()),
		degrees(((HarvbotArmCircleNode*)this->nodes[1])->currentPosition()),
		degrees(((HarvbotArmCircleNode*)this->nodes[2])->currentPosition()),
		degrees(((HarvbotArmLinearNode*)this->nodes[3])->currentPosition()));
}

void HarvbotArm2::printPointerPositions()
{
	HarvbotPoint pointer = getPointerCoords();
	printf("x: %f, y: %f, z: %f\n", pointer.x, pointer.y, pointer.z);
}