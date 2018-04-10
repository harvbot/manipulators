#ifndef HarvbotArm2_H_
#define HarvbotArm2_H_

#include "HarvbotArm.h"
#include "HarvbotArmConstants.h"
#include "Spatial/HarvbotPoint.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmScrewNode.h"

class HarvbotArm2 : public HarvbotArm {
	public:
		HarvbotArm2();
		
		~HarvbotArm2();

		HarvbotArmScrewNode* getClaw();

		void goToStartPosition();

		HarvbotPoint getPointerCoords();

		void printNodesPositions();

		virtual void printPointerPositions() = 0;
};

#endif /* HarvbotArm2_H_ */
