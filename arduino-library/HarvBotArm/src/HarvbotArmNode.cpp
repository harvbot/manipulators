#include "HarvbotArmNode.h"

HarvbotArmNode::HarvbotArmNode(int type) {
	this->type = type;
}

HarvbotArmNode::~HarvbotArmNode() {
}

int HarvbotArmNode::getType() {
	return this->type;
}