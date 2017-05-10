#ifndef HarvbotArmServoNode_H_
#define HarvbotArmServoNode_H_

#include <Arduino.h>
#include <Servo.h>

#include <HarvbotArmNode.h>

struct HarvbotArmServoNodePins
{
	int Pin;
	int InitialPos;
};

class HarvbotArmServoNode : public HarvbotArmNode {
	protected: 
		int m_pin;
		int m_pos;
		int m_minPos;
		int m_maxPos;
		int m_sweepDelay;
		Servo* servo;
	public:
		HarvbotArmServoNode(int type, int pin, int pos, int minPos, int maxPos);
		~HarvbotArmServoNode();
		int read();
		void write(int pos);
		void sweep(int pos);
		int getSweepDelay();
		void setSweepDelay(int delay);
};

#endif /* GAMServoNode_H_ */