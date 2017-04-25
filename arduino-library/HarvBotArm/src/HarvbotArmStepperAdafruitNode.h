#ifndef HarvbotArmStepperAdafruitNode_H_
#define HarvbotArmStepperAdafruitNode_H_

#include <Arduino.h>
#include <AFMotor.h>
#include <HarvbotArmStepperNode.h>

class  HarvbotArmStepperAdafruitNode : public HarvbotArmStepperNode {
	private:
		AF_Stepper* stepper;
	public:
		HarvbotArmStepperAdafruitNode(int type, int adafruitShieldPort, int pos, int maxStepsCount, int maxFullRotaionCount);
		~HarvbotArmStepperAdafruitNode();
		void rotate(int steps);
		void setSpeed(int speed);
};

#endif /* HarvbotArmStepperAdafruitNode_H_ */