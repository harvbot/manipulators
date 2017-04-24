#include "HarvbotArm.h"
#include "HarvbotArmNode.h"

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

HarvbotArmNode* HarvbotArm::getBedplate()
{
	return this->getNodeByType(HARVBOT_ARM_BEDPLATE_NODE);
}

HarvbotArmNode* HarvbotArm::getShoulder()
{
	return this->getNodeByType(HARVBOT_ARM_SHOULDER_NODE);
}

HarvbotArmNode* HarvbotArm::getElbow()
{
	return this->getNodeByType(HARVBOT_ARM_ELBOW_NODE);
}

HarvbotArmNode* HarvbotArm::getNodeByType(int type)
{
	for(int i=0;i<nodesCount;i++)
	{
		if(this->nodes[i]->getType() == type)
		{
			return this->nodes[i];
		}
	}

	return NULL;
}