#ifndef HarvbotVL53L0XRangefinder_H_
#define HarvbotVL53L0XRangefinder_H_

#include "HarvbotRangefinder.h"
#include "../Native/VL53L0XPi.hpp"

class HarvbotVL53L0XRangefinder : public HarvbotRangefinder
{
public:
	HarvbotVL53L0XRangefinder(const char* device="/dev/i2c-1");
	~HarvbotVL53L0XRangefinder();

	void powerOn();

	void powerOff();

	void startContinuous(uint32_t periodMilliseconds = 0);

	void stopContinuous();

	uint16_t readRangeSingleMillimeters();

	uint16_t readRangeContinuousMillimeters();
private:
	VL53L0XPi * innerRangefinder;
};

#endif /* HarvbotVL53L0XRangefinder_H_ */