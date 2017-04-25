#ifndef HarvbotArmNode_H_
#define HarvbotArmNode_H_

#include <Arduino.h>

#ifndef HARVBOT_ARM_BEDPLATE_NODE
#define HARVBOT_ARM_BEDPLATE_NODE 1
#endif

#ifndef HARVBOT_ARM_SHOULDER_NODE
#define HARVBOT_ARM_SHOULDER_NODE 2
#endif

#ifndef HARVBOT_ARM_ELBOW_NODE
#define HARVBOT_ARM_ELBOW_NODE 3
#endif

#ifndef HARVBOT_ARM_ELBOW_SCREW_NODE
#define HARVBOT_ARM_ELBOW_SCREW_NODE 4
#endif

#ifndef HARVBOT_ARM_HAND_NODE
#define HARVBOT_ARM_HAND_NODE 5
#endif

#ifndef HARVBOT_ARM_HAND_SCREW_NODE
#define HARVBOT_ARM_HAND_SCREW_NODE 6
#endif

#ifndef HARVBOT_ARM_CLAW_NODE
#define HARVBOT_ARM_CLAW_NODE 7
#endif

class HarvbotArmNode {
	private:
		int type;
	public:
		HarvbotArmNode(int type);
		~HarvbotArmNode();
		virtual int getType();		
};

#endif /* HarvbotArmNode_H_ */