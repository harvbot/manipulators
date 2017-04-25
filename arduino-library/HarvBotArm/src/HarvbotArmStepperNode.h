#ifndef HarvbotArmStepperNode_H_
#define HarvbotArmStepperNode_H_

#include <Arduino.h>
#include <HarvbotArmNode.h>

class HarvbotArmStepperNode : public HarvbotArmNode {
	protected: 
		int m_pos;
		int m_speed;
		int m_maxStepsCount;
		int m_maxFullRotaionCount;
	public:
		HarvbotArmStepperNode(int type, int pos, int maxStepsCount, int maxFullRotaionCount);
		~HarvbotArmStepperNode();
		int read();
		virtual void rotate(int steps);
		int getSpeed();
		virtual void setSpeed(int speed);
};

#endif /* HarvbotArmStepperNode_H_ */