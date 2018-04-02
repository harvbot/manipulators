#include <cstdio>
#include <wiringPi.h>
#include "HarvbotArmFactory.h"


int main()
{
	wiringPiSetup();

	printf("hello from HarvbotArm!\n");

	HarvbotArm2* arm = HarvbotArmFactory::CreateArm2();

	arm->getElbow()->move(1);
	arm->runToPosition();

	delete arm;
    return 0;
}