#ifndef HarvbotTerminalStopper_H_
#define HarvbotTerminalStopper_H_

#include "HarvbotStepperStopper.h"

class HarvbotTerminalStopper: public HarvbotStepperStopper
{
private:
	// Stores terminal pin.
	int _terminalPin;

	// Stores stepper direction in time of terminal fire.
	bool _blockerDirection;
public:
	HarvbotTerminalStopper(int terminalPin, bool blockerDirection);
	~HarvbotTerminalStopper();

	bool isTerminated();

	bool blockedDirection();
};

#endif /* HarvbotTerminalStopper_H_ */