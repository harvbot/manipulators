#ifndef HarvbotRangefinder_H_
#define HarvbotRangefinder_H_

#include <stdint.h>
#include <cstddef>
#include <wiringSerial.h>
#include "HarvbotRangefinder.h"

using namespace std;

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
	uint32_t m_baud;
	uint32_t m_deviceHandle;

	size_t getResponse(unsigned char* buffer, size_t dataAvailable);

	size_t sendCommand(unsigned char* command, size_t len);

	uint8_t chksum8(const unsigned char *buff, size_t len);
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

	void laserOn();

	void laserOff();
};

#endif /* HarvbotRangefinder_H_ */