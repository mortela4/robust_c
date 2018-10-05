#include <inttypes.h>
#include <stdbool.h>
//
#include <stdio.h>
//
#include "coeffs.h"


/*********************** LOCAL FUNCTIONS ********************************/

static bool GetTempPoint(uint8_t *tempPoint, uint8_t tempVal)
{
	uint8_t idx = tempVal / TEMP_DIV;

	if (idx == MAX_TEMP_POINTS)
	{
		if (tempVal % TEMP_DIV == 0)
		{
			--idx;	// Round down ...
		}
	}

	if (idx >= MAX_TEMP_POINTS)
	{
		printf("%s(): calculated index=%d is above max=%d\n", __FUNCTION__, idx, MAX_TEMP_POINTS-1);
		return false;
	}
	else
	{
		*tempPoint = idx;
	}

	return true;
}

static bool GetPressPoint(uint8_t *pressPoint, uint8_t pressVal)
{
	uint8_t idx = pressVal / PRESS_DIV;

	if (idx == MAX_PRESSURE_POINTS)
	{
		if (pressVal % PRESS_DIV == 0)
		{
			--idx;	// Round down ...
		}
	}

	if (idx >= MAX_PRESSURE_POINTS)
	{
		printf("%s(): calculated index=%d is above max=%d\n", __FUNCTION__, idx, MAX_PRESSURE_POINTS-1);
		return false;
	}
	else
	{
		*pressPoint = idx;
	}

	return true;
}


/******************************* GLOBAL FUNCTIONS ***********************************/

float GetCoeff(const float coeffTable[MAX_TEMP_POINTS][MAX_PRESSURE_POINTS], uint8_t tempVal, uint8_t pressVal)
{
	uint8_t pIdx = 0;
	uint8_t tIdx = 0;
	float coeffVal = 0.0F;
	bool ok = true;

	ok = GetTempPoint(&tIdx, tempVal);
	if (ok == false)
	{
	   printf("Invalid value for temperature-point index! Value = %d\n", tIdx);
	}

	ok = GetPressPoint(&pIdx, pressVal);
	if (ok == false)
	{
	   printf("Invalid value for pressure-point index! Value = %d\n", pIdx);
	}

	if (ok)
	{
		coeffVal = coeffTable[tIdx][pIdx];
	}

	return coeffVal;	// Will be 0.0F in case of error ...
}

