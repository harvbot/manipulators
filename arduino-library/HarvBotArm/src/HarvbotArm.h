#ifndef HarvbotArm_H_
#define HarvbotArm_H_

#include <Arduino.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmCircleNode.h>
#include <HarvbotArmScrewNode.h>

#ifndef HARVBOT_ARM_TYPE_1
#define HARVBOT_ARM_TYPE_1 1
#endif

#ifndef HARVBOT_ARM_TYPE_2
#define HARVBOT_ARM_TYPE_2 2
#endif

#ifndef HARVBOT_ARM_TYPE_3
#define HARVBOT_ARM_TYPE_3 3
#endif

class HarvbotArm {
	private: 
		int armType;
	protected:
		int nodesCount;
		HarvbotArmNode** nodes;
	public:
		HarvbotArm(int armType);
		~HarvbotArm();
		int getType();
		virtual HarvbotArmCircleNode* getBedplate();
		virtual HarvbotArmCircleNode* getShoulder();
		virtual HarvbotArmCircleNode* getElbow();
		virtual HarvbotArmNode* getNodeByType(int nodeType);
};

#endif /* HarvbotArm_H_ */
