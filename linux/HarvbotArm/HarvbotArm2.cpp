#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmStepperCircleNode.h"
#include "HarvbotArmStepperScrewNode.h"
#include "HarvbotArmConstants.h"

//					WiringPI			Shifter-sheld      
#define SX_STEP         4       //    		16
#define SX_DIR          5       // 		    18
#define SX_END          6       //    		22

#define SY_STEP         11      //   		26
#define SY_DIR          26      //    		32
#define SY_END          27  	//			36

#define SZ_STEP         23		//  		33   
#define SZ_DIR          22      //    		31 
#define SZ_END          21		//			29

#define SJ_STEP         3       //  		15 
#define SJ_DIR          2       //  		13


HarvbotArm2::HarvbotArm2() 
: HarvbotArm(ArmType2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmStepperCircleNode(Bedplate, SX_STEP, SX_DIR, 0.0f, 0.0f, 360.0, 1000, 1);
	this->nodes[1] = new HarvbotArmStepperCircleNode(Shoulder, SY_STEP, SY_DIR, 0.0f, 0.0f, 180, 1000, 1);
	this->nodes[2] = new HarvbotArmStepperCircleNode(Elbow, SZ_STEP, SZ_DIR, 0.0f, 0.0f, 180, 1000, 1);
	this->nodes[3] = new HarvbotArmStepperScrewNode(Claw, SJ_STEP, SJ_DIR, 0, 1000, 8);

	this->goToStartPosition();
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->write(90);
	((HarvbotArmCircleNode*)this->nodes[1])->write(150);
	((HarvbotArmCircleNode*)this->nodes[2])->write(60);
	((HarvbotArmScrewNode*)this->nodes[3])->goToStartPosition();
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(Claw);
}