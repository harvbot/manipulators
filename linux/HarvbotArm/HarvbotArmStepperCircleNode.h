#ifndef HarvbotArmStepperCircleNode_H_
#define HarvbotArmStepperCircleNode_H_

#include "Steppers/HarvbotTerminableStepper.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"

class HarvbotArmStepperCircleNode : public HarvbotArmCircleNode {
	protected:
		int m_maxStepCount;
		int m_reductorGear; 
		int m_speed;
		HarvbotTerminableStepper* stepper;
	public:
		HarvbotArmStepperCircleNode(
			HarvbotArmNodeIdentifiers identifier, 
			uint8_t pinStep,
			uint8_t pinDir,
			uint8_t pinTerminal,
			float pos, 
			float minPos, 
			float maxPos, 
			unsigned int maxStepCount,
			uint8_t reductorGear=1);
		~HarvbotArmStepperCircleNode();
		
		/**
			Sets the current angle.
		*/
		float write(float pos);

		int getSpeed();

		void setSpeed(int speed);

		HarvbotNodeStatuses getStatus();
};

#endif /* HarvbotArmStepperCircleNode_H_ */