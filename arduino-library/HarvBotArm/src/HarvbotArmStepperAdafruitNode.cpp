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

	// Get the full step count.
	float fullSteps = floor(abs(currentPos-prevPos));

	// Get the microstep count.
	float microSteps = floor((abs(currentPos-prevPos) - fullSteps) * MICROSTEPS);

	// Get direction
	int direction = currentPos-prevPos > 0 ? FORWARD : BACKWARD;

	// Rotate
	this->stepper->step(fullSteps, direction, SINGLE);
	if(microSteps > 0)
	{
		this->stepper->step(microSteps, direction, MICROSTEP);
	}

	// Reset current position.
	this->m_pos=prevPos + (fullSteps+microSteps/(float)MICROSTEPS) * (direction == FORWARD ? 1 : -1);

	return this->m_pos;
}

void HarvbotArmStepperAdafruitNode::setSpeed(int speed) {
	HarvbotArmStepperNode::setSpeed(speed);

	this->stepper->setSpeed(speed);
}

#endif