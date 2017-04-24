#ifndef HarvbotArm1_H_
#define HarvbotArm1_H_

#include <Arduino.h>
#include <HarvbotArm.h>
#include <HarvbotArmNode.h>

class HarvbotArm1 : public HarvbotArm {
	public:
		HarvbotArm1(HarvbotArmServoNodePins beadplate, 
			HarvbotArmServoNodePins shoulder,
			HarvbotArmServoNodePins elbow,
			HarvbotArmServoNodePins elbowScrew,
			HarvbotArmServoNodePins hand,
			HarvbotArmServoNodePins handScrew);
		~HarvbotArm1();
		HarvbotArmNode* getElbowScrew();
		HarvbotArmNode* getHand();
		HarvbotArmNode* getHandScrew();
};

#endif /* HarvbotArm1_H_ */
