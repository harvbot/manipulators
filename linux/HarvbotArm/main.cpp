#include <cstdio>
#include <wiringPi.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "HarvbotArmFactory.h"
#include "LaserRangefinder/HarvbotRangefinder.h"
using namespace cv;
using namespace std;

#define CAMERA_MAX_VIEW_ANGLE_DEGREES 100
#define CAMERA_FRAME_WIDTH 600
#define CAMERA_FRAME_HEIGHT 600

int main()
{
	wiringPiSetup();

	printf("hello from HarvbotArm!\n");

	HarvbotArm2* arm = HarvbotArmFactory::CreateArm2();
	HarvbotRangefinder* rangefinder = new HarvbotRangefinder("/dev/ttyUSB0", 9600);
	rangefinder->start();

	arm->getElbow()->move(1);
	arm->runToPosition();

	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "Cannot open camera";
	}

	/*Font font;
	InitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5, 0.5);*/

	//unconditional loop
	while (true) {
		float distance = rangefinder->read();

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
			if (rect.size().width > 20 && rect.size().height > 20)
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

		if (whole.size().width > 20 && whole.size().height > 20)
		{
			char buffer[255];
			sprintf(buffer, "Distance to object %d", distance);

			rectangle(cameraFrame, whole.tl(), whole.br(), Scalar(0, 255, 0), 2, 8, 0);
			putText(cameraFrame, buffer, Point(0,0), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 4);

			int wholeCenterX = whole.x + whole.width / 2;
			int wholeCenterY = whole.y + whole.height / 2;

			float moveAngleX = (CAMERA_MAX_VIEW_ANGLE_DEGREES * (CAMERA_FRAME_WIDTH / 2 - wholeCenterX)) / CAMERA_FRAME_WIDTH;
			float moveAngleY = (CAMERA_MAX_VIEW_ANGLE_DEGREES * (CAMERA_FRAME_HEIGHT / 2 - wholeCenterY)) / CAMERA_FRAME_HEIGHT;

			printf(buffer, "Distance to object %d", distance);
			printf(buffer, "Move X: %d", moveAngleX);
			printf(buffer, "Move Y: %d", moveAngleY);

			if (fabs(moveAngleX) < 3)
			{
				arm->getBedplate()->move(moveAngleX);
			}

			if (fabs(moveAngleY) < 3)
			{
				arm->getElbow()->move(moveAngleY);
			}

			arm->goToStartPosition();
		}

		imshow("cam", cameraFrame);
		if (waitKey(30) >= 0)
			break;
	}

	rangefinder->stop();

	delete rangefinder;
	delete arm;
    return 0;
}