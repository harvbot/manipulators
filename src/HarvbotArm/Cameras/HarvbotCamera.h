#pragma once
#include "HarvbotFrame.h"

class HarvbotCamera
{
public:
	HarvbotCamera();
	~HarvbotCamera();

	virtual HarvbotFrame* read() = 0;

	virtual bool isOpened() = 0;

	virtual unsigned int frameWidth() = 0;

	virtual unsigned int frameHeight() = 0;
};

