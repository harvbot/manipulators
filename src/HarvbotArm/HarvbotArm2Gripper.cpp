#include "HarvbotGripper.h"
#include "HarvbotArm2Gripper.h"
#include "HarvbotGripperObserver.h"
#include "Cameras/HarvbotOpenCvCamera.h"
#include "Rangefinder/HarvbotVL53L0XRangefinder.h"

HarvbotArm2Gripper::HarvbotArm2Gripper(HarvbotRecognizer* recognizer) : HarvbotGripper(recognizer)
{
	_arm = new HarvbotArm2();
	_visualizer = new HarvbotArm2StateVisualizer(_arm);
	_rangefinder = new HarvbotVL53L0XRangefinder(HARVBOT_VL53L0X_I2C);
	_camera = new HarvbotOpenCvCamera();

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

	delete _movementThread;
	delete _movementLocker;

	delete _recognizeThread;
	delete _recognizeLocker;
}

void HarvbotArm2Gripper::start()
{
	startMovementProcessing();
	startRecognition();
}

void HarvbotArm2Gripper::stop()
{
	stopMovementProcessing();
	stopRecognition();
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
			else
			{
				printf("Object is too far");
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
				
				if (rect.width > HARVBOT_GREAPER_MIN_CONTOUR_SIZE && rect.height > HARVBOT_GREAPER_MIN_CONTOUR_SIZE)
				{
					printf("Recognition on new frame: x=%d, y=%d, width=%d, height=%d\n", rect.x, rect.y, rect.width, rect.height);

					int wholeCenterX = rect.x + rect.width / 2;
					int wholeCenterY = rect.y + rect.height / 2;

					int frameWidth = camera->frameWidth();
					int frameHeight = camera->frameHeight();

					float diffCenterX = wholeCenterX - frameWidth / 2;
					float moveAngleX = 0;

					if (diffCenterX < -HARVBOT_GREAPER_CENTERING_THRESHOLD)
					{
						moveAngleX = radians(HARVBOT_GREAPER_MOVE_DELTA_X);
					}
					if (diffCenterX > HARVBOT_GREAPER_CENTERING_THRESHOLD)
					{
						moveAngleX = radians(-HARVBOT_GREAPER_MOVE_DELTA_X);
					}

					if (fabs(diffCenterX) > HARVBOT_GREAPER_MIN_CONTOUR_SIZE)
					{
						moveAngleX = moveAngleX * 2;
					}

					float diffCenterY = wholeCenterY - frameHeight / 2;
					float moveAngleY = 0;

					if (diffCenterY < -HARVBOT_GREAPER_CENTERING_THRESHOLD)
					{
						moveAngleY = radians(-HARVBOT_GREAPER_MOVE_DELTA_Y);
					}
					if (diffCenterY > HARVBOT_GREAPER_CENTERING_THRESHOLD)
					{
						moveAngleY = radians(HARVBOT_GREAPER_MOVE_DELTA_Y);
					}

					if (fabs(diffCenterY) > HARVBOT_GREAPER_MIN_CONTOUR_SIZE)
					{
						moveAngleY = moveAngleY * 2;
					}

					_movementLocker->lock();
					if (!_pickInProgress && _arm->getStatus() == Ready)
					{
						if (moveAngleY != 0)
						{
							if ((_arm->getElbow()->distranceToGo() < 0 && moveAngleY > 0) || (_arm->getElbow()->distranceToGo() > 0 && moveAngleY < 0))
							{
								_arm->getElbow()->stop();
							}

							if (_arm->getElbow()->getStatus() == Ready)
							{
								printf("Move elbow: %f\n", moveAngleY);
								_arm->getElbow()->move(moveAngleY);
							}
						}
						if (moveAngleX != 0)
						{
							if ((_arm->getBedplate()->distranceToGo() < 0 && moveAngleX > 0) || (_arm->getBedplate()->distranceToGo() > 0 && moveAngleX < 0))
							{
								_arm->getBedplate()->stop();
							}

							if (_arm->getBedplate()->getStatus() == Ready)
							{
								printf("Move bedplate: %f\n", moveAngleX);
								_arm->getBedplate()->move(moveAngleX);
							}
						}

						if (moveAngleX == 0 && moveAngleY == 0)
						{
							_rangefinder->startContinuous();
							for(int i=0;i<10;i++)
							{
								float distanceValue = _rangefinder->readRangeContinuousMillimeters();
								if (distanceValue > 0 && distanceValue < HARVBOT_VL53L0X_MAX_DISTANCE)
								{
									_distanceToObject = distanceValue;
									printf("Distance to object: %f\n", distanceValue);
									break;
								}
							} 

							_rangefinder->stopContinuous();
							printf("Picking was started\n");
							_pickInProgress = true;
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

			if (rect.isEmpty())
			{
				for (std::vector<HarvbotGripperObserver*>::iterator it = observers.begin(); it != observers.end(); ++it)
				{
					(*it)->NoObjectDetected(frame);
				}
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