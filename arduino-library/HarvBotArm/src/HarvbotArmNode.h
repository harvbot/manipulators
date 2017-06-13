#ifndef HarvbotArmNode_H_
#define HarvbotArmNode_H_

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
		virtual int getType() = 0;	

		// Gets current node status.
		virtual int getStatus() = 0;
};

#endif /* HarvbotArmNode_H_ */