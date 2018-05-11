#include "HarvbotGripperObserver.h"

HarvbotGripperObserver::HarvbotGripperObserver(HarvbotArm* arm)
{
	_arm = arm;
}

HarvbotGripperObserver::~HarvbotGripperObserver()
{
}

HarvbotArm* HarvbotGripperObserver::arm()
{
	return _arm;
}