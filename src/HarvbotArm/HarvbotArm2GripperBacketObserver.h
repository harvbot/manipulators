#ifndef HarvbotArm2GripperBacketObserver_H_
#define HarvbotArm2GripperBacketObserver_H_

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

#endif /* HarvbotArm2GripperBacketObserver_H_ */