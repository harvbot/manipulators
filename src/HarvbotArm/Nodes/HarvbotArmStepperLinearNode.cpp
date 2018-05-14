#include <math.h>
#include "HarvbotArmStepperLinearNode.h"

HarvbotArmStepperLinearNode::HarvbotArmStepperLinearNode(
	HarvbotArmNodeIdentifiers identifier, 
	uint8_t pinStep,
	uint8_t pinDir,
	uint8_t pinTerminal,
	unsigned int stepperFrequency,
	float pos, 
	unsigned int maxStepsCount,
	unsigned int maxFullRotaionCount,
	uint8_t reductorGear)
	: HarvbotArmStepperLinearNode(identifier, pos, maxStepsCount, maxFullRotaionCount, reductorGear)
{
	this->stepper = new HarvbotTerminableStepper(pinStep, pinDir, pinTerminal);
	this->stepper->setEngineFrequency(stepperFrequency);
}

HarvbotArmStepperLinearNode::~HarvbotArmStepperLinearNode()
{
	delete this->stepper;
}

float HarvbotArmStepperLinearNode::rotate(float steps)
{
	int destinationPos = this->currentPosition();
	if (this->currentPosition() + steps < 0)
	{
		destinationPos = 0;
	}
	else if (this->currentPosition() + steps >= this->m_maxRevolutionsCount * this->m_stepsPerRevolution * this->m_reductorGear)
	{
		destinationPos = this->m_maxRevolutionsCount * this->m_stepsPerRevolution * this->m_reductorGear;
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

HarvbotNodeStatuses HarvbotArmStepperLinearNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}

void HarvbotArmStepperLinearNode::goToStartPosition()
{
	this->stepper->runTillTerminal(false);
	setCurrentPosition(0);
}

bool HarvbotArmStepperLinearNode::run()
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

void HarvbotArmStepperLinearNode::runToPosition()
{
	while (run())
		;
}

void HarvbotArmStepperLinearNode::stop()
{
	this->stepper->stop();
}

float HarvbotArmStepperLinearNode::distranceToGo()
{
	return this->stepper->distanceToGo();
}

unsigned int HarvbotArmStepperLinearNode::accelerationPercent()
{
	return this->stepper->accelerationPercent();
}

void HarvbotArmStepperLinearNode::setAccelerationPercent(unsigned int percent)
{
	this->stepper->setAccelerationPercent(percent);
}