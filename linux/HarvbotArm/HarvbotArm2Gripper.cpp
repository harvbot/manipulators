#include "HarvbotGripper.h"
#include "HarvbotArm2Gripper.h"
#include "HarvbotGripperObserver.h"
#include "Cameras/HarvbotOpenCvCamera.h"

HarvbotArm2Gripper::HarvbotArm2Gripper(HarvbotRecognizer* recognizer) : HarvbotGripper(recognizer)
{
	_arm = new HarvbotArm2();
	_visualizer = new HarvbotArm2StateVisualizer(_arm);
	_rangefinder = new HarvbotLaserRangefinder("/dev/ttyUSB0", 9600);
	_camera = new HarvbotOpenCvCamera();

	_measurementThread = NULL;
	_measurementLocker = new mutex();

	_movementThread = NULL;
	_movementLocker = new mutex();

	_recognizeThread = NULL;
	_recognizeLocker = new mutex();

	turnOnVisuaization();
}

HarvbotArm2Gripper::~HarvbotArm2Gripper()
{
	stop();

	delete _rangefinder;
	delete _visualizer;
	delete _arm;

	delete _measurementThread;
	delete _measurementLocker;

	delete _movementThread;
	delete _movementLocker;

	delete _recognizeThread;
	delete _recognizeLocker;
}

void HarvbotArm2Gripper::start()
{
	startRangefinderMeasurement();
	startMovementProcessing();
	startRecognition();
}

void HarvbotArm2Gripper::stop()
{
	stopRangefinderMeasurement();
	stopMovementProcessing();
	stopRecognition();
}

void HarvbotArm2Gripper::startRangefinderMeasurement()
{
	this->getRangefinder()->startContinuous();
	_measurementRun = true;
	_measurementThread = new thread([this] { this->measurementThreadFunc(); });
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
	_movementThread = new thread([this] { this->movementThreadFunc(); });
	_movementThread->detach();
}

void HarvbotArm2Gripper::stopMovementProcessing()
{
	_movementLocker->lock();
	_movementRun = false;
	_movementLocker->unlock();
}

void HarvbotArm2Gripper::startRecognition()
{
	stopRecognition();
	_recognizeRun = true;
	_recognizeThread = new thread([this] { this->recognizeThreadFunc(); });
	_recognizeThread->detach();
}

void HarvbotArm2Gripper::stopRecognition()
{
	_recognizeLocker->lock();
	_recognizeRun = false;
	_recognizeLocker->unlock();
}

HarvbotArm* HarvbotArm2Gripper::getArm()
{
	return _arm;
}

HarvbotCamera* HarvbotArm2Gripper::getCamera()
{
	return _camera;
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
		_measurementLocker->lock();
		float distanceValue = _rangefinder->readRangeContinuousMillimeters()-30;
		if (distanceValue > 0)
		{
			_distanceToObject = distanceValue;
			printf("Distance to object: %f\n", distanceValue);
		}
		
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
			if (_arm->pickObject(_distanceToObject))
			{
				for (std::vector<HarvbotGripperObserver*>::iterator it = observers.begin(); it != observers.end(); ++it)
				{
					(*it)->ObjectPicked();
				}
			}
			_pickInProgress = false;
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

void HarvbotArm2Gripper::recognizeThreadFunc()
{
	while (true)
	{
		_recognizeLocker->lock();

		try
		{
			HarvbotCamera* camera = getCamera();
			HarvbotFrame* frame = camera->read();
			HarvbotRect rect;
			rect.empty();
			if (!_pickInProgress)
			{
				rect = getRecognizer()->recognize(frame);
				
				if (rect.width > MIN_CONTOUR_SIZE && rect.height > MIN_CONTOUR_SIZE)
				{
					printf("Recognition on new frame: x=%d, y=%d, width=%d, height=%d\n", rect.x, rect.y, rect.width, rect.height);

					int wholeCenterX = rect.x + rect.width / 2;
					int wholeCenterY = rect.y + rect.height / 2;

					int frameWidth = camera->frameWidth();
					int frameHeight = camera->frameHeight();

					float diffCenterX = wholeCenterX - frameWidth / 2;
					float moveAngleX = 0;

					if (diffCenterX < -CENTERING_THRESHOLD)
					{
						moveAngleX = radians(0.5);
					}
					if (diffCenterX > CENTERING_THRESHOLD)
					{
						moveAngleX = radians(-0.5);
					}

					moveAngleX = moveAngleX * fabs(diffCenterX) / (CENTERING_THRESHOLD * 5.0f);

					float diffCenterY = wholeCenterY - frameHeight / 2;
					float moveAngleY = 0;

					if (diffCenterY < -CENTERING_THRESHOLD)
					{
						moveAngleY = radians(-0.5);
					}
					if (diffCenterY > CENTERING_THRESHOLD)
					{
						moveAngleY = radians(0.5);
					}

					moveAngleY = moveAngleY * fabs(diffCenterY) / (CENTERING_THRESHOLD*5.0f);

					_movementLocker->lock();
					if (!_pickInProgress && _arm->getStatus() == Ready)
					{
						if (moveAngleY != 0)
						{
							printf("Move elbow: %f\n", moveAngleY);
							_arm->getElbow()->move(moveAngleY);
						}
						if (moveAngleX != 0)
						{
							printf("Move bedplate: %f\n", moveAngleX);
							_arm->getBedplate()->move(moveAngleX);
						}

						if (moveAngleX == 0 && moveAngleY == 0 && _distanceToObject > 0)
						{
							_measurementLocker->lock();
							float distanceValue = 0;

							do
							{
								distanceValue = _rangefinder->readRangeContinuousMillimeters();
								if (distanceValue > 0)
								{
									_distanceToObject = distanceValue;
									printf("Distance to object: %f\n", distanceValue);
								}
							} while (distanceValue == 0);

							printf("Picking was started\n");
							_pickInProgress = true;

							_measurementLocker->unlock();
						}
					}
					_movementLocker->unlock();
				}
				else
				{
					rect.empty();
				}
			}

			if (isVisualizationOn())
			{
				_visualizer->render(frame, rect, _distanceToObject);
			}

			for (std::vector<HarvbotGripperObserver*>::iterator it = observers.begin(); it != observers.end(); ++it)
			{
				(*it)->ProcessedFrame(frame);
			}
		}
		catch (...)
		{
		}

		bool dontStop = _recognizeRun;
		_recognizeLocker->unlock();

		if (!dontStop)
		{
			break;
		}
	}
}