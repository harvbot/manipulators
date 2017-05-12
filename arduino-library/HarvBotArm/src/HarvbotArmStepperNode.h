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
		HarvbotArmStepperNode(int type, int pos, int maxStepsCount, int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION);
		~HarvbotArmStepperNode();
		int getSteps();
		virtual void rotate(int steps);
		int getSpeed();
		virtual void setSpeed(int speed);
		virtual void revolution(int direction);
};

#endif /* HarvbotArmStepperNode_H_ */