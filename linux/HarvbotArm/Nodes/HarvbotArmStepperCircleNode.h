#ifndef HarvbotArmStepperCircleNode_H_
#define HarvbotArmStepperCircleNode_H_

#include "../Steppers/HarvbotTerminableStepper.h"
#include "../HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"

class HarvbotArmStepperCircleNode : public HarvbotArmCircleNode {
	protected:
		int m_maxStepCount;
		int m_reductorGear; 
		HarvbotTerminableStepper* stepper;
	public:
		HarvbotArmStepperCircleNode(
			HarvbotArmNodeIdentifiers identifier, 
			uint8_t pinStep,
			uint8_t pinDir,
			uint8_t pinTerminal,
			unsigned int stepperFrequency,
			float pos, 
			float minPos, 
			float maxPos, 
			unsigned int maxStepCount,
			uint8_t reductorGear=1);
		~HarvbotArmStepperCircleNode();
		
		/**
			Sets the current angle.
		*/
		float move(float pos);

		HarvbotNodeStatuses getStatus();

		bool run();

		void runToPosition();

		void goToStartPosition();
	private:
		/**
		Gets the angle per step.
		*/
		float getAnglePerStep();
};

#endif /* HarvbotArmStepperCircleNode_H_ */