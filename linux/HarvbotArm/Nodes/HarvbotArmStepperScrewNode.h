#ifndef HarvbotArmStepperScrewNode_H_
#define HarvbotArmStepperScrewNode_H_

#include "../Steppers/HarvbotTerminableStepper.h"
#include "../HarvbotArmConstants.h"
#include "HarvbotArmScrewNode.h"

class  HarvbotArmStepperScrewNode : public HarvbotArmScrewNode {
	private:
		HarvbotTerminableStepper* stepper;
	public:
		HarvbotArmStepperScrewNode(
			HarvbotArmNodeIdentifiers identifier, 
			uint8_t pinStep,
			uint8_t pinDir,
			uint8_t pinTerminal,
			unsigned int stepperFrequency,
			float pos, 
			unsigned int maxStepsCount,
			unsigned int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION,
			uint8_t reductorGear=1);
			
		~HarvbotArmStepperScrewNode();

		float rotate(float steps);

		HarvbotNodeStatuses getStatus();

		void goToStartPosition();

		bool run();

		void runToPosition();

		void stop();

		float distranceToGo();
};

#endif /* HarvbotArmStepperScrewNode_H_ */