#pragma once
class HarvbotStepperStopper
{
public:
	HarvbotStepperStopper();
	~HarvbotStepperStopper();

	virtual bool isTerminated() = 0;

	virtual bool blockedDirection() = 0;
};

