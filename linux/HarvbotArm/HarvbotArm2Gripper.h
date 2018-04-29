#pragma once
#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include "HarvbotGripper.h"
#include "HarvbotArm2.h"
#include "Visualization/HarvbotArm2StateVisualizer.h"
#include "Rangefinder/HarvbotLaserRangefinder.h"
#include "Recognition/HarvbotRecognizer.h"

using namespace std;

#define MIN_CONTOUR_SIZE 60
#define CENTERING_THRESHOLD 15

class HarvbotArm2Gripper: public HarvbotGripper
{
public:
	HarvbotArm2Gripper(HarvbotRecognizer* recognizer);
	~HarvbotArm2Gripper();

	HarvbotArm* getArm();

	HarvbotCamera* getCamera();

	HarvbotRangefinder* getRangefinder();

	unsigned int getDistanceMillimeters();

	void start();

	void stop();

protected:
	void startRangefinderMeasurement();

	void stopRangefinderMeasurement();

	void startMovementProcessing();

	void stopMovementProcessing();

	void startRecognition();

	void stopRecognition();
private :

	HarvbotArm2StateVisualizer* _visualizer;

	HarvbotArm2* _arm;

	HarvbotLaserRangefinder* _rangefinder;

	HarvbotCamera* _camera;

	unsigned int _distanceToObject;

	mutex* _measurementLocker;

	thread* _measurementThread;

	bool _measurementRun;

	void measurementThreadFunc();

	mutex* _movementLocker;

	thread* _movementThread;

	bool _movementRun;

	void movementThreadFunc();

	mutex* _recognizeLocker;

	thread* _recognizeThread;

	bool _recognizeRun;

	void recognizeThreadFunc();

	bool _pickInProgress;
};

