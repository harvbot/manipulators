#ifndef HarvbotArmCircleNode_H_
#define HarvbotArmCircleNode_H_

#include <HarvbotArmNode.h>
#include <HarvbotArmConstants.h>

class HarvbotArmCircleNode : public HarvbotArmNode {
	protected:
		float m_pos;
		float m_minPos;
		float m_maxPos;
	public:
		HarvbotArmCircleNode(int nodeType, float pos, float minPos, float maxPos);
		~HarvbotArmCircleNode();
		int getType();
		virtual float read();
		virtual float write(float pos);
};

#endif /* HarvbotArmCircleNode_H_ */