#ifndef HarvbotArmStepperNode_H_
#define HarvbotArmStepperNode_H_

#include <Arduino.h>
#include <HarvbotArmNode.h>

class HarvbotArmStepperNode : public HarvbotArmNode {
	protected: 
		float m_pos;
		int m_speed;
		int m_maxStepsCount;
		int m_maxFullRotaionCount;
	public:
		HarvbotArmStepperNode(int type, float pos, int maxStepsCount, int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION);
		~HarvbotArmStepperNode();
		float getSteps();
		virtual float rotate(float steps);
		int getSpeed();
		virtual void setSpeed(int speed);
		virtual float revolution(int direction);
		virtual float getAnglePerStep();
		virtual float getCurrentAngle();
};

#endif /* HarvbotArmStepperNode_H_ */