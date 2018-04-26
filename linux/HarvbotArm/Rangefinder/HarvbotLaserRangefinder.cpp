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
	uint8_t command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x06, 0x03 };

	sendCommand(command, 3);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return -1;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
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
		return 0;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	uint16_t result = 0;

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
	uint8_t command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x06, 0x03 };

	sendCommand(command, 3);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	delete buffer;
}

void HarvbotLaserRangefinder::stopContinuous()
{
	uint8_t command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x04, 0x02 };

	sendCommand(command, 3);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	delete buffer;
}

void HarvbotLaserRangefinder::powerOn()
{
	uint8_t command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR, 0x06, 0x05, 0x01 };

	sendCommand(command, 4);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR && buffer[1] == 0x06 && buffer[2] == 0x01;

	delete buffer;
}

void HarvbotLaserRangefinder::powerOff()
{
	uint8_t command[] = { HARVBOT_RANGEFINDER_DEFAULT_ADDR,  0x06, 0x05, 0x00 };

	sendCommand(command, 4);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == HARVBOT_RANGEFINDER_DEFAULT_ADDR && buffer[1] == 0x06 && buffer[2] == 0x01;

	delete buffer;
}

bool HarvbotLaserRangefinder::setRange(HarvbotLaserRangefinderRanges range)
{
	uint8_t command[] = { 0xFA, 0x04, 0x09, range };

	sendCommand(command, 4);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x89 && buffer[3] == 0x79;

	delete buffer;

	return success;
}

bool HarvbotLaserRangefinder::setResolution(HarvbotLaserRangefinderResolutions resolution)
{
	uint8_t command[] = { 0xFA, 0x04, 0x0C, resolution };

	sendCommand(command, 4);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x8C && buffer[3] == 0x76;

	delete buffer;

	return success;
}

bool HarvbotLaserRangefinder::setFrequency(HarvbotLaserRangefinderFrequencies frequency)
{
	uint8_t command[] = { 0xFA, 0x04, 0x0A, frequency };

	sendCommand(command, 4);

	int dataAvailable = serialDataAvail(this->m_deviceHandle);
	if (dataAvailable <= 0)
	{
		return false;
	}

	uint8_t* buffer = new uint8_t[dataAvailable];
	getResponse(buffer, dataAvailable);

	bool success = buffer[0] == command[0] && buffer[1] == command[1] && buffer[2] == 0x8A && buffer[3] == 0x78;

	delete buffer;

	return success;
}

size_t HarvbotLaserRangefinder::sendCommand(uint8_t* command, size_t len)
{
	uint8_t* commandWitCs = new uint8_t[len + 1];

	for (int i = 0; i < len; i++)
	{
		commandWitCs[i] = command[i];
	}

	commandWitCs[len] = chksum8(commandWitCs, len);

	serialPuts(this->m_deviceHandle, (const char *)commandWitCs);

	delete commandWitCs;

	return len;
}

size_t HarvbotLaserRangefinder::getResponse(uint8_t* buffer, size_t dataAvailable)
{
	for (int i = 0; i < dataAvailable; i++)
	{
		buffer[i] = serialGetchar(this->m_deviceHandle);
	}

	serialFlush(this->m_deviceHandle);

	return dataAvailable;
}

uint8_t HarvbotLaserRangefinder::chksum8(const uint8_t *buff, size_t len)
{
	uint32_t sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += buff[i];
	}

	return (uint8_t)(0x100 - sum);
}