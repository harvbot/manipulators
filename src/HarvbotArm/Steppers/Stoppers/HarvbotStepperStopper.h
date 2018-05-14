#ifndef HarvbotStepperStopper_H_
#define HarvbotStepperStopper_H_

class HarvbotStepperStopper
{
public:
	HarvbotStepperStopper();
	~HarvbotStepperStopper();

	virtual bool isTerminated() = 0;

	virtual bool blockedDirection() = 0;
};

#endif /* HarvbotStepperStopper_H_ */