#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "HarvbotRangefinder.h"

HarvbotRangefinder::HarvbotRangefinder(const char *device, const int baud)
{
	this->m_device = const_cast<char*>(device);
	this->m_deviceHandle = serialOpen(this->m_device, baud);
	if (this->m_deviceHandle < 0)
	{
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
	}
}

HarvbotRangefinder::~HarvbotRangefinder()
{
	if (this->m_deviceHandle > 0)
	{
		serialClose(this->m_deviceHandle);
	}
}

float HarvbotRangefinder::read() 
{
	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return -1;
	}

	float result = -1;
	unsigned char* buffer = new unsigned char[dataAvailable];
	for (int i = 0; i < dataAvailable; i++)
	{
		buffer[i] = serialGetchar(this->m_deviceHandle);
	}

	if (dataAvailable % 11 == 0)
	{
		if (buffer[0] == HarvbotRangefinder_DefaultAddr &&
			buffer[1] == 0x06 && buffer[2] == 0x83 && buffer[6] == 0x2E)
		{
			result = 0;

			result += (buffer[3] - 48) * 100;
			result += (buffer[4] - 48) * 10;
			result += (buffer[5] - 48);

			result += (buffer[7] - 48) * 0.1;
			result += (buffer[8] - 48) * 0.01;
			result += (buffer[9] - 48) * 0.001;
		}
	}

	serialFlush(this->m_deviceHandle);

	delete buffer;

	return result;
}

void HarvbotRangefinder::start() 
{
	char command[] = {HarvbotRangefinder_DefaultAddr, 0x06, 0x03, 0x77};

	serialPuts(this->m_deviceHandle, (const char*)&command);
}

void HarvbotRangefinder::stop() 
{
	char command[] = {HarvbotRangefinder_DefaultAddr, 0x04, 0x02, 0x7A};

	serialPuts(this->m_deviceHandle, (const char*)&command);
}