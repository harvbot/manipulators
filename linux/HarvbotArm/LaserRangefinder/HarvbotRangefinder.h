#ifndef HarvbotRangefinder_H_
#define HarvbotRangefinder_H_

#include <wiringSerial.h>

#define HARVBOT_RANGEFINDER_DEFAULT_ADDR 0x80

enum HarvbotRangefinderRanges
{
	Range05 = 05,
	Range10 = 10,
	Range30 = 30,
	Range50 = 50,
	Range80 = 80
};

enum HarvbotRangefinderResolutions
{
	mm1 = 1,
	mm01 = 2,
};

enum HarvbotRangefinderFrequencies
{
	Frequency5 = 5,
	Frequency10 = 10,
	Frequency20 = 20,
};

class HarvbotRangefinder {
	private: 
		// Serial port reference.
		char* m_device;
		int m_baud;
		int m_deviceHandle;

		int getResponse(unsigned char* buffer);
	public:
		HarvbotRangefinder(const char *device, const int baud);
		~HarvbotRangefinder();

		void turnLaserOn();

		void turnLaserOff();

		bool setRange(HarvbotRangefinderRanges range);

		bool setResolution(HarvbotRangefinderResolutions resolution);

		bool setFrequency(HarvbotRangefinderFrequencies frequency);

		void start();

		float read();

		void stop();
};

#endif /* HarvbotRangefinder_H_ */