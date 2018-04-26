#ifndef HarvbotRangefinder_H_
#define HarvbotRangefinder_H_

#include <stdint.h>
#include <wiringSerial.h>
#include "HarvbotRangefinder.h"

#define HARVBOT_RANGEFINDER_DEFAULT_ADDR 0x80

enum HarvbotLaserRangefinderRanges
{
	Range05 = 05,
	Range10 = 10,
	Range30 = 30,
	Range50 = 50,
	Range80 = 80
};

enum HarvbotLaserRangefinderResolutions
{
	mm1 = 1,
	mm01 = 2,
};

enum HarvbotLaserRangefinderFrequencies
{
	Frequency5 = 5,
	Frequency10 = 10,
	Frequency20 = 20,
};

class HarvbotLaserRangefinder: public HarvbotRangefinder {
private:
	// Serial port reference.
	char* m_device;
	int m_baud;
	int m_deviceHandle;

	int getResponse(unsigned char* buffer, int dataAvailable);
public:
	HarvbotLaserRangefinder(const char *device, const int baud);
	~HarvbotLaserRangefinder();

	void powerOn();

	void powerOff();

	bool setRange(HarvbotLaserRangefinderRanges range);

	bool setResolution(HarvbotLaserRangefinderResolutions resolution);

	bool setFrequency(HarvbotLaserRangefinderFrequencies frequency);

	void startContinuous(uint32_t periodMilliseconds = 0);

	uint16_t readRangeContinuousMillimeters();

	uint16_t readRangeSingleMillimeters();

	void stopContinuous();
};

#endif /* HarvbotRangefinder_H_ */