#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../HarvbotArm2.h"

using namespace cv;
using namespace std;

class HarvbotArm2StateVisualizer
{
private:
	HarvbotArm2* _arm;
public:
	HarvbotArm2StateVisualizer(HarvbotArm2* arm);
	~HarvbotArm2StateVisualizer();

	void drawXZ(Mat canvas);
	void drawXY(Mat canvas);
};

