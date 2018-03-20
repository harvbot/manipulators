#include <cstdio>
#include <wiringPi.h>
#include "HarvbotArmFactory.h"


int main()
{
	wiringPiSetup();

	HarvbotArm2* arm = HarvbotArmFactory::CreateArm2();

    printf("hello from HarvbotArm!\n");

	delete arm;
    return 0;
}