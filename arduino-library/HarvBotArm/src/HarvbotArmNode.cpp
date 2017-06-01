#include "HarvbotArmNode.h"

HarvbotArmNode::HarvbotArmNode(int nodeType) {
	this->m_nodeType = nodeType;
}

HarvbotArmNode::~HarvbotArmNode() {
}

int HarvbotArmNode::getNodeType() {
	return this->m_nodeType;
}