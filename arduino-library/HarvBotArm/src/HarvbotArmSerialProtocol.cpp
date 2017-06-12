#include <Arduino.h>
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

String HarvbotArmSerialProtocol::readRequest()
{
	return Serial.readString();
}

void HarvbotArmSerialProtocol::writeResponse(String response)
{
	Serial.println(response);
}