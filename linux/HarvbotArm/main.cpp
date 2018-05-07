#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <wiringPi.h>
#include "HarvbotArm2Gripper.h"
#include "Recognition/HarvbotOpenCvColorRecognizer.h"
#include "Visualization/HarvbotArm2StateVisualizer.h"
#include "HarvbotArm2GripperBacketObserver.h"

HarvbotArm2Gripper* gripper;
HarvbotOpenCvColorRecognizer* recognizer;
HarvbotArm2GripperBacketObserver* observer;
using namespace cv;

int main()
{
	wiringPiSetup();

	recognizer = new HarvbotOpenCvColorRecognizer(Scalar(10, 70, 70), Scalar(20, 255, 255));
	gripper = new HarvbotArm2Gripper(recognizer);
	observer = new HarvbotArm2GripperBacketObserver((HarvbotArm2*)gripper->getArm());

	gripper->attachObserver((HarvbotGripperObserver*)observer);
	gripper->start();
	while (true) {
		
		if (waitKey() >= 0)
		{
			break;
		}

		delay(300);
	}
	gripper->stop();

	delete gripper;
	delete recognizer;
	delete observer;
	
    return 0;
}