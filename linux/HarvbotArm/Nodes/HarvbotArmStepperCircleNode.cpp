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
		int steps = round((pos - currentPos)*this->m_maxStepCount * this->m_reductorGear / (2.0 * M_PI));
		this->stepper->move(steps);
	}

	return pos;
}

HarvbotNodeStatuses HarvbotArmStepperCircleNode::getStatus()
{
	return this->stepper->distanceToGo()==0 ? Ready : InProcess;
}

float HarvbotArmStepperCircleNode::distranceToGo()
{
	return this->stepper->distanceToGo() * getAnglePerStep();
}

bool HarvbotArmStepperCircleNode::run()
{
	long stepperPosStart = this->stepper->distanceToGo();
	bool result = this->stepper->run();
	long stepperPosEnd = this->stepper->distanceToGo();

	if (result && stepperPosStart != stepperPosEnd)
	{
		float currentPos = this->currentPosition();
		float offset = getAnglePerStep() * (stepperPosStart - stepperPosEnd);
		//printf("New postion %d offset: %f, pos: %f\n", getType(), (offset), (currentPos + offset));
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
		int steps = round(-1 * this->m_maxStepCount * this->m_reductorGear / (2.0 * M_PI));
		this->stepper->move(steps);

		run();
	} while (!this->stepper->isTerminated());

	setCurrentPosition(getMinPos());
}

float HarvbotArmStepperCircleNode::getAnglePerStep()
{
	return ((2.0*M_PI) / (this->m_maxStepCount * this->m_reductorGear));
}

void HarvbotArmStepperCircleNode::stop()
{
	this->stepper->stop();
}

unsigned int HarvbotArmStepperCircleNode::accelerationPercent()
{
	return this->stepper->accelerationPercent();
}

void HarvbotArmStepperCircleNode::setAccelerationPercent(unsigned int percent)
{
	this->stepper->setAccelerationPercent(percent);
}