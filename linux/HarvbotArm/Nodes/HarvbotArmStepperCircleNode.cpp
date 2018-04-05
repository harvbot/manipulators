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

float HarvbotArmStepperCircleNode::moveTo(float pos) {

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
		int steps = round((pos - currentPos)*this->m_maxStepCount * this->m_reductorGear / 360.0);
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
	bool result = this->stepper->run();

	if (result)
	{
		float currentPos = this->currentPosition();
		float offset = getAnglePerStep() * (this->stepper->direction() ? 1 : -1);
		printf("%f\n", (currentPos + offset));
		setCurrentPosition(currentPos + offset);
	}

	return result;
}

void HarvbotArmStepperCircleNode::runToPosition()
{
	while (run())
		;
}

void HarvbotArmStepperCircleNode::goToStartPosition()
{
	do
	{
		move(-1);
		run();
	} while (!this->stepper->isTerminated());
}

float HarvbotArmStepperCircleNode::getAnglePerStep()
{
	return (360.0 / (this->m_maxStepCount * this->m_reductorGear));
}