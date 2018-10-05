#include "lut_coeffs.h"

#include <inttypes.h>
#include <stdbool.h>
//
#include <stdio.h>
//


/*********************** LOCAL FUNCTIONS ********************************/

static bool GetTempPoint(const temp_comp_t *coeffTable, uint8_t *idxOut, float compTemp)
{
	uint8_t idx = 0;
	bool status = true;

	for (uint8_t i=0; i<MAX_TEMP_POINTS; i++)
	{
		/* DEBUG printout */
		float temp = coeffTable[i].tempVal;
		if (temp <= compTemp)
		{
			idx = i;	// TODO: checks for corner-case!
		}
	}

	if (idx >= MAX_TEMP_POINTS)
	{
		printf("%s(): calculated index=%d is above max=%d\n", __FUNCTION__, idx, MAX_TEMP_POINTS-1);
		status = false;
	}
	else
	{
		*idxOut = idx;
		status = true;
		printf("%s(): calculated temp-comp index=%d\n", __FUNCTION__, idx);
	}

	return status;
}

static bool GetPressPoint(const pressure_comp_t *pressPoint,  uint8_t *idxOut, float pressVal)
{
	uint8_t idx = 0;
	bool status = true;
	float pval = 0.0F;

	for (uint8_t i=0; i<MAX_PRESSURE_POINTS; i++)
	{
		pval = pressPoint[i].pressureVal;

		if (pval <= pressVal)
		{
			idx = i;	// TODO: checks for corner-case!
		}
	}

	if (idx >= MAX_PRESSURE_POINTS)
	{
		printf("%s(): calculated index=%d is above max=%d\n", __FUNCTION__, idx, MAX_PRESSURE_POINTS-1);
		status = false;
	}
	else
	{
		*idxOut = idx;
		status = true;
		printf("%s(): calculated pressure-comp index=%d\n", __FUNCTION__, idx);
	}

	return status;

}


/******************************* GLOBAL FUNCTIONS ***********************************/

float GetCoeff(const temp_comp_t *coeffTable, float tempValue, float pressValue)
{
	uint8_t pIdx = 0;
	uint8_t tIdx = 0;
	float coeffVal = 0.0F;
	bool ok = true;

	ok = GetTempPoint(coeffTable, &tIdx, tempValue);
	if (ok == false)
	{
	   printf("Invalid value for temperature-point index! Value = %d\n", tIdx);
	}

	const pressure_comp_t *pcomp = coeffTable[tIdx].pcompTable;

	ok = GetPressPoint(pcomp, &pIdx, pressValue);
	if (ok == false)
	{
	   printf("Invalid value for pressure-point index! Value = %d\n", pIdx);
	}

	if (ok)
	{
		coeffVal = coeffTable[tIdx].pcompTable[pIdx].compVal;	// NOTE: beware of indexes! Temp first, then Pressure!!
	}

	return coeffVal;	// Will be 0.0F in case of error ...
}

