#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega48__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__PIC32MX__)

#ifndef HarvbotArmAFMotorScrewNode_H_
#define HarvbotArmAFMotorScrewNode_H_

#include <Arduino.h>
#include <AFMotor.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmConstants.h>

class  HarvbotArmAFMotorScrewNode : public HarvbotArmScrewNode {
	private:
		AF_Stepper* stepper;
	public:
		HarvbotArmAFMotorScrewNode(
			int nodeType, 
			int adafruitShieldPort, 
			float pos, 
			int maxStepsCount, 
			int maxFullRotaionCount=HARVBOT_ARM_CLAW_MAX_FULL_ROTATION);
		~HarvbotArmAFMotorScrewNode();
		float rotate(float steps);
		void setSpeed(int speed);
};

#endif /* HarvbotArmAFMotorScrewNode_H_ */
#endif