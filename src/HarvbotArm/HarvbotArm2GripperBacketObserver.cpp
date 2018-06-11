#include "HarvbotArm2.h"
#include "HarvbotGripperObserver.h"
#include "HarvbotArm2GripperBacketObserver.h"

HarvbotArm2GripperBacketObserver::HarvbotArm2GripperBacketObserver(HarvbotArm2 * arm2) : HarvbotGripperObserver(arm2)
{
	_arm2 = arm2;
	_frame = NULL;
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

void HarvbotArm2GripperBacketObserver::ProcessedFrame(HarvbotFrame* frame)
{
	_frame = frame;
}

void HarvbotArm2GripperBacketObserver::NoObjectDetected(HarvbotFrame* frame)
{
	if (_arm2->getStatus() == Ready)
	{
		/*if (_arm2->getShoulder()->currentPosition() != 120)
		{
			_arm2->getShoulder()->moveTo(radians(120));
		}

		if (_arm2->getElbow()->currentPosition() != 45)
		{
			_arm2->getElbow()->moveTo(radians(45));
		}*/
	}
}

HarvbotFrame* HarvbotArm2GripperBacketObserver::latestFrame()
{
	return _frame;
}