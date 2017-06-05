#ifndef HarvbotArmAccelStepperScrewNode_H_
#define HarvbotArmAccelStepperScrewNode_H_

#include <AccelStepper.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmConstants.h>

class  HarvbotArmAccelStepperScrewNode : public HarvbotArmScrewNode {
	private:
		AccelStepper* stepper;
	public:
		HarvbotArmAccelStepperScrewNode(
			int nodeType, 
			int pinDir, 
			int pinStep, 
			float pos, 
			int maxStepsCount, 
			int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION, 
			int reductorGear=1);
		~HarvbotArmAccelStepperScrewNode();
		float rotate(float steps);
		void setSpeed(int speed);
};

#endif /* HarvbotArmAccelStepperScrewNode_H_ */