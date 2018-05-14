#ifndef HarvbotArmStepperLinearNode_H_
#define HarvbotArmStepperLinearNode_H_

#include "../Steppers/HarvbotTerminableStepper.h"
#include "../HarvbotArmConstants.h"
#include "HarvbotArmLinearNode.h"

class  HarvbotArmStepperLinearNode : public HarvbotArmLinearNode {
	private:
		HarvbotTerminableStepper* stepper;
	public:
		HarvbotArmStepperLinearNode(
			HarvbotArmNodeIdentifiers identifier, 
			uint8_t pinStep,
			uint8_t pinDir,
			uint8_t pinTerminal,
			unsigned int stepperFrequency,
			float pos, 
			unsigned int maxStepsCount,
			unsigned int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION,
			uint8_t reductorGear=1);
			
		~HarvbotArmStepperLinearNode();

		float rotate(float steps);

		HarvbotNodeStatuses getStatus();

		void goToStartPosition();

		bool run();

		void runToPosition();

		void stop();

		float distranceToGo();

		unsigned int accelerationPercent();

		void setAccelerationPercent(unsigned int percent);
};

#endif /* HarvbotArmStepperLinearNode_H_ */