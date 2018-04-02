#include "HarvbotArm.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmCircleNode.h"

HarvbotArm::HarvbotArm(HarvbotArmTypes armType) 
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

HarvbotArmTypes HarvbotArm::getType()
{
	return this->armType;
}

HarvbotArmCircleNode* HarvbotArm::getBedplate()
{
	return (HarvbotArmCircleNode*)this->getNodeByType(Bedplate);
}

HarvbotArmCircleNode* HarvbotArm::getShoulder()
{
	return (HarvbotArmCircleNode*)this->getNodeByType(Shoulder);
}

HarvbotArmCircleNode* HarvbotArm::getElbow()
{
	return (HarvbotArmCircleNode*)this->getNodeByType(Elbow);
}

HarvbotArmNode* HarvbotArm::getNodeByType(HarvbotArmNodeIdentifiers node)
{
	for(int i=0;i<nodesCount;i++)
	{
		if(this->nodes[i]->getIdentifier() == node)
		{
			return this->nodes[i];
		}
	}

	return NULL;
}

HarvbotNodeStatuses HarvbotArm::getStatus()
{
	for(int i=0;i<nodesCount;i++)
	{
		if(this->nodes[i]->getStatus() != Ready)
		{
			return InProcess;
		}
	}

	return Ready;
}

bool HarvbotArm::run()
{
	bool result = false;
	for (int i = 0; i < nodesCount; i++)
	{
		result = result || this->nodes[i]->run();
	}
	return result;
}

void HarvbotArm::runToPosition()
{
	while (run())
		;
}