#pragma once
#include "Cameras/HarvbotFrame.h"
#include "HarvbotArm.h"

class HarvbotGripperObserver
{
public:
	HarvbotGripperObserver(HarvbotArm* arm);
	~HarvbotGripperObserver();

	HarvbotArm* arm();

	virtual void ObjectPicked() = 0;

	virtual void ProcessedFrame(HarvbotFrame* frame) = 0;
private:
	HarvbotArm * _arm;
};

