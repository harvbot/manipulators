#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

#include <AFMotor.h>
#include "HarvbotArmStepperNode.h"
#include "HarvbotArmStepperAdafruitNode.h"

HarvbotArmStepperAdafruitNode::HarvbotArmStepperAdafruitNode(int type, int adafruitShieldPort, 
	int pos, int maxStepsCount, int maxFullRotaionCount) 
	: HarvbotArmStepperNode(type, pos, maxStepsCount, maxFullRotaionCount)
{
	this->stepper = new AF_Stepper(maxStepsCount, adafruitShieldPort);
}

HarvbotArmStepperAdafruitNode::~HarvbotArmStepperAdafruitNode()
{
	delete this->stepper;
}

void HarvbotArmStepperAdafruitNode::rotate(int steps) 
{
	int prevPos = HarvbotArmStepperNode::read();
	HarvbotArmStepperNode::rotate(steps);
	int currentPos = HarvbotArmStepperNode::read();

	if(currentPos-prevPos > 0)
	{
		this->stepper->step(abs(currentPos-prevPos), FORWARD, SINGLE);
	}
	else
	{
		this->stepper->step(abs(currentPos-prevPos), BACKWARD, SINGLE);
	}
}

void HarvbotArmStepperAdafruitNode::setSpeed(int speed) {
	HarvbotArmStepperNode::setSpeed(speed);

	this->stepper->setSpeed(speed);
}

#endif