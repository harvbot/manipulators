#ifndef HarvbotArmServoNode_H_
#define HarvbotArmServoNode_H_

#include <Servo.h>
#include <HarvbotArmConstants.h>
#include <HarvbotArmCircleNode.h>

struct HarvbotArmServoNodePins
{
	int Pin;
	int InitialPos;
};

class HarvbotArmServoNode : public HarvbotArmCircleNode {
	protected: 
		int m_pin;
		int m_sweepDelay;
		Servo* servo;
	public:
		HarvbotArmServoNode(int nodeType, int pin, float pos, float minPos, float maxPos);
		~HarvbotArmServoNode();
		float write(float pos);
		int getSweepDelay();
		void setSweepDelay(int delay);
};

#endif /* HarvbotArmServoNode_H_ */