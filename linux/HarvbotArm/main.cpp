#include <cstdio>
#include <iostream>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <wiringPi.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HarvbotArmFactory.h"
#include "LaserRangefinder/HarvbotRangefinder.h"
using namespace cv;
using namespace std;

#define CAMERA_MAX_VIEW_ANGLE_DEGREES 100
#define CAMERA_FRAME_WIDTH 640
#define CAMERA_FRAME_HEIGHT 480

bool exitFromApp = false;
float distanceToObject = 0;
HarvbotArm2* arm;
HarvbotRangefinder* rangefinder;
std::mutex locker;

void movingThread()
{
	while (!exitFromApp)
	{
		locker.lock();
		arm->runToPosition();
		//arm->printNodesPositions();
		locker.unlock();
	}
}

void measureDistanceThread()
{
	rangefinder->start();
	while (!exitFromApp)
	{
		distanceToObject = rangefinder->read();
	}
}


int main()
{
	wiringPiSetup();

	printf("hello from HarvbotArm!\n");

	arm = HarvbotArmFactory::CreateArm2();
	rangefinder = new HarvbotRangefinder("/dev/ttyUSB0", 9600);

	//arm->getElbow()->move(1);
	//arm->runToPosition();

	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
	stream1.set(CV_CAP_PROP_BUFFERSIZE, 3); // internal buffer will now store only 3 frames

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "Cannot open camera";
	}

	std::thread(movingThread).detach();
	std::thread(measureDistanceThread).detach();

	/*Font font;
	InitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);*/

	//unconditional loop
	while (true) {
		
		Mat cameraFrame;
		stream1.read(cameraFrame);

		Mat imgHSV;
		cvtColor(cameraFrame, imgHSV, COLOR_BGR2HSV);

		Mat imgThresholded;
		inRange(imgHSV, Scalar(10, 70, 70), Scalar(20, 255, 255), imgThresholded);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(imgThresholded,
			contours,
			hierarchy,
			CV_RETR_TREE,
			CV_CHAIN_APPROX_SIMPLE,
			Point(0, 0));

		vector<vector<Point>> contours_poly(contours.size());
		Rect whole;
		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			Rect rect = boundingRect(Mat(contours_poly[i]));
			if (rect.size().width > 60 && rect.size().height > 60)
			{
				if (whole.size().width > 0 && whole.size().height > 0)
				{
					whole = whole | rect;
				}
				else
				{
					whole = rect;
				}
			}
		}

		if (whole.size().width > 60 && whole.size().height > 60)
		{
			char buffer[255];
			sprintf(buffer, "Distance to object %d\n", distanceToObject);

			rectangle(cameraFrame, whole.tl(), whole.br(), Scalar(0, 255, 0), 2, 8, 0);
			putText(cameraFrame, buffer, Point(0,0), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 16);

			int wholeCenterX = whole.x + whole.width / 2;
			int wholeCenterY = whole.y + whole.height / 2;

			//float moveAngleX = (CAMERA_MAX_VIEW_ANGLE_DEGREES * (wholeCenterX - CAMERA_FRAME_WIDTH / 2)) / CAMERA_FRAME_WIDTH;
			float diffCenterY = wholeCenterY - CAMERA_FRAME_HEIGHT / 2;
			float moveAngleY = 0;
			if (diffCenterY < -10)
			{
				moveAngleY = -1;
			}
			if (diffCenterY > 10)
			{
				moveAngleY = 1;
			}

			//printf("Distance to object %f\n", distance);
			
			/*if (fabs(moveAngleX) > 3)
			{
				arm->getBedplate()->move(moveAngleX);
				printf("Move Y: %d\n", moveAngleX);
			}*/

			locker.lock();
			if (fabs(moveAngleY) != 0)
			{
				if (arm->getStatus() == Ready)
				{
					arm->getElbow()->move(moveAngleY);
				}
			}
			locker.unlock();
		}

		imshow("cam", cameraFrame);
		if (waitKey(30) >= 0)
		{
			exitFromApp = true;
			break;
		}
	}

	rangefinder->stop();

	delete rangefinder;
	delete arm;
    return 0;
}