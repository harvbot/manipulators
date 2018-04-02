#include "HarvbotArmNode.h"
#include "HarvbotArmCircleNode.h"
#include "../HarvbotArmConstants.h"

HarvbotArmCircleNode::HarvbotArmCircleNode(HarvbotArmNodeIdentifiers identifier, float pos, float minPos, float maxPos) 
	: HarvbotArmNode(identifier)
{
	m_pos = pos;
	m_minPos = minPos;
	m_maxPos = maxPos;
}

HarvbotArmCircleNode::~HarvbotArmCircleNode(){
}

HarvbotArmNodeTypes HarvbotArmCircleNode::getType()
{
	return Circle;
}

float HarvbotArmCircleNode::currentPosition() {
	return m_pos;
}

float HarvbotArmCircleNode::move(float pos) {

	if (m_minPos > pos)
	{
		pos = m_minPos;
	}

	if (m_maxPos < pos)
	{
		pos = m_maxPos;
	}

	if (m_pos != pos)
	{
		m_pos = pos;
	}
}