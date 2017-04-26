#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

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
#endif