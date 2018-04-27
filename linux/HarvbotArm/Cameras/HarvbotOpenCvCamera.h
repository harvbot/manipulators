#pragma once
#include "HarvbotCamera.h"
#include "HarvbotFrame.h"

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

