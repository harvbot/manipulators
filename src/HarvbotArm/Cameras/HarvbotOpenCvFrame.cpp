#include "HarvbotOpenCvFrame.h"

HarvbotOpenCvFrame::HarvbotOpenCvFrame(Mat frame)
{
	_frame = frame;
}

HarvbotOpenCvFrame::~HarvbotOpenCvFrame()
{
}

Mat HarvbotOpenCvFrame::getFrame()
{
	return _frame;
}
