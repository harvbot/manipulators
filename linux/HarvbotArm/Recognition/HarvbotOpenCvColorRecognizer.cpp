#include "HarvbotOpenCvColorRecognizer.h"
#include "../Cameras/HarvbotOpenCvFrame.h"

HarvbotOpenCvColorRecognizer::HarvbotOpenCvColorRecognizer(Scalar lowValues, Scalar highValues)
{
	_lowValues = lowValues;
	_highValues = highValues;
}

HarvbotOpenCvColorRecognizer::~HarvbotOpenCvColorRecognizer()
{
}

HarvbotRect HarvbotOpenCvColorRecognizer::recognize(HarvbotFrame* frame)
{
	HarvbotOpenCvFrame* openCvFrame = (HarvbotOpenCvFrame*)frame;
	Mat cameraFrame = frame->getFrame();

	Mat imgHSV;
	cvtColor(cameraFrame, imgHSV, COLOR_BGR2HSV);

	Mat imgThresholded;
	inRange(imgHSV, _lowValues, _highValues, imgThresholded);

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
		if (rect.size().width > MIN_CONTOUR_SIZE && rect.size().height > MIN_CONTOUR_SIZE)
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

	return whole;
}