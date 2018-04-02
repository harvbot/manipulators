#ifndef HarvbotArmNode_H_
#define HarvbotArmNode_H_

#include "../HarvbotArmConstants.h"

class HarvbotArmNode {
	private:

		// Stores node type.
		HarvbotArmNodeIdentifiers m_identifier;
	public:

		// Initialzies a new instance.
		HarvbotArmNode(HarvbotArmNodeIdentifiers identifier);

		// Release all resouces.
		~HarvbotArmNode();

		// Gets the node identifier. For instance Elbow.
		HarvbotArmNodeIdentifiers getIdentifier();

		// Gets the node type: circle or screw.
		virtual HarvbotArmNodeTypes getType() = 0;	

		// Gets current node status.
		virtual HarvbotNodeStatuses getStatus() = 0;

		virtual bool run();

		virtual void runToPosition();
};

#endif /* HarvbotArmNode_H_ */