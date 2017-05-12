#include "HarvbotArmNode.h"
#include "HarvbotArmStepperNode.h"

HarvbotArmStepperNode::HarvbotArmStepperNode(int type, int pos, int maxStepsCount, int maxFullRotaionCount) 
	: HarvbotArmNode(type)
{
	this->m_pos = pos;
	this->m_maxStepsCount = maxStepsCount;
	this->m_maxFullRotaionCount = maxFullRotaionCount;
}

HarvbotArmStepperNode::~HarvbotArmStepperNode()
{
}

int HarvbotArmStepperNode::getSteps() 
{
	return this->m_pos;
}

void HarvbotArmStepperNode::rotate(int steps) 
{
	if(this->m_pos + steps < 0)
	{
		this->m_pos = 0;
	}
	else if(this->m_pos + steps >= this->m_maxFullRotaionCount * this->m_maxStepsCount)
	{
		this->m_pos = this->m_maxFullRotaionCount * this->m_maxStepsCount;
	}
	else
	{
		this->m_pos += steps;
	}
}

int HarvbotArmStepperNode::getSpeed() {
	return this->m_speed;
}

void HarvbotArmStepperNode::setSpeed(int speed) {
	this->m_speed = speed;
}

void HarvbotArmStepperNode::revolution(int direction) {

	if(direction == 1)
	{
		this->rotate(this->m_maxStepsCount);
	}
	else
	{
		this->rotate(-this->m_maxStepsCount);
	}
}