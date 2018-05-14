#ifndef HarvbotArm2StateVisualizer_H_
#define HarvbotArm2StateVisualizer_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "../HarvbotArm2.h"
#include "../Cameras/HarvbotFrame.h"
#include "../Spatial/HarvbotRect.h"

using namespace cv;
using namespace std;

class HarvbotArm2StateVisualizer
{
private:
	HarvbotArm2* _arm;
	
public:
	HarvbotArm2StateVisualizer(HarvbotArm2* arm);
	~HarvbotArm2StateVisualizer();

	void render(HarvbotFrame* frame, HarvbotRect rect, unsigned int distanceToObject);
	void drawXZ(Mat canvas);
	void drawXY(Mat canvas);
};

#endif /* HarvbotArm2StateVisualizer_H_ */