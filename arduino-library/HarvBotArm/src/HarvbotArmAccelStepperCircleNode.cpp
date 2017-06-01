#include <math.h>
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmAccelStepperCircleNode.h"

HarvbotArmAccelStepperCircleNode::HarvbotArmAccelStepperCircleNode(
	int nodeType, 
	int pinDir, 
	int pinStep, 
	float pos, 
	float minPos, 
	float maxPos) 
	: HarvbotArmCircleNode(nodeType, pos, minPos, maxPos)
{
	this->stepper = new AccelStepper(1, pinDir, pinStep);
}

HarvbotArmAccelStepperCircleNode::~HarvbotArmAccelStepperCircleNode(){
	delete this->stepper;
}

float HarvbotArmAccelStepperCircleNode::write(float pos) {

	int currentPos = (int)read();

	pos = floor(pos);
	
	if (currentPos != pos)
	{
		this->stepper->move((int)pos-currentPos);
		this->stepper->run();
	}

	return pos;
}