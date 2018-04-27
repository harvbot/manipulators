#include "HarvbotGripper.h"

HarvbotGripper::HarvbotGripper(HarvbotRecognizer* recognizer)
{
	_recognizer = recognizer;
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