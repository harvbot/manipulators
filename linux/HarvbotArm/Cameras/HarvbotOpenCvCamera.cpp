#include "HarvbotOpenCvCamera.h"
#include "HarvbotOpenCvFrame.h"
#include "HarvbotFrame.h"

HarvbotOpenCvCamera::HarvbotOpenCvCamera(int idx)
{
	_innerCamera = new VideoCapture(idx);
}

HarvbotOpenCvCamera::~HarvbotOpenCvCamera()
{
}

HarvbotFrame* HarvbotOpenCvCamera::read()
{
	Mat cameraFrame;
	_innerCamera->read(cameraFrame);

	return new HarvbotOpenCvFrame(cameraFrame);
}

bool HarvbotOpenCvCamera::isOpened()
{
	return _innerCamera->isOpened();
}