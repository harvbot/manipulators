#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

#include <AFMotor.h>
#include <math.h>
#include "HarvbotArmConstants.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmAFMotorScrewNode.h"

HarvbotArmAFMotorScrewNode::HarvbotArmAFMotorScrewNode(HarvbotArmNodeIdentifiers identifier, int adafruitShieldPort, 
	float pos, int maxStepsCount, int maxFullRotaionCount) 
	: HarvbotArmScrewNode(identifier, pos, maxStepsCount, maxFullRotaionCount, 1)
{
	this->stepper = new AF_Stepper(maxStepsCount, adafruitShieldPort);
	this->setSpeed(HARVBOT_DEFAULT_STEPPER_SPEED);

	this->m_status = Ready;
}

HarvbotArmAFMotorScrewNode::~HarvbotArmAFMotorScrewNode()
{
	delete this->stepper;
}

float HarvbotArmAFMotorScrewNode::rotate(float steps) 
{
	this->m_status = InProcess;

	float prevPos = HarvbotArmScrewNode::getSteps();
	HarvbotArmScrewNode::rotate(steps);
	float currentPos = HarvbotArmScrewNode::getSteps();

	// Get the full step count.
	float fullSteps = floor(abs(currentPos-prevPos));

	// Get the microstep count.
	float microSteps = floor((abs(currentPos-prevPos) - fullSteps) * MICROSTEPS);

	// Get direction.
	int direction = currentPos-prevPos > 0 ? FORWARD : BACKWARD;

	// Rotate.
	this->stepper->step(fullSteps, direction, SINGLE);
	if(microSteps > 0)
	{
		this->stepper->step(microSteps, direction, MICROSTEP);
	}

	// Reset current position.
	this->m_pos=prevPos + (fullSteps+microSteps/(float)MICROSTEPS) * (direction == FORWARD ? 1 : -1);

	this->m_status = Ready;

	return this->m_pos;
}

void HarvbotArmAFMotorScrewNode::setSpeed(int speed) {
	HarvbotArmScrewNode::setSpeed(speed);

	this->stepper->setSpeed(speed);
}

HarvbotNodeStatuses HarvbotArmAFMotorScrewNode::getStatus()
{
	return this->m_status;
}

#endif