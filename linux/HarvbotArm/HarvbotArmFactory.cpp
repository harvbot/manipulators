#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "HarvbotArmConstants.h"
#include "HarvbotArmFactory.h"

HarvbotArmFactory::HarvbotArmFactory() {
}

HarvbotArm2* HarvbotArmFactory::CreateArm2()
{
	return new HarvbotArm2();
}