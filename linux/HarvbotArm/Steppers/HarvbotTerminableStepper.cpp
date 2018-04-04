#include <wiringPi.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include "HarvbotTerminableStepper.h"

HarvbotTerminableStepper::HarvbotTerminableStepper(uint8_t stepPin, uint8_t dirPin, uint8_t terminalPin) : HarvbotStepper(stepPin, dirPin)
{
	_terminalPin = terminalPin;

	if (_terminalPin > 0)
	{
		pinMode(_terminalPin, INPUT);
	}
}

void HarvbotTerminableStepper::step(long step)
{
	if (_terminalPin != 0)
	{
		int endVal = digitalRead(_terminalPin);
		if (endVal == LOW)
		{
			if (_terminalPressed)
			{
				if (_terminalPressedDir == direction())
				{
					stop();
					move(currentPosition());
					return;
				}
			}
			else
			{
				// Stop movement
				moveTo(currentPosition());
				_terminalPressed = true;
				_terminalPressedDir = direction();
				return;
			}

		}
		else
		{
			_terminalPressed = false;
		}
	}

	HarvbotStepper::step(step);
}

bool HarvbotTerminableStepper::isTerminated()
{
	return _terminalPressed;
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