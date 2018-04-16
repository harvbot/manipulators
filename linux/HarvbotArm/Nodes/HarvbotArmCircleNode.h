#ifndef HarvbotArmCircleNode_H_
#define HarvbotArmCircleNode_H_

#include "HarvbotArmNode.h"
#include "../HarvbotArmConstants.h"

class HarvbotArmCircleNode : public HarvbotArmNode {
	protected:
		float m_pos;
		float m_minPos;
		float m_maxPos;
	public:
		HarvbotArmCircleNode(HarvbotArmNodeIdentifiers identifier, float pos, float minPos, float maxPos);
		
		~HarvbotArmCircleNode();

		HarvbotArmNodeTypes getType();

		virtual float getMinPos();

		virtual float getMaxPos();

		virtual float currentPosition();

		virtual float move(float pos);

		virtual float moveTo(float pos);
	protected:
		virtual float setCurrentPosition(float pos);
};

#endif /* HarvbotArmCircleNode_H_ */