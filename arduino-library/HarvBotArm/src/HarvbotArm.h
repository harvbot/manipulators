#ifndef HarvbotArm_H_
#define HarvbotArm_H_

#include <Arduino.h>
#include <HarvbotArmNode.h>
#include <HarvbotArmServoNode.h>

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
		virtual HarvbotArmNode* getBedplate();
		virtual HarvbotArmNode* getShoulder();
		virtual HarvbotArmNode* getElbow();
		virtual HarvbotArmNode* getNodeByType(int type);
};

#endif /* HarvbotArm_H_ */
