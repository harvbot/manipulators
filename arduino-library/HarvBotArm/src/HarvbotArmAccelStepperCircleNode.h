#ifndef HarvbotArmAccelStepperCircleNode_H_
#define HarvbotArmAccelStepperCircleNode_H_

#include <Arduino.h>
#include <AccelStepper.h>

#include <HarvbotArmCircleNode.h>

class HarvbotArmAccelStepperCircleNode : public HarvbotArmCircleNode {
	protected: 
		AccelStepper* stepper;
	public:
		HarvbotArmAccelStepperCircleNode(int nodeType, int pinDir, int pinStep, float pos, float minPos, float maxPos);
		~HarvbotArmAccelStepperCircleNode();
		
		/**
			Sets the current angle.
		*/
		float write(float pos);
};

#endif /* HarvbotArmAccelStepperCircleNode_H_ */