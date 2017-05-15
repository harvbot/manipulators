#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

#include <AFMotor.h>
#include <math.h>
#include "HarvbotArmStepperNode.h"
#include "HarvbotArmStepperAdafruitNode.h"

HarvbotArmStepperAdafruitNode::HarvbotArmStepperAdafruitNode(int type, int adafruitShieldPort, 
	float pos, int maxStepsCount, int maxFullRotaionCount) 
	: HarvbotArmStepperNode(type, pos, maxStepsCount, maxFullRotaionCount)
{
	this->stepper = new AF_Stepper(maxStepsCount, adafruitShieldPort);
}

HarvbotArmStepperAdafruitNode::~HarvbotArmStepperAdafruitNode()
{
	delete this->stepper;
}

float HarvbotArmStepperAdafruitNode::rotate(float steps) 
{
	float prevPos = HarvbotArmStepperNode::getSteps();
	HarvbotArmStepperNode::rotate(steps);
	float currentPos = HarvbotArmStepperNode::getSteps();

	float fullSteps = floor(abs(currentPos-prevPos));
	float partSteps = floor(((abs(currentPos-prevPos) - fullSteps) * 100) / MICROSTEPS);

	if(currentPos-prevPos > 0)
	{
		this->stepper->step(fullSteps, FORWARD, SINGLE);
		if(partSteps > 0)
		{
			this->stepper->step(partSteps, FORWARD, MICROSTEP);
		}
	}
	else if(currentPos-prevPos < 0)
	{
		this->stepper->step(fullSteps, BACKWARD, SINGLE);
		if(partSteps > 0)
		{
			this->stepper->step(partSteps, FORWARD, MICROSTEP);
		}
	}

	return currentPos;
}

void HarvbotArmStepperAdafruitNode::setSpeed(int speed) {
	HarvbotArmStepperNode::setSpeed(speed);

	this->stepper->setSpeed(speed);
}

#endif