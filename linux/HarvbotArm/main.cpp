#include <cstdio>
#include <wiringPi.h>
#include "HarvbotArmFactory.h"


int main()
{
	wiringPiSetup();

	HarvbotArm2* arm = HarvbotArmFactory::CreateArm2();

	arm->getBedplate()->write(10);

    printf("hello from HarvbotArm!\n");

	delete arm;
    return 0;
}