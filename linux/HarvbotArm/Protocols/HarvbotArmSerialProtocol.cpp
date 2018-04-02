#include <string>
#include "../HarvbotArm.h"
#include "../Nodes/HarvbotArmNode.h"
#include "../Nodes/HarvbotArmCircleNode.h"
#include "../Nodes/HarvbotArmScrewNode.h"
#include "HarvbotArmProtocol.h"
#include "HarvbotArmSerialProtocol.h"

HarvbotArmSerialProtocol::HarvbotArmSerialProtocol() 
	: HarvbotArmProtocol() 
{
}

HarvbotArmSerialProtocol::~HarvbotArmSerialProtocol() {
}

std::string HarvbotArmSerialProtocol::readRequest()
{
	return std::string();
}

void HarvbotArmSerialProtocol::writeResponse(std::string response)
{
}