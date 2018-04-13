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

	float alpha = this->getShoulder()->currentPosition() *  PI / 180.0;
	float betta = this->getElbow()->currentPosition() *  PI / 180.0;
	float gamma = this->getBedplate()->currentPosition() *  PI / 180.0;
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

bool HarvbotArm2::pickObject(float distanceToObject)
{
	if (distanceToObject == 0) return false;

	float alpha = this->getShoulder()->currentPosition() *  PI / 180.0;
	float betta = this->getElbow()->currentPosition() *  PI / 180.0;
	float a = HARVBOT_ARM_2_BEDPLATE;
	float b = HARVBOT_ARM_2_SHOULDER;
	float c = HARVBOT_ARM_2_ELBOW;

	float xC = HARVBOT_ARM_2_SHOULDER * sin(alpha);
	float yC = HARVBOT_ARM_2_BEDPLATE - HARVBOT_ARM_2_SHOULDER*cos(alpha);

	HarvbotPoint dPoint = getPointerCoords();
	float xD = dPoint.x;
	float yD = dPoint.y;

	float xE, yE;

	if (xC == xD)
	{
		xE = xD;
		if (yD > yC)
		{
			yE = yD + distanceToObject;
		}
		else
		{
			yE = yC + distanceToObject;
		}
	}
	else
	{
		float k = (yD - yC) / (xD - xC);
		float s = k * xC - yC;
		float p = 1 + k * k;
		float q = -2 * (xD + k * (s + yD));

		float r = pow(xD, 2) + pow((s + yD), 2) - pow(distanceToObject, 2);
		float d = pow(q, 2) - 4 * p*r;

		float xE1 = (-q + sqrt(d)) / (2 * p);
		float xE2 = (-q - sqrt(d)) / (2 * p);

		if (xE1 >= xD && xD >= xC)
		{
			xE = xE1;
		}
		else if (xE1 <= xD && xD <= xC)
		{
			xE = xE1;
		}
		else if (xE2 >= xD && xD >= xC)
		{
			xE = xE2;
		}
		else if (xE2 <= xD && xD <= xC)
		{
			xE = xE2;
		}

		yE = k * xE - s;

		float t2 = pow(c, 2) - pow(xE, 2) - pow(b, 2) - pow(yE, 2) + 2 * a * yE - pow(a, 2);
		float p2 = pow((yE - a), 2) + pow(xE, 2);
		float q2 = -t2 * (yE - a) / b;

		float r2 = pow(t2, 2) / pow(4 * b, 2) - pow(xE, 2);
		float d2 = pow(q2, 2) - 4 * p2*r2;

		float targetBetta = acos((pow(b, 2) + pow(c, 2) - pow(a, 2) + 2 * a*yE - pow(xE, 2) - pow(yE, 2)) / (2 * b*c));
		
		float targetAlpha1 = acos((-q2 - sqrt(d2)) / (2 * p2));
		float targetAlpha2 = acos((-q2 + sqrt(d2)) / (2 * p2));

		float targetAlpha = abs(targetAlpha1 - alpha) < abs(targetAlpha2 - alpha) ? targetAlpha1 : targetAlpha2;

		this->getShoulder()->moveTo(targetAlpha);
		this->getElbow()->moveTo(targetBetta);

		this->runToPosition();
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