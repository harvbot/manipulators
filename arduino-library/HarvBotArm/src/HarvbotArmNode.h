#ifndef HarvbotArmNode_H_
#define HarvbotArmNode_H_

#include <Arduino.h>

// Arm nodes.
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

#ifndef HARVBOT_ARM_CLAW_MAX_FULL_ROTATION
#define HARVBOT_ARM_CLAW_MAX_FULL_ROTATION 28
#endif

// Nodes types
#ifndef HARVBOT_ARM_CIRCLE_NODE_TYPE
#define HARVBOT_ARM_CIRCLE_NODE_TYPE 1
#endif

#ifndef HARVBOT_ARM_SCREW_NODE_TYPE
#define HARVBOT_ARM_SCREW_NODE_TYPE 2
#endif

class HarvbotArmNode {
	private:

		// Stores node type.
		int m_nodeType;
	public:

		// Initialzies a new instance.
		HarvbotArmNode(int nodeType);

		// Release all resouces.
		~HarvbotArmNode();

		// Gets the node identifier. For instance Elbow.
		virtual int getNodeType();

		// Gets the node type: circle or screw.
		virtual int getType();		
};

#endif /* HarvbotArmNode_H_ */