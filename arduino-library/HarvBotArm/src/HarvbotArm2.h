#ifndef HarvbotArm2_H_
#define HarvbotArm2_H_

#include <Arduino.h>
#include <HarvbotArm.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmStepperNode.h>

class HarvbotArm2 : public HarvbotArm {
	public:
		HarvbotArm2(HarvbotArmServoNodePins beadplate, 
			HarvbotArmServoNodePins shoulder,
			HarvbotArmServoNodePins elbow,
			HarvbotArmStepperNode* claw);
		~HarvbotArm2();
		HarvbotArmStepperNode* getClaw();
};

#endif /* HarvbotArm2_H_ */
