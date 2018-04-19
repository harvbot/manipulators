#include "HarvbotTerminalStopper.h"
#include <wiringPi.h>

HarvbotTerminalStopper::HarvbotTerminalStopper(int terminalPin, bool blockerDirection)
{
	_terminalPin = terminalPin;
	_blockerDirection = blockerDirection;

	if (_terminalPin > 0)
	{
		pinMode(_terminalPin, INPUT);
	}
}

HarvbotTerminalStopper::~HarvbotTerminalStopper()
{
}

bool HarvbotTerminalStopper::isTerminated()
{
	int endVal = digitalRead(_terminalPin);
	return endVal == LOW;
}

bool HarvbotTerminalStopper::blockedDirection()
{
	return _blockerDirection;
}