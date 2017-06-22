#ifndef HarvbotArmServoNode_H_
#define HarvbotArmServoNode_H_

#include <Servo.h>
#include <HarvbotArmConstants.h>
#include <HarvbotArmCircleNode.h>

class HarvbotArmServoNode : public HarvbotArmCircleNode {
	protected: 
		int m_pin;
		int m_sweepDelay;
		HarvbotNodeStatuses m_status;
		Servo* servo;
	public:
		HarvbotArmServoNode(HarvbotArmNodeIdentifiers identifier, int pin, float pos, float minPos, float maxPos);

		~HarvbotArmServoNode();

		float write(float pos);

		int getSweepDelay();

		void setSweepDelay(int delay);

		HarvbotNodeStatuses getStatus();
};

#endif /* HarvbotArmServoNode_H_ */