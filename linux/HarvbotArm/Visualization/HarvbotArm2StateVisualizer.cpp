#include <math.h>
#include "HarvbotArm2StateVisualizer.h"
#include "../Cameras/HarvbotOpenCvFrame.h"

HarvbotArm2StateVisualizer::HarvbotArm2StateVisualizer(HarvbotArm2* arm)
{
	_arm = arm;
}

HarvbotArm2StateVisualizer::~HarvbotArm2StateVisualizer()
{
}

void HarvbotArm2StateVisualizer::render(HarvbotFrame* frame, HarvbotRect rect, unsigned int distanceToObject)
{
	Rect whole(rect.x, rect.y, rect.width, rect.height);
	Mat cameraFrame = ((HarvbotOpenCvFrame*)frame)->getFrame();
	rectangle(cameraFrame, whole.tl(), whole.br(), Scalar(0, 255, 0), 2, 8, 0);

	char buffer[500];
	sprintf(buffer, "Distance to object %f\n", distanceToObject);
	putText(cameraFrame, buffer, Point(0, 25), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 2);

	drawXY(cameraFrame);
	drawXZ(cameraFrame);

	imshow("cam", cameraFrame);
}

void HarvbotArm2StateVisualizer::drawXZ(Mat canvas)
{
	float q1 = _arm->getBedplate()->currentPosition();
	float q2 = M_PI - _arm->getShoulder()->currentPosition();
	float q3 = M_PI - (M_PI / 2 - _arm->getElbow()->currentPosition());

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	Rect xzStateRect;
	xzStateRect.x = 0;
	xzStateRect.y = canvas.size().height - 100;
	xzStateRect.width = 100;
	xzStateRect.height = 100;

	rectangle(canvas, xzStateRect, Scalar(255, 255, 255), CV_FILLED, 8, 0);
	rectangle(canvas, xzStateRect, Scalar(0, 0, 0), 1, 8, 0);

	float scale = (float)xzStateRect.height/((float)(a1 + a2 + a3));

	Point ptBeadplate1(xzStateRect.x + xzStateRect.width / 2, xzStateRect.y + xzStateRect.height);
	Point ptBeadplate2(xzStateRect.x + xzStateRect.width / 2, xzStateRect.y + xzStateRect.height - (int)(a1* scale));
	line(canvas, ptBeadplate1, ptBeadplate2, Scalar(255, 0, 0), 1, 8, 0);
	
	float xShoulder, zShoulder;
	xShoulder = (a2 * cos(q2)) * scale;
	zShoulder = (a2 * sin(q2) + a1) * scale;
	Point ptShoulder((int)xShoulder + xzStateRect.x + xzStateRect.width / 2, (int)(xzStateRect.y + xzStateRect.height - zShoulder));
	line(canvas, ptBeadplate2, ptShoulder, Scalar(255, 0, 0), 1, 8, 0);

	float xElbow = (a2*cos(q2) + a3 * cos(q2 - q3))*scale;
	float zElbow = (a2*sin(q2) + a3 * sin(q2 - q3) + a1)*scale;
	Point ptElbow((int)xElbow + xzStateRect.x + xzStateRect.width / 2, (int)(xzStateRect.y + xzStateRect.height - zElbow));
	line(canvas, ptShoulder, ptElbow, Scalar(255, 0, 0), 1, 8, 0);

	circle(canvas, ptBeadplate2, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
	circle(canvas, ptShoulder, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
	circle(canvas, ptElbow, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
}

void HarvbotArm2StateVisualizer::drawXY(Mat canvas)
{
	float q1 = _arm->getBedplate()->currentPosition();
	float q2 = M_PI - _arm->getShoulder()->currentPosition();
	float q3 = M_PI - (M_PI / 2 - _arm->getElbow()->currentPosition());

	float a1 = HARVBOT_ARM_2_BEDPLATE;
	float a2 = HARVBOT_ARM_2_SHOULDER;
	float a3 = HARVBOT_ARM_2_ELBOW;

	Rect xyStateRect;
	xyStateRect.x = 100;
	xyStateRect.y = canvas.size().height - 100;
	xyStateRect.width = 100;
	xyStateRect.height = 100;

	rectangle(canvas, xyStateRect, Scalar(255, 255, 255), CV_FILLED, 8, 0);
	rectangle(canvas, xyStateRect, Scalar(0, 0, 0), 1, 8, 0);

	float scale = (float)xyStateRect.height / ((float)(a2 + a3 + 10)*2.0f);

	Point ptBeadplate(xyStateRect.x + xyStateRect.width / 2, xyStateRect.y + xyStateRect.height / 2);

	float xShoulder, yShoulder;
	xShoulder = (a2 * sin(q1)) * scale;
	yShoulder = (a2 * cos(q1)) * scale;
	Point ptShoulder((int)xShoulder + xyStateRect.x + xyStateRect.width / 2, (int)(xyStateRect.y + xyStateRect.height / 2 - yShoulder));
	line(canvas, ptBeadplate, ptShoulder, Scalar(255, 0, 0), 1, 8, 0);

	float xElbow = (a2*sin(q1) + a3 * sin(q1))*scale;
	float yElbow = (a2*cos(q1) + a3 * cos(q1))*scale;
	Point ptElbow((int)xElbow + xyStateRect.x + xyStateRect.width / 2, (int)(xyStateRect.y + xyStateRect.height / 2 - yElbow));
	line(canvas, ptShoulder, ptElbow, Scalar(255, 0, 0), 1, 8, 0);

	circle(canvas, ptBeadplate, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
	circle(canvas, ptShoulder, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
	circle(canvas, ptElbow, 3, Scalar(255, 0, 255), CV_FILLED, 8, 0);
}