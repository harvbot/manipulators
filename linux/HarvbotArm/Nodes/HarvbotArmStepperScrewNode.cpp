#include <math.h>
#include "../HarvbotArmConstants.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmStepperScrewNode.h"

HarvbotArmStepperScrewNode::HarvbotArmStepperScrewNode(
	HarvbotArmNodeIdentifiers identifier, 
	uint8_t pinStep,
	uint8_t pinDir,
	uint8_t pinTerminal,
	unsigned int stepperFrequency,
	float pos, 
	unsigned int maxStepsCount,
	unsigned int maxFullRotaionCount,
	uint8_t reductorGear)
	: HarvbotArmScrewNode(identifier, pos, maxStepsCount, maxFullRotaionCount, reductorGear)
{
	this->stepper = new HarvbotTerminableStepper(pinStep, pinDir, pinTerminal);
	this->stepper->setEngineFrequency(stepperFrequency);
}

HarvbotArmStepperScrewNode::~HarvbotArmStepperScrewNode()
{
	delete this->stepper;
}

float HarvbotArmStepperScrewNode::rotate(float steps)
{
	int destinationPos = this->currentPosition();
	if (this->currentPosition() + steps < 0)
	{
		destinationPos = 0;
	}
	else if (this->currentPosition() + steps >= this->m_maxFullRotaionCount * this->m_maxStepsCount * this->m_reductorGear)
	{
		destinationPos = this->m_maxFullRotaionCount * this->m_maxStepsCount * this->m_reductorGear;
	}
	else
	{
		destinationPos += steps;
	}

	// Get the full step count.
	int fullSteps = (int)floor(destinationPos - this->currentPosition());

	// Rotate.
	this->stepper->move(fullSteps);

	return this->currentPosition();
}

HarvbotNodeStatuses HarvbotArmStepperScrewNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}

void HarvbotArmStepperScrewNode::goToStartPosition()
{
	this->stepper->runTillTerminal(false);
	setCurrentPosition(0);
}

bool HarvbotArmStepperScrewNode::run()
{
	long stepperPosStart = this->stepper->distanceToGo();
	bool result = this->stepper->run();
	long stepperPosEnd = this->stepper->distanceToGo();

	if (result && stepperPosStart != stepperPosEnd)
	{
		float currentPos = this->currentPosition();
		setCurrentPosition(currentPos + stepperPosStart - stepperPosEnd);
	}

	return result;
}

void HarvbotArmStepperScrewNode::runToPosition()
{
	while (run())
		;
}

void HarvbotArmStepperScrewNode::stop()
{
	this->stepper->stop();
}