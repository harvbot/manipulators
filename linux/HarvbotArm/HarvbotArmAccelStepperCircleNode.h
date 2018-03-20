#ifndef HarvbotArmAccelStepperCircleNode_H_
#define HarvbotArmAccelStepperCircleNode_H_

#include "AccelStepper/AccelStepper.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"

class HarvbotArmAccelStepperCircleNode : public HarvbotArmCircleNode {
	protected:
		int m_maxStepCount;
		int m_reductorGear; 
		int m_speed;
		AccelStepper* stepper;
	public:
		HarvbotArmAccelStepperCircleNode(
			HarvbotArmNodeIdentifiers identifier, 
			int pinStep,
			int pinDir, 
			float pos, 
			float minPos, 
			float maxPos, 
			int maxStepCount, 
			int reductorGear=1);
		~HarvbotArmAccelStepperCircleNode();
		
		/**
			Sets the current angle.
		*/
		float write(float pos);

		int getSpeed();

		void setSpeed(int speed);

		HarvbotNodeStatuses getStatus();
};

#endif /* HarvbotArmAccelStepperCircleNode_H_ */