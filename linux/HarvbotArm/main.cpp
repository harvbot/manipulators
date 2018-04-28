#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <wiringPi.h>
#include "HarvbotArm2Gripper.h"
#include "Recognition/HarvbotOpenCvColorRecognizer.h"
#include "Visualization/HarvbotArm2StateVisualizer.h"

HarvbotArm2Gripper* arm;
HarvbotOpenCvColorRecognizer* recognizer;
using namespace cv;

int main()
{
	wiringPiSetup();

	recognizer = new HarvbotOpenCvColorRecognizer(Scalar(10, 70, 70), Scalar(20, 255, 255));
	arm = new HarvbotArm2Gripper(recognizer);

	arm->start();
	while (true) {
		
		if (waitKey(30) >= 0)
		{
			break;
		}
	}
	arm->stop();

	delete arm;
	delete recognizer;
	
    return 0;
}