#include <algorithm>
#include "HarvbotGripper.h"

HarvbotGripper::HarvbotGripper(HarvbotRecognizer* recognizer)
{
	_recognizer = recognizer;
	observers = vector<HarvbotGripperObserver*>();
}

HarvbotGripper::~HarvbotGripper()
{
}

HarvbotRecognizer* HarvbotGripper::getRecognizer()
{
	return _recognizer;
}

void HarvbotGripper::turnOnVisuaization()
{
	_isVisualizationOn = true;
}

void HarvbotGripper::turnOffVisuaization()
{
	_isVisualizationOn = false;
}

bool HarvbotGripper::isVisualizationOn()
{
	return _isVisualizationOn;
}

void HarvbotGripper::attachObserver(HarvbotGripperObserver* observer)
{
	observers.push_back(observer);
}

void HarvbotGripper::detachObserver(HarvbotGripperObserver* observer)
{
	remove(observers.begin(), observers.end(), observer);
}