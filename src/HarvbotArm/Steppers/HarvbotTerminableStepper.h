#ifndef HarvbotTerminableStepper_h
#define HarvbotTerminableStepper_h

#include "Stoppers/HarvbotStepperStopper.h"
#include "HarvbotStepper.h"

class HarvbotTerminableStepper : public HarvbotStepper
{
public:
	HarvbotTerminableStepper(uint8_t stepPin, uint8_t dirPin, uint8_t terminalPin = 0);
	~HarvbotTerminableStepper();
	
	void runTillTerminal(bool direction);

	bool isTerminated();
protected:
	void step(long step);
	
private:

	HarvbotStepperStopper* _stopper;
};

#endif
