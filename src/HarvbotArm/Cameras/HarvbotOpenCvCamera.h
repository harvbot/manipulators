#ifndef HarvbotOpenCvCamera_H_
#define HarvbotOpenCvCamera_H_

#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "HarvbotCamera.h"
#include "HarvbotFrame.h"

using namespace cv;
using namespace std;

#define CAMERA_FRAME_WIDTH 640
#define CAMERA_FRAME_HEIGHT 480

class HarvbotOpenCvCamera: public HarvbotCamera
{
public:
	HarvbotOpenCvCamera(int idx=0);
	~HarvbotOpenCvCamera();

	HarvbotFrame* read();

	bool isOpened();

	unsigned int frameWidth();

	unsigned int frameHeight();
private:
	VideoCapture* _innerCamera;
};

#endif /* HarvbotOpenCvCamera_H_ */