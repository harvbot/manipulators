#ifndef HarvbotArm2_H_
#define HarvbotArm2_H_

#include "HarvbotArm.h"
#include "HarvbotArmNode.h"
#include "HarvbotArmCircleNode.h"
#include "HarvbotArmScrewNode.h"
#include "HarvbotArmConstants.h"

class HarvbotArm2 : public HarvbotArm {
	public:
		HarvbotArm2();
		
		~HarvbotArm2();

		HarvbotArmScrewNode* getClaw();

		void goToStartPosition();
};

#endif /* HarvbotArm2_H_ */
