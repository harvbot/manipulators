#include "HarvbotArmNode.h"
#include "HarvbotArmServoNode.h"

HarvbotArmServoNode::HarvbotArmServoNode(int pin, int minPos, int maxPos) {
	m_pin = pin;
	m_minPos = minPos;
	m_maxPos = maxPos;
	servo.attach(pin);
}

HarvbotArmServoNode::~HarvbotArmServoNode(){
	servo.detach();
}

int HarvbotArmServoNode::read() {
	return servo.read();
}

void HarvbotArmServoNode::write(int pos) {

	if (m_minPos <= pos && pos <= m_maxPos)
	{
		servo.write(pos);
	}
}