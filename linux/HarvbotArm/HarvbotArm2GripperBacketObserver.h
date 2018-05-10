#pragma once
#include "HarvbotArm2.h"
#include "HarvbotGripperObserver.h"
#include "Cameras/HarvbotFrame.h"

class HarvbotArm2GripperBacketObserver : HarvbotGripperObserver
{
public:
	HarvbotArm2GripperBacketObserver(HarvbotArm2* arm2);
	~HarvbotArm2GripperBacketObserver();

	void ObjectPicked();

	void ProcessedFrame(HarvbotFrame* frame);

	HarvbotFrame* latestFrame();
private:
	HarvbotArm2 * _arm2;

	HarvbotFrame* _frame;
};

