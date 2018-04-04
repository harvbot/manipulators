#ifndef HarvbotRangefinder_H_
#define HarvbotRangefinder_H_

#include <wiringSerial.h>

#define HarvbotRangefinder_DefaultAddr 0x80

class HarvbotRangefinder {
	private: 
		// Serial port reference.
		char *m_device;
		int m_baud;
		int m_deviceHandle;
	public:
		HarvbotRangefinder(const char *device, const int baud);
		~HarvbotRangefinder();
		void start();
		float read();
		void stop();
};

#endif /* HarvbotRangefinder_H_ */