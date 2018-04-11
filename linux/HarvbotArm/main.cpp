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
#define MIN_CONTOUR_SIZE 60
#define CENTERING_THRESHOLD 10

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
		//arm->printPointerPositions();
		locker.unlock();
	}
}

void measureDistanceThread()
{
	rangefinder->start();
	while (!exitFromApp)
	{
		float distanceValue = rangefinder->read();
		if (distanceValue != -1)
		{
			distanceToObject = distanceValue;
			printf("Distance to object: %f\n", distanceToObject);
		}
	}
}

int main()
{
	wiringPiSetup();

	printf("hello from HarvbotArm!\n");

	arm = HarvbotArmFactory::CreateArm2();
	rangefinder = new HarvbotRangefinder("/dev/ttyUSB0", 9600);

	arm->goToStartPosition();

	//VideoCapture camera(0);   //0 is the id of video device.0 if you have only one camera.
	//camera.set(CV_CAP_PROP_BUFFERSIZE, 3); // internal buffer will now store only 3 frames

	//if (!camera.isOpened()) { //check if video device has been initialised
	//	printf("Cannot open camera\n");
	//}

	//std::thread(movingThread).detach();
	//std::thread(measureDistanceThread).detach();

	//while (true) {
	//	
	//	Mat cameraFrame;
	//	camera.read(cameraFrame);

	//	Mat imgHSV;
	//	cvtColor(cameraFrame, imgHSV, COLOR_BGR2HSV);

	//	Mat imgThresholded;
	//	inRange(imgHSV, Scalar(10, 70, 70), Scalar(20, 255, 255), imgThresholded);

	//	vector<vector<Point>> contours;
	//	vector<Vec4i> hierarchy;
	//	findContours(imgThresholded,
	//		contours,
	//		hierarchy,
	//		CV_RETR_TREE,
	//		CV_CHAIN_APPROX_SIMPLE,
	//		Point(0, 0));

	//	vector<vector<Point>> contours_poly(contours.size());
	//	Rect whole;
	//	for (int i = 0; i < contours.size(); i++)
	//	{
	//		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
	//		Rect rect = boundingRect(Mat(contours_poly[i]));
	//		if (rect.size().width > MIN_CONTOUR_SIZE && rect.size().height > MIN_CONTOUR_SIZE)
	//		{
	//			if (whole.size().width > 0 && whole.size().height > 0)
	//			{
	//				whole = whole | rect;
	//			}
	//			else
	//			{
	//				whole = rect;
	//			}
	//		}
	//	}

	//	if (whole.size().width > MIN_CONTOUR_SIZE && whole.size().height > MIN_CONTOUR_SIZE)
	//	{
	//		rectangle(cameraFrame, whole.tl(), whole.br(), Scalar(0, 255, 0), 2, 8, 0);

	//		char buffer[500];
	//		sprintf(buffer, "Distance to object %f\n", distanceToObject);
	//		putText(cameraFrame, buffer, Point(0, 25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);

	//		int wholeCenterX = whole.x + whole.width / 2;
	//		int wholeCenterY = whole.y + whole.height / 2;

	//		float diffCenterX = wholeCenterX - CAMERA_FRAME_WIDTH / 2;
	//		float moveAngleX = 0;
	//		if (diffCenterX < -CENTERING_THRESHOLD)
	//		{
	//			moveAngleX = -0.5;
	//		}
	//		if (diffCenterX > CENTERING_THRESHOLD)
	//		{
	//			moveAngleX = 0.5;
	//		}

	//		float diffCenterY = wholeCenterY - CAMERA_FRAME_HEIGHT / 2;
	//		float moveAngleY = 0;
	//		if (diffCenterY < -CENTERING_THRESHOLD)
	//		{
	//			moveAngleY = -0.5;
	//		}
	//		if (diffCenterY > CENTERING_THRESHOLD)
	//		{
	//			moveAngleY = 0.5;
	//		}

	//		locker.lock();
	//		if (arm->getStatus() == Ready)
	//		{
	//			if (moveAngleY != 0)
	//			{
	//				arm->getElbow()->move(moveAngleY);
	//			}
	//			if (moveAngleX != 0)
	//			{
	//				arm->getBedplate()->move(moveAngleX);
	//			}
	//		}
	//		locker.unlock();
	//	}

	//	imshow("cam", cameraFrame);
	//	if (waitKey(30) >= 0)
	//	{
	//		exitFromApp = true;
	//		break;
	//	}
	//}

	rangefinder->stop();

	delete rangefinder;
	delete arm;
    return 0;
}