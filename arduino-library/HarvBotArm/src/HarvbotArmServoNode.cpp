#include <math.h>
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmServoNode.h"

HarvbotArmServoNode::HarvbotArmServoNode(int nodeType, int pin, float pos, float minPos, float maxPos) 
	: HarvbotArmCircleNode(nodeType, pos, minPos, maxPos)
{
	m_pin = pin;
	m_sweepDelay = 15;

	servo = new Servo();
	servo->attach(pin);
	servo->write((int)floor(pos));
}

HarvbotArmServoNode::~HarvbotArmServoNode(){
	servo->detach();
	delete servo;
}

float HarvbotArmServoNode::write(float pos) {

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

	return pos;
}

int HarvbotArmServoNode::getSweepDelay()
{
	return m_sweepDelay;
}
		
void HarvbotArmServoNode::setSweepDelay(int delay)
{
	m_sweepDelay = delay;
}