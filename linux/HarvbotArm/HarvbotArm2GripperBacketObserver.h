#pragma once
#include "HarvbotArm2.h"
#include "HarvbotGripperObserver.h"

class HarvbotArm2GripperBacketObserver : HarvbotGripperObserver
{
public:
	HarvbotArm2GripperBacketObserver(HarvbotArm2* arm2);
	~HarvbotArm2GripperBacketObserver();

	void ObjectPicked();
private:
	HarvbotArm2 * _arm2;
};

