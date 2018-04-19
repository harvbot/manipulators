#include <wiringPi.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include "HarvbotTerminableStepper.h"
#include "Stoppers/HarvbotTerminalStopper.h"

HarvbotTerminableStepper::HarvbotTerminableStepper(uint8_t stepPin, uint8_t dirPin, uint8_t terminalPin) : HarvbotStepper(stepPin, dirPin)
{
	_stopper = NULL;
	if (terminalPin > 0)
	{
		_stopper = new HarvbotTerminalStopper(terminalPin, false);
	}
}

HarvbotTerminableStepper::~HarvbotTerminableStepper()
{
	if (_stopper != NULL)
	{
		delete _stopper;
	}
}

void HarvbotTerminableStepper::step(long step)
{
	if (_stopper != NULL)
	{
		if (_stopper->isTerminated())
		{
			if (_stopper->blockedDirection() == direction())
			{
				stop();
				moveTo(currentPosition());
				return;
			}
		}
	}

	HarvbotStepper::step(step);
}

bool HarvbotTerminableStepper::isTerminated()
{
	return _stopper->isTerminated();
}

void HarvbotTerminableStepper::runTillTerminal(bool direction)
{
	do 
	{
		move(direction ? 1 : -1);
		run();
	}
	while (!isTerminated());
}