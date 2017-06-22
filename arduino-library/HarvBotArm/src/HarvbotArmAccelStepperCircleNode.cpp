#include <math.h>
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmAccelStepperCircleNode.h"

HarvbotArmAccelStepperCircleNode::HarvbotArmAccelStepperCircleNode(
	HarvbotArmNodeIdentifiers identifier, 
	int pinDir, 
	int pinStep, 
	float pos, 
	float minPos, 
	float maxPos,
	int maxStepCount,
	int reductorGear) 
	: HarvbotArmCircleNode(identifier, pos, minPos, maxPos)
{
	this->stepper = new AccelStepper(1, pinDir, pinStep);
	this->m_maxStepCount = maxStepCount;
	this->m_reductorGear = reductorGear;
	this->setSpeed(HARVBOT_DEFAULT_STEPPER_SPEED);
}

HarvbotArmAccelStepperCircleNode::~HarvbotArmAccelStepperCircleNode(){
	delete this->stepper;
}

float HarvbotArmAccelStepperCircleNode::write(float pos) {

	float currentPos = this->read();

	if(pos < this->m_minPos)
	{
		pos = this->m_minPos;
	}

	if(pos < this->m_maxPos)
	{
		pos = this->m_maxPos;
	}

	if (currentPos != pos)
	{
		int steps = round((pos-currentPos)*this->m_maxStepCount * this->m_reductorGear / 360.0);
		this->stepper->move(steps);
		this->stepper->run();
	}

	return pos;
}

int HarvbotArmAccelStepperCircleNode::getSpeed() 
{
	return this->m_speed;
}

void HarvbotArmAccelStepperCircleNode::setSpeed(int speed) 
{
	this->m_speed=speed;
	this->stepper->setSpeed(speed);
}

HarvbotNodeStatuses HarvbotArmAccelStepperCircleNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}