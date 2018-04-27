#include "HarvbotArm2Gripper.h"

HarvbotArm2Gripper::HarvbotArm2Gripper(HarvbotRecognizer* recognizer) : HarvbotArmGripper(recognizer)
{
	_arm = new HarvbotArm2();
	_visualizer = new HarvbotArm2StateVisualizer(_arm);
	_rangefinder = new HarvbotLaserRangefinder("/dev/ttyUSB0", 9600);

	_measurementThread = NULL;
	_measurementLocker = new mutex();

	_movementThread = NULL;
	_movementLocker = new mutex();
}

HarvbotArm2Gripper::~HarvbotArm2Gripper()
{
	stopRangefinderMeasurement();

	delete _rangefinder;
	delete _visualizer;
	delete _arm;
	delete _measurementThread;
	delete _measurementLocker;
}

void HarvbotArm2Gripper::startRangefinderMeasurement()
{
	stopRangefinderMeasurement();
	this->getRangefinder()->startContinuous();
	_measurementRun = true;
	_measurementThread = new thread(measurementThreadFunc);
	_measurementThread->detach();
}

void HarvbotArm2Gripper::stopRangefinderMeasurement()
{
	_measurementLocker->lock();
	_measurementRun = false;
	_measurementLocker->unlock();
	this->getRangefinder()->stopContinuous();
}

void HarvbotArm2Gripper::startMovementProcessing()
{
	stopMovementProcessing();
	_movementRun = true;
	_movementThread = new thread(movementThreadFunc);
	_movementThread->detach();
}

void HarvbotArm2Gripper::stopMovementProcessing()
{
	_movementLocker->lock();
	_movementRun = false;
	_movementLocker->unlock();
}

HarvbotArm* HarvbotArm2Gripper::getArm()
{
	return _arm;
}

HarvbotCamera* HarvbotArm2Gripper::getCamera()
{
	return NULL;
}

HarvbotRangefinder* HarvbotArm2Gripper::getRangefinder()
{
	return _rangefinder;
}

unsigned int HarvbotArm2Gripper::getDistanceMillimeters()
{
	return _distanceToObject;
}

void HarvbotArm2Gripper::measurementThreadFunc()
{
	while (true)
	{
		float distanceValue = _rangefinder->readRangeContinuousMillimeters();
		if (distanceValue > 0)
		{
			_distanceToObject = distanceValue;
		}

		_measurementLocker->lock();
		bool dontStop = _measurementRun;
		_measurementLocker->unlock();

		if (!dontStop)
		{
			break;
		}
	}
}

void HarvbotArm2Gripper::movementThreadFunc()
{
	while (true)
	{
		_movementLocker->lock();

		if (_pickInProgress)
		{
			_arm->pickObject(_distanceToObject);
		}
		else
		{
			_arm->runToPosition();
		}

		bool dontStop = _movementRun;
		_movementLocker->unlock();

		if (!dontStop)
		{
			break;
		}
	}
}