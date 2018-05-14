#include <math.h>
#include "HarvbotArmLinearNode.h"

HarvbotArmLinearNode::HarvbotArmLinearNode(HarvbotArmNodeIdentifiers identifier, float pos, int stepsPerRevolution, int maxRevolutionsCount, int reductorGear)
	: HarvbotArmNode(identifier)
{
	this->m_pos = pos;
	this->m_stepsPerRevolution = stepsPerRevolution;
	this->m_maxRevolutionsCount = maxRevolutionsCount;
	this->m_reductorGear = reductorGear;
}

HarvbotArmLinearNode::~HarvbotArmLinearNode()
{
}

float HarvbotArmLinearNode::rotate(float steps)
{
	if(this->m_pos + steps < 0)
	{
		this->m_pos = 0;
	}
	else if(this->m_pos + steps >= this->m_maxRevolutionsCount * this->m_stepsPerRevolution * this->m_reductorGear)
	{
		this->m_pos = this->m_maxRevolutionsCount * this->m_stepsPerRevolution * this->m_reductorGear;
	}
	else
	{
		this->m_pos += steps;
	}

	return this->m_pos;
}

float HarvbotArmLinearNode::revolution(bool direction) {

	if(direction)
	{
		return this->rotate(this->m_stepsPerRevolution * this->m_reductorGear);
	}
	else
	{
		return this->rotate(-this->m_stepsPerRevolution * this->m_reductorGear);
	}
}

float HarvbotArmLinearNode::getCurrentAngle()
{
	// Calculate the number of revolutions which were done on screw.
	int fullRotation = round(this->m_pos) / (this->m_stepsPerRevolution * this->m_reductorGear);
	
	// Get the position on current revolution.
	float pos = this->m_pos - fullRotation * this->m_stepsPerRevolution * this->m_reductorGear;

	float anglePerStep = this->getAnglePerStep();

	// Calculate current angle.
	return pos * anglePerStep;
}

float HarvbotArmLinearNode::getAnglePerStep()
{
	return ((2.0*M_PI) / (this->m_stepsPerRevolution * this->m_reductorGear));
}

HarvbotArmNodeTypes HarvbotArmLinearNode::getType()
{
	return Screw;
}

float HarvbotArmLinearNode::currentPosition()
{
	return this->m_pos;
}

float HarvbotArmLinearNode::setCurrentPosition(float pos)
{
	this->m_pos = pos;

	return this->m_pos;
}

void HarvbotArmLinearNode::open()
{
	rotate(-currentPosition());
}

void HarvbotArmLinearNode::close()
{
	rotate(m_maxRevolutionsCount * this->m_stepsPerRevolution * this->m_reductorGear - currentPosition());
}