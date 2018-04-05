#include <math.h>
#include <wiringPi.h>
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
	this->stepper = new HarvbotTerminableStepper(pinDir, pinStep, pinTerminal);
	this->stepper->setEngineFrequency(stepperFrequency);
}

HarvbotArmStepperScrewNode::~HarvbotArmStepperScrewNode()
{
	delete this->stepper;
}

float HarvbotArmStepperScrewNode::rotate(float steps)
{
	float prevPos = HarvbotArmScrewNode::currentPosition();
	HarvbotArmScrewNode::rotate(steps);
	float currentPos = HarvbotArmScrewNode::currentPosition();

	// Get the full step count.
	int fullSteps = (int)floor(currentPos-prevPos);

	// Rotate.
	this->stepper->move(fullSteps);

	return this->m_pos;
}

HarvbotNodeStatuses HarvbotArmStepperScrewNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}

void HarvbotArmStepperScrewNode::goToStartPosition()
{
	this->stepper->runTillTerminal(false);
}

bool HarvbotArmStepperScrewNode::run()
{
	bool result = this->stepper->run();

	if (result)
	{
		this->m_pos += getAnglePerStep();
	}

	return result;
}

void HarvbotArmStepperScrewNode::runToPosition()
{
	while (run())
		;
}