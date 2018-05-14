#ifndef HarvbotArm2_H_
#define HarvbotArm2_H_

#include "HarvbotArm.h"
#include "HarvbotArmConstants.h"
#include "Spatial/HarvbotPoint.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmLinearNode.h"

class HarvbotArm2 : public HarvbotArm {
	public:
		HarvbotArm2();
		
		~HarvbotArm2();

		HarvbotArmLinearNode* getClaw();

		void goToStartPosition();

		bool run();

		HarvbotPoint getPointerCoords();

		bool setPointerCoords(HarvbotPoint point);

		bool pickObject(float distanceToObject);

		void printNodesPositions();

		void printPointerPositions();
};

#endif /* HarvbotArm2_H_ */
