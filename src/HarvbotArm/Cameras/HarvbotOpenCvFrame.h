#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HarvbotFrame.h"

using namespace cv;

class HarvbotOpenCvFrame : public HarvbotFrame
{
public:
	HarvbotOpenCvFrame(Mat frame);
	~HarvbotOpenCvFrame();
	Mat getFrame();
private:
	Mat _frame;
};

