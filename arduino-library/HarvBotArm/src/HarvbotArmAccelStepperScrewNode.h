#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

#ifndef HarvbotArmAccelStepperScrewNode_H_
#define HarvbotArmAccelStepperScrewNode_H_

#include <Arduino.h>
#include <AccelStepper.h>
#include <HarvbotArmScrewNode.h>

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
#endif