#include <string>
#include "HarvbotArm.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmScrewNode.h"
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