#pragma once
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HarvbotCamera.h"
#include "HarvbotFrame.h"

using namespace cv;
using namespace std;

class HarvbotOpenCvCamera: public HarvbotCamera
{
public:
	HarvbotOpenCvCamera(int idx=0);
	~HarvbotOpenCvCamera();

	HarvbotFrame* read();

	bool isOpened();
private:
	VideoCapture* _innerCamera;
};

