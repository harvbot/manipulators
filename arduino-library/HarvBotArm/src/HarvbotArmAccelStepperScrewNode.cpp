#include <AccelStepper.h>
#include <math.h>
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmAccelStepperScrewNode.h"

HarvbotArmAccelStepperScrewNode::HarvbotArmAccelStepperScrewNode(
	int nodeType, 
	int pinDir,
	int pinStep, 
	float pos, 
	int maxStepsCount, 
	int maxFullRotaionCount, 
	int reductorGear) 
	: HarvbotArmScrewNode(nodeType, pos, maxStepsCount, maxFullRotaionCount, reductorGear)
{
	this->stepper = new AccelStepper(1, pinDir, pinStep);
}

HarvbotArmAccelStepperScrewNode::~HarvbotArmAccelStepperScrewNode()
{
	delete this->stepper;
}

float HarvbotArmAccelStepperScrewNode::rotate(float steps) 
{
	float prevPos = HarvbotArmScrewNode::getSteps();
	HarvbotArmScrewNode::rotate(steps);
	float currentPos = HarvbotArmScrewNode::getSteps();

	// Get the full step count.
	int fullSteps = (int)floor(currentPos-prevPos);

	// Wait till current action will be finished.
	while(this->stepper->distanceToGo()!=0)
	{
		delay(10);
	}

	// Rotate.
	this->stepper->move(fullSteps);
	this->stepper->run();

	// Reset current position.
	this->m_pos=prevPos + fullSteps;

	return this->m_pos;
}

void HarvbotArmAccelStepperScrewNode::setSpeed(int speed) {
	HarvbotArmScrewNode::setSpeed(speed);

	this->stepper->setSpeed(speed);
}