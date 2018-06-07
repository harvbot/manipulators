#ifndef HarvbotGripperObserver_H_
#define HarvbotGripperObserver_H_

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

	virtual void NoObjectDetected(HarvbotFrame* frame) = 0;
private:
	HarvbotArm * _arm;
};

#endif /* HarvbotGripperObserver_H_ */