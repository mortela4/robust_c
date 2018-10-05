/*
 ============================================================================
 Name        : array_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : demonstrates reading coefficients from LUT
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
//
#include "coeffs.h"


#define INCREMENT	50
#define MAX_VALUES	(MAX_TEMP_POINTS*MAX_PRESSURE_POINTS)


const float coeffTable[MAX_TEMP_POINTS][MAX_PRESSURE_POINTS] =
	{
			{1.1, 1.2, 1.3},
			{2.1, 2.2, 2.3},
			{3.1, 3.2, 3.3},
			{4.1, 4.2, 4.3}
	};



bool CheckValues(float fval)
{
	static unsigned int numValues = 0;
	static float ptMatrixValues[MAX_VALUES];		// 12 values

	if (numValues > 0)
	{
		for (int i=0; i<numValues; i++)
		{
			/* FLOAT-comparison = dangerous! */
			if (ptMatrixValues[i] == fval)
			{
				return false;
			}
		}
	}

	ptMatrixValues[numValues] = fval;
	++numValues;
	if (numValues > MAX_VALUES)
	{
		printf("%s(): ERROR: accumulated %d=MAX values!\n", __FUNCTION__, numValues);
		return false;
	}

	return true;
}


/************************************ TESTING **********************************/

int main(void)
{
    uint8_t tVal = INCREMENT;
    uint8_t pVal = INCREMENT;

    float fval = 0.0F;

    fval = GetCoeff((const float(*)[])&coeffTable, tVal, pVal);		// Ignore warning (for demo purpose) ...
	printf("Got coefficient value = %0.3f\n", fval);

	tVal += INCREMENT;
	pVal += INCREMENT;

	fval = GetCoeff((const float(*)[])coeffTable, tVal, pVal);		// Ignore warning (for demo purpose) ...
	printf("Got coefficient value = %0.3f\n", fval);

	tVal += INCREMENT;
	pVal += INCREMENT;

	fval = GetCoeff((const float(*)[])&coeffTable, tVal, pVal);		// Ignore warning (for demo purpose) ...
	printf("Got coefficient value = %0.3f\n", fval);


	/* Iterative test */
	for (tVal=0; tVal<UCHAR_MAX; tVal++)
	{
		for (pVal=0; pVal<UCHAR_MAX; pVal++)
		{
			fval = GetCoeff((const float(*)[])&coeffTable, tVal, pVal);
			if (CheckValues(fval))
			{
				printf("Coefficient value at temp=%d and pressure=%d: %0.2f\n", tVal, pVal, fval);
			}
		}
	}

	return EXIT_SUCCESS;
}
