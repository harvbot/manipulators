#pragma once
#include "HarvbotFrame.h"

class HarvbotCamera
{
public:
	HarvbotCamera();
	~HarvbotCamera();

	virtual HarvbotFrame* read() = 0;

	virtual bool isOpened() = 0;
};

