#pragma once
#include "HarvbotArm.h"

class HarvbotGripperObserver
{
public:
	HarvbotGripperObserver(HarvbotArm* arm);
	~HarvbotGripperObserver();

	HarvbotArm* arm();

	virtual void ObjectPicked() = 0;
private:
	HarvbotArm * _arm;
};

