#ifndef HarvbotArmServoNode_H_
#define HarvbotArmServoNode_H_

#include <Arduino.h>
#include <Servo.h>

#include <HarvbotArmNode.h>

class HarvbotArmServoNode : public HarvbotArmNode {
	protected: 
		int m_pin;
		int m_pos;
		int m_minPos;
		int m_maxPos;
		Servo* servo;
	public:
		HarvbotArmServoNode(int pin, int pos, int minPos, int maxPos);
		~HarvbotArmServoNode();
		int read();
		void write(int pos);
		void sweep(int pos);
};

#endif /* GAMServoNode_H_ */