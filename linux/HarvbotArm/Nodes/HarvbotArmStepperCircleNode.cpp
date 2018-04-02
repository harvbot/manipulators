#include <math.h>
#include "../HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmStepperCircleNode.h"

HarvbotArmStepperCircleNode::HarvbotArmStepperCircleNode(
	HarvbotArmNodeIdentifiers identifier, 
	uint8_t pinStep,
	uint8_t pinDir,
	uint8_t pinTerminal,
	unsigned int stepperFrequency,
	float pos, 
	float minPos, 
	float maxPos,
	unsigned int maxStepCount,
	uint8_t reductorGear)
	: HarvbotArmCircleNode(identifier, pos, minPos, maxPos)
{
	this->stepper = new HarvbotTerminableStepper(pinStep, pinDir, pinTerminal);
	this->stepper->setEngineFrequency(stepperFrequency);
	this->m_maxStepCount = maxStepCount;
	this->m_reductorGear = reductorGear;
}

HarvbotArmStepperCircleNode::~HarvbotArmStepperCircleNode(){
	delete this->stepper;
}

float HarvbotArmStepperCircleNode::move(float pos) {

	float currentPos = this->currentPosition();

	if(pos < this->m_minPos)
	{
		pos = this->m_minPos;
	}

	if(pos > this->m_maxPos)
	{
		pos = this->m_maxPos;
	}

	if (currentPos != pos)
	{
		int steps = round((pos-currentPos)*this->m_maxStepCount * this->m_reductorGear / 360.0);
		this->stepper->move(steps);
	}

	return pos;
}

HarvbotNodeStatuses HarvbotArmStepperCircleNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}

bool HarvbotArmStepperCircleNode::run()
{
	return this->stepper->run();
}

void HarvbotArmStepperCircleNode::runToPosition()
{
	return this->stepper->runToPosition();
}

void HarvbotArmStepperCircleNode::goToStartPosition()
{
	return this->stepper->runTillTerminal(false);
}