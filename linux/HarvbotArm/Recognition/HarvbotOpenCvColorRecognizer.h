#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../Spatial/HarvbotRect.h"
#include "../Cameras/HarvbotFrame.h"
#include "HarvbotRecognizer.h"

using namespace cv;

class HarvbotOpenCvColorRecognizer : public HarvbotRecognizer
{
public:
	HarvbotOpenCvColorRecognizer(Scalar lowValues, Scalar highValues);
	~HarvbotOpenCvColorRecognizer();

	HarvbotRect recognize(HarvbotFrame* frame);
private:
	Scalar _lowValues;
	Scalar _highValues;
};

