#include <Arduino.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>

#ifndef HarvbotArm1_H_

#ifndef SERVO_BEDPLATE_PIN
#define SERVO_BEDPLATE_PIN 2
#endif

#ifndef SERVO_SHOULDER_PIN
#define SERVO_SHOULDER_PIN 3
#endif

#ifndef SERVO_ELBOW_PIN
#define SERVO_ELBOW_PIN 4
#endif

#ifndef SERVO_ELBOW_SCREW_PIN
#define SERVO_ELBOW_SCREW_PIN 5
#endif

#ifndef SERVO_HAND_PIN
#define SERVO_HAND_PIN 6
#endif

#ifndef SERVO_HAND_SCREW_PIN
#define SERVO_HAND_SCREW_PIN 7
#endif

class HarvbotArm1 {
	private:
		HarvbotArmServoNode* bedplateNode;
		HarvbotArmServoNode* shoulderNode;
		HarvbotArmServoNode* elbowNode;
		HarvbotArmServoNode* elbowScrewNode;
		HarvbotArmServoNode* handNode;
		HarvbotArmServoNode* handScrewNode;
	public:
		HarvbotArm1();
		~HarvbotArm1();
		void setup();
		HarvbotArmServoNode* getBedplate();
		HarvbotArmServoNode* getShoulder();
		HarvbotArmServoNode* getElbow();
		HarvbotArmServoNode* getElbowScrew();
		HarvbotArmServoNode* getHand();
		HarvbotArmServoNode* getHandScrew();
};

#endif /* HarvbotArm1_H_ */
