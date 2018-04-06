#include <math.h>
#include "HarvbotArmNode.h"
#include "HarvbotArmScrewNode.h"

HarvbotArmScrewNode::HarvbotArmScrewNode(HarvbotArmNodeIdentifiers identifier, float pos, int maxStepsCount, int maxFullRotaionCount, int reductorGear) 
	: HarvbotArmNode(identifier)
{
	this->m_pos = pos;
	this->m_maxStepsCount = maxStepsCount;
	this->m_maxFullRotaionCount = maxFullRotaionCount;
	this->m_reductorGear = reductorGear;
}

HarvbotArmScrewNode::~HarvbotArmScrewNode()
{
}

float HarvbotArmScrewNode::rotate(float steps) 
{
	if(this->m_pos + steps < 0)
	{
		this->m_pos = 0;
	}
	else if(this->m_pos + steps >= this->m_maxFullRotaionCount * this->m_maxStepsCount * this->m_reductorGear)
	{
		this->m_pos = this->m_maxFullRotaionCount * this->m_maxStepsCount * this->m_reductorGear;
	}
	else
	{
		this->m_pos += steps;
	}

	return this->m_pos;
}

float HarvbotArmScrewNode::revolution(int direction) {

	if(direction == 1)
	{
		return this->rotate(this->m_maxStepsCount * this->m_reductorGear);
	}
	else
	{
		return this->rotate(-this->m_maxStepsCount * this->m_reductorGear);
	}
}

float HarvbotArmScrewNode::getCurrentAngle()
{
	// Calculate the number of revolutions which were done on screw.
	int fullRotation = round(this->m_pos) / (this->m_maxStepsCount * this->m_reductorGear);
	
	// Get the position on current revolution.
	float pos = this->m_pos - fullRotation * this->m_maxStepsCount * this->m_reductorGear;

	float anglePerStep = this->getAnglePerStep();

	// Calculate current angle.
	return pos * anglePerStep;
}

float HarvbotArmScrewNode::getAnglePerStep()
{
	return 360.0 / (this->m_maxStepsCount  * this->m_reductorGear);
}

HarvbotArmNodeTypes HarvbotArmScrewNode::getType()
{
	return Screw;
}

float HarvbotArmScrewNode::currentPosition()
{
	return this->m_pos;
}

float HarvbotArmScrewNode::setCurrentPosition(float pos)
{
	this->m_pos = pos;

	return this->m_pos;
}