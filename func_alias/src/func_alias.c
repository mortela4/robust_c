/*
 ============================================================================
 Name        : func_alias.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#define AdcRead		Ads1258_Read	/* @note signature: void AdcRead(uint8_t channel) */
#define LutRead		EepromLutRead	/* @note signature: uint16_t LutRead(uint8_t *bufStart, const size_t bufSize) */


void Ads1258_Read(uint8_t channel)
{
	printf("%s(): reading channel %d\n", __FUNCTION__, channel);
}

void Ad7124_Read(uint8_t channel)
{
	printf("%s(): reading channel %d\n", __FUNCTION__, channel);
}

uint16_t EepromLutRead(uint8_t *bufStart, const size_t bufSize)
{
	size_t maxSize = (bufSize - 40 > 0) ? bufSize - 40 : bufSize;
	const uint8_t data = 0xAC;
	uint16_t i;

	printf("%s(): reading EEPROM-LUT\n", __FUNCTION__);

	for (i=0; i<maxSize; i++)
	{
		bufStart[i] = data;
	}

	return i;
}

uint16_t RamLutRead(uint8_t *bufStart, const size_t bufSize)
{
	size_t maxSize = (bufSize - 25 > 0) ? bufSize - 25 : bufSize;
	const uint8_t data = 0xDC;
	uint16_t i;

	printf("%s(): reading RAM-LUT\n", __FUNCTION__);

	for (i=0; i<maxSize; i++)
	{
		bufStart[i] = data;
	}

	return i;
}


int main(void)
{
	uint8_t buf[50];
	uint16_t lutSize =  0;

	(void *)memset(buf, 0, sizeof(buf));

	AdcRead(3U);
	lutSize = LutRead(buf, sizeof(buf));
	for (int i=0; i<sizeof(buf); i++)
	{
		if (i<lutSize)
		{
			printf("LUT[%d] = 0x%02X\n", i, buf[i]);
		}
		else
		{
			printf("LUT[%d] = 0x%02X (beyond defined values)\n", i, buf[i]);
		}
	}
	printf("\r\n");

#ifdef AdcRead
#undef AdcRead		// Avoids 'symbol redefined' warning ...
#define AdcRead		Ad7124_Read
#endif

	AdcRead(6U);

#ifdef LutRead
#undef LutRead
#define LutRead		RamLutRead
#endif

	LutRead(buf, sizeof(buf));
	lutSize = LutRead(buf, sizeof(buf));
	for (int i=0; i<sizeof(buf); i++)
	{
		if (i<lutSize)
		{
			printf("LUT[%d] = 0x%02X\n", i, buf[i]);
		}
		else
		{
			printf("LUT[%d] = 0x%02X (beyond defined values)\n", i, buf[i]);
		}
	}

	return EXIT_SUCCESS;
}
