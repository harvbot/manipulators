#ifndef HarvbotArmFactory_H_
#define HarvbotArmFactory_H_

#include <HarvbotArm.h>
#include <HarvbotArm1.h>
#include <HarvbotArm2.h>

class HarvbotArmFactory {
	private:
		// Initialzies a new instance.
		HarvbotArmFactory();

    public:
        static HarvbotArm1* CreateServoArm1();

        static HarvbotArm2* CreateAFMotorArm2();
};

#endif /* HarvbotArmFactory_H_ */