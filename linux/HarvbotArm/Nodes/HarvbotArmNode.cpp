#include "HarvbotArmNode.h"
#include "../HarvbotArmConstants.h"

HarvbotArmNode::HarvbotArmNode(HarvbotArmNodeIdentifiers identifier) {
	this->m_identifier = identifier;
}

HarvbotArmNode::~HarvbotArmNode() {
}

HarvbotArmNodeIdentifiers HarvbotArmNode::getIdentifier() {
	return this->m_identifier;
}