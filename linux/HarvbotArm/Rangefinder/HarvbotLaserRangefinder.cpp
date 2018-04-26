#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "HarvbotLaserRangefinder.h"

HarvbotLaserRangefinder::HarvbotLaserRangefinder(const char *device, const int baud)
{
	this->m_device = const_cast<char*>(device);
	this->m_deviceHandle = serialOpen(this->m_device, baud);
	if (this->m_deviceHandle < 0)
	{
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
	}
}

HarvbotLaserRangefinder::~HarvbotLaserRangefinder()
{
	if (this->m_deviceHandle > 0)
	{
		serialClose(this->m_deviceHandle);
	}
}

uint16_t HarvbotLaserRangefinder::readRangeSingleMillimeters()
{
	char command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x06, 0x03, 0x77 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return -1;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	uint16_t result = -1;

	if (dataAvailable % 11 == 0)
	{
		if (buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR &&
			buffer[1] == 0x06 && buffer[2] == 0x83 && buffer[6] == 0x2E)
		{
			result = 0;

			result += (buffer[3] - 48) * 1000;
			result += (buffer[4] - 48) * 100;
			result += (buffer[5] - 48) * 10;
			result += (buffer[7] - 48);
		}
	}

	delete buffer;

	return result;
}

uint16_t HarvbotLaserRangefinder::readRangeContinuousMillimeters()
{
	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return -1;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	uint16_t result = -1;

	if (dataAvailable % 11 == 0)
	{
		if (buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR &&
			buffer[1] == 0x06 && buffer[2] == 0x83 && buffer[6] == 0x2E)
		{
			result = 0;

			result += (buffer[3] - 48) * 1000;
			result += (buffer[4] - 48) * 100;
			result += (buffer[5] - 48) * 10;
			result += (buffer[7] - 48);
		}
	}

	delete buffer;

	return result;
}

void HarvbotLaserRangefinder::startContinuous(uint32_t periodMilliseconds)
{
	char command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x06, 0x03, 0x77 };

	serialPuts(this->m_deviceHandle, (const char*)&command);
}

void HarvbotLaserRangefinder::stopContinuous()
{
	char command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x04, 0x02, 0x7A };

	serialPuts(this->m_deviceHandle, (const char*)&command);
}

void HarvbotLaserRangefinder::powerOn()
{
	char command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR,  0x06, 0x05, 0x01, 0x74 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR && buffer[1] == 0x06 && buffer[2] == 0x01;

	delete buffer;
}

void HarvbotLaserRangefinder::powerOff()
{
	char command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR,  0x06, 0x05, 0x00, 0x74 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR && buffer[1] == 0x06 && buffer[2] == 0x01;

	delete buffer;
}

bool HarvbotLaserRangefinder::setRange(HarvbotLaserRangefinderRanges range)
{
	char command[] = { 0xFA, 0x04, 0x09, range, 0xF4 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x89 && buffer[3] == 0x79;

	delete buffer;

	return success;
}

bool HarvbotLaserRangefinder::setResolution(HarvbotLaserRangefinderResolutions resolution)
{
	char command[] = { 0xFA, 0x04, 0x0C, resolution, 0xF5 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x8C && buffer[3] == 0x76;

	delete buffer;

	return success;
}

bool HarvbotLaserRangefinder::setFrequency(HarvbotLaserRangefinderFrequencies frequency)
{
	char command[] = { 0xFA, 0x04, 0x0A, frequency, 0xF5 };

	serialPuts(this->m_deviceHandle, (const char*)&command);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	unsigned char* buffer = new unsigned char[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x8A && buffer[3] == 0x78;

	delete buffer;

	return success;
}

int HarvbotLaserRangefinder::getResponse(unsigned char* buffer, int dataAvailable)
{
	for (int i = 0; i < dataAvailable; i++)
	{
		buffer[i] = serialGetchar(this->m_deviceHandle);
	}

	serialFlush(this->m_deviceHandle);

	return dataAvailable;
}