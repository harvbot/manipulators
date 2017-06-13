#ifndef HarvbotArm1_H_
#define HarvbotArm1_H_

#include <HarvbotArm.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmCircleNode.h>
#include <HarvbotArmScrewNode.h>
#include <HarvbotArmConstants.h>

class HarvbotArm1 : public HarvbotArm {
	public:
		HarvbotArm1(int beadplatePin, int shoulderPin, int elbow, int elbowScrewPin, int handPin, int handScrewPin);

		~HarvbotArm1();

		void goToStartPosition();

		HarvbotArmCircleNode* getElbowScrew();

		HarvbotArmCircleNode* getHand();

		HarvbotArmCircleNode* getHandScrew();
};

#endif /* HarvbotArm1_H_ */
