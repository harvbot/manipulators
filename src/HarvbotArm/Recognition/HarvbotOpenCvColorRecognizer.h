#ifndef HarvbotOpenCvColorRecognizer_H_
#define HarvbotOpenCvColorRecognizer_H_

#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../Spatial/HarvbotRect.h"
#include "../Cameras/HarvbotFrame.h"
#include "HarvbotRecognizer.h"

using namespace cv;
using namespace std;

#define MIN_CONTOUR_SIZE 60

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

#endif /* HarvbotOpenCvColorRecognizer_H_ */