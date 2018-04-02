#include <math.h>
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmStepperCircleNode.h"

HarvbotArmStepperCircleNode::HarvbotArmStepperCircleNode(
	HarvbotArmNodeIdentifiers identifier, 
	uint8_t pinStep,
	uint8_t pinDir,
	uint8_t pinTerminal,
	float pos, 
	float minPos, 
	float maxPos,
	unsigned int maxStepCount,
	uint8_t reductorGear)
	: HarvbotArmCircleNode(identifier, pos, minPos, maxPos)
{
	this->stepper = new HarvbotTerminableStepper(pinStep, pinDir, pinTerminal);
	this->m_maxStepCount = maxStepCount;
	this->m_reductorGear = reductorGear;
}

HarvbotArmStepperCircleNode::~HarvbotArmStepperCircleNode(){
	delete this->stepper;
}

float HarvbotArmStepperCircleNode::write(float pos) {

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

HarvbotNodeStatuses HarvbotArmStepperCircleNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}