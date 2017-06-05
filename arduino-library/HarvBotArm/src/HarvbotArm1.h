#ifndef HarvbotArm1_H_
#define HarvbotArm1_H_

#include <HarvbotArm.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmCircleNode.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmServoNode.h>
#include <HarvbotArmConstants.h>

class HarvbotArm1 : public HarvbotArm {
	public:
		HarvbotArm1(HarvbotArmServoNodePins beadplate, 
			HarvbotArmServoNodePins shoulder,
			HarvbotArmServoNodePins elbow,
			HarvbotArmServoNodePins elbowScrew,
			HarvbotArmServoNodePins hand,
			HarvbotArmServoNodePins handScrew);
		~HarvbotArm1();
		HarvbotArmCircleNode* getElbowScrew();
		HarvbotArmCircleNode* getHand();
		HarvbotArmCircleNode* getHandScrew();
};

#endif /* HarvbotArm1_H_ */
