#include <Servo.h>
#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"

HarvbotArmServoNode::HarvbotArmServoNode(int type, int pin, int pos, int minPos, int maxPos) 
	: HarvbotArmNode(type)
{
	m_pin = pin;
	m_pos = pos;
	m_minPos = minPos;
	m_maxPos = maxPos;
	m_sweepDelay = 15;

	servo = new Servo();
	servo->attach(pin);
	servo->write(pos);
}

HarvbotArmServoNode::~HarvbotArmServoNode(){
	servo->detach();
}

int HarvbotArmServoNode::read() {
	return m_pos;
}

void HarvbotArmServoNode::write(int pos) {

	if (m_minPos <= pos && pos <= m_maxPos)
	{
		m_pos = pos;
		servo->write(pos);
	}
}

void HarvbotArmServoNode::sweep(int pos) {

	if (m_minPos > pos)
	{
		pos = m_minPos;
	}

	if (m_maxPos < pos)
	{
		pos = m_maxPos;
	}

	if (m_pos != pos)
	{
		if (pos > m_pos)
		{
			for (int i = m_pos+1; i <= pos; i += 1) {
				m_pos = i;
				servo->write(i);
				delay(m_sweepDelay);
			}
		}
		else if (pos < m_pos)
		{
			for (int i = m_pos-1; i >= pos; i -= 1) {
				m_pos = i;
				servo->write(i);
				delay(m_sweepDelay);
			}
		}
	}
}

int HarvbotArmServoNode::getSweepDelay()
{
	return m_sweepDelay;
}
		
void HarvbotArmServoNode::setSweepDelay(int delay)
{
	m_sweepDelay = delay;
}