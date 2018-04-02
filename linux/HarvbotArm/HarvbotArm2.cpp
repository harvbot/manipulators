#include "HarvbotArm.h"
#include "HarvbotArm2.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmScrewNode.h"
#include "Nodes/HarvbotArmStepperCircleNode.h"
#include "Nodes/HarvbotArmStepperScrewNode.h"
#include "HarvbotArmConstants.h"

//					WiringPI			Shifter-sheld      
#define SX_STEP         4       //    		16
#define SX_DIR          5       // 		    18
#define SX_END          6       //    		22
#define SX_RATIO        50 * 4

#define SY_STEP         11      //   		26
#define SY_DIR          26      //    		32
#define SY_END          27  	//			36
#define SY_RATIO        50 * 4

#define SZ_STEP         23		//  		33   
#define SZ_DIR          22      //    		31 
#define SZ_END          21		//			29
#define SZ_RATIO        50 * 4

#define SJ_STEP         3       //  		15 
#define SJ_DIR          2       //  		13
#define SJ_END          30		//			27
#define SJ_RATIO        1 * 4


HarvbotArm2::HarvbotArm2() 
: HarvbotArm(ArmType2) {

	this->nodesCount = 4;
	
	this->nodes = new HarvbotArmNode*[4];

	this->nodes[0] = new HarvbotArmStepperCircleNode(Bedplate, SX_STEP, SX_DIR, SX_END, 1000, 0.0f, 0.0f, 360.0, 200, SX_RATIO);
	this->nodes[1] = new HarvbotArmStepperCircleNode(Shoulder, SY_STEP, SY_DIR, SY_END, 1000, 0.0f, 0.0f, 180, 200, SY_RATIO);
	this->nodes[2] = new HarvbotArmStepperCircleNode(Elbow, SZ_STEP, SZ_DIR, SZ_END, 1000, 0.0f, 0.0f, 180, 200, SZ_RATIO);
	this->nodes[3] = new HarvbotArmStepperScrewNode(Claw, SJ_STEP, SJ_DIR, SJ_END, 1600, 0, 200, 8, SJ_RATIO);

	//this->goToStartPosition();
}

HarvbotArm2::~HarvbotArm2() {}

void HarvbotArm2::goToStartPosition()
{
	((HarvbotArmCircleNode*)this->nodes[0])->move(90);
	((HarvbotArmCircleNode*)this->nodes[1])->move(150);
	((HarvbotArmCircleNode*)this->nodes[2])->move(60);
	((HarvbotArmScrewNode*)this->nodes[3])->goToStartPosition();
}

HarvbotArmScrewNode* HarvbotArm2::getClaw()
{
	return (HarvbotArmScrewNode*)this->getNodeByType(Claw);
}