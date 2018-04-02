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
	float prevPos = HarvbotArmScrewNode::getSteps();
	HarvbotArmScrewNode::rotate(steps);
	float currentPos = HarvbotArmScrewNode::getSteps();

	// Get the full step count.
	int fullSteps = (int)floor(currentPos-prevPos);

	// Rotate.
	this->stepper->move(fullSteps);

	// Reset current position.
	this->m_pos=prevPos + fullSteps;

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
	return this->stepper->run();
}

void HarvbotArmStepperScrewNode::runToPosition()
{
	return this->stepper->runToPosition();
}