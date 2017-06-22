#include <math.h>
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmServoNode.h"

HarvbotArmServoNode::HarvbotArmServoNode(HarvbotArmNodeIdentifiers identifier, int pin, float pos, float minPos, float maxPos) 
	: HarvbotArmCircleNode(identifier, pos, minPos, maxPos)
{
	this->m_pin = pin;
	this->m_sweepDelay = 15;
	this->m_status = Ready;

	servo = new Servo();
	servo->attach(pin);
	servo->write((int)floor(pos));
}

HarvbotArmServoNode::~HarvbotArmServoNode(){
	servo->detach();
	delete servo;
}

float HarvbotArmServoNode::write(float pos) {

	this->m_status = InProcess;

	int currentPos = (int)read();

	pos = floor(pos);
	
	if (currentPos != pos)
	{
		if (pos > currentPos)
		{
			for (int i = currentPos+1; i <= (int)pos; i += 1) {
				servo->write(i);
				delay(m_sweepDelay);
			}
		}
		else if (currentPos < m_pos)
		{
			for (int i = currentPos-1; i >= (int)pos; i -= 1) {
				servo->write(i);
				delay(m_sweepDelay);
			}
		}

		HarvbotArmCircleNode::write(pos);
	}

	this->m_status = Ready;

	return pos;
}

int HarvbotArmServoNode::getSweepDelay()
{
	return this->m_sweepDelay;
}
		
void HarvbotArmServoNode::setSweepDelay(int delay)
{
	this->m_sweepDelay = delay;
}

HarvbotNodeStatuses HarvbotArmServoNode::getStatus()
{
	return this->m_status;
}