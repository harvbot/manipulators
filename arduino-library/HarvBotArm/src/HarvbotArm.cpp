#include "HarvbotArm.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"

HarvbotArm::HarvbotArm(int armType) 
{
	this->armType = armType;
}

HarvbotArm::~HarvbotArm() 
{
	if(this->nodes != NULL)
	{
		delete this->nodes;
	}
}

int HarvbotArm::getType()
{
	return this->armType;
}

HarvbotArmCircleNode* HarvbotArm::getBedplate()
{
	return this->getNodeByType(HARVBOT_ARM_BEDPLATE_NODE);
}

HarvbotArmCircleNode* HarvbotArm::getShoulder()
{
	return this->getNodeByType(HARVBOT_ARM_SHOULDER_NODE);
}

HarvbotArmCircleNode* HarvbotArm::getElbow()
{
	return this->getNodeByType(HARVBOT_ARM_ELBOW_NODE);
}

HarvbotArmNode* HarvbotArm::getNodeByType(int nodeType)
{
	for(int i=0;i<nodesCount;i++)
	{
		if(this->nodes[i]->getNodeType() == nodeType)
		{
			return this->nodes[i];
		}
	}

	return NULL;
}

int HarvbotArm::getStatus()
{
	for(int i=0;i<nodesCount;i++)
	{
		if(this->nodes[i]->getStatus() != HARVBOT_NODE_STATUS_READY)
		{
			return HARVBOT_NODE_STATUS_INPROCESS;
		}
	}

	return HARVBOT_NODE_STATUS_READY;
}

void HarvbotArm::gotToStartPosition()
{
	// empty for now.
}