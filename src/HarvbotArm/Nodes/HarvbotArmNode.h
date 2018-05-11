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

		virtual void runToPosition() = 0;

		/**
		Moves screw to start position.
		*/
		virtual void goToStartPosition() = 0;

		virtual void stop() = 0;

		virtual float distranceToGo() = 0;
};

#endif /* HarvbotArmNode_H_ */