#include "HarvbotArmNode.h"
#include "HarvbotArmStepperNode.h"

HarvbotArmStepperNode::HarvbotArmStepperNode(int type, float pos, int maxStepsCount, int maxFullRotaionCount) 
	: HarvbotArmNode(type)
{
	this->m_pos = pos;
	this->m_maxStepsCount = maxStepsCount;
	this->m_maxFullRotaionCount = maxFullRotaionCount;
}

HarvbotArmStepperNode::~HarvbotArmStepperNode()
{
}

float HarvbotArmStepperNode::getSteps() 
{
	return this->m_pos;
}

float HarvbotArmStepperNode::rotate(float steps) 
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

	return this->m_pos;
}

int HarvbotArmStepperNode::getSpeed() {
	return this->m_speed;
}

void HarvbotArmStepperNode::setSpeed(int speed) {
	this->m_speed = speed;
}

float HarvbotArmStepperNode::revolution(int direction) {

	if(direction == 1)
	{
		return this->rotate(this->m_maxStepsCount);
	}
	else
	{
		return this->rotate(-this->m_maxStepsCount);
	}
}

float HarvbotArmStepperNode::getCurrentAngle()
{
	int fullRotation = round(this->m_pos) / this->m_maxStepsCount;
	float pos = this->m_pos - fullRotation * this->m_maxStepsCount;
	float anglePerStep = 360.0 / this->m_maxStepsCount;
	return pos * anglePerStep;
}