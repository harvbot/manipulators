#ifndef HarvbotArmFactory_H_
#define HarvbotArmFactory_H_

#include "HarvbotArm.h"
#include "HarvbotArm2.h"

class HarvbotArmFactory {
	private:
		// Initialzies a new instance.
		HarvbotArmFactory();

    public:
        static HarvbotArm2* CreateArm2();
};

#endif /* HarvbotArmFactory_H_ */