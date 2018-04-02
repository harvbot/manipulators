#ifndef HarvbotArm2_H_
#define HarvbotArm2_H_

#include "HarvbotArm.h"
#include "Nodes/HarvbotArmNode.h"
#include "Nodes/HarvbotArmCircleNode.h"
#include "Nodes/HarvbotArmScrewNode.h"
#include "HarvbotArmConstants.h"

class HarvbotArm2 : public HarvbotArm {
	public:
		HarvbotArm2();
		
		~HarvbotArm2();

		HarvbotArmScrewNode* getClaw();

		void goToStartPosition();
};

#endif /* HarvbotArm2_H_ */
