#pragma once
#include "../Spatial/HarvbotRect.h"
#include "../Cameras/HarvbotFrame.h"

class HarvbotRecognizer
{
public:
	HarvbotRecognizer();
	~HarvbotRecognizer();

	virtual HarvbotRect recognize(HarvbotFrame* frame) = 0;
};

