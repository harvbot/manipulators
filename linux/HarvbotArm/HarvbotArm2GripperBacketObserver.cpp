#include "HarvbotArm2.h"
#include "HarvbotGripperObserver.h"
#include "HarvbotArm2GripperBacketObserver.h"

HarvbotArm2GripperBacketObserver::HarvbotArm2GripperBacketObserver(HarvbotArm2 * arm2) : HarvbotGripperObserver(arm2)
{
	_arm2 = arm2;
}

HarvbotArm2GripperBacketObserver::~HarvbotArm2GripperBacketObserver()
{
}

void HarvbotArm2GripperBacketObserver::ObjectPicked()
{
	_arm2->getShoulder()->moveTo(radians(90));
	_arm2->getElbow()->moveTo(radians(0));
	_arm2->getBedplate()->moveTo(radians(-180));
	_arm2->runToPosition();

	_arm2->getClaw()->open();

	_arm2->getBedplate()->moveTo(0);
	_arm2->runToPosition();
	
}