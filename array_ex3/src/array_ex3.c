/*
 ============================================================================
 Name        : array_ex2.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : demonstrates reading coefficients from N*M LUT using SCAN/COMPARE
               (with deterministic lookup-time = k1*N + k2*M)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
//

#include "lut_coeffs.h"


#define TEMP_INCREMENT	30.0F  	// -55 to +85 yields 140degC --> 140/7 = 20, e.g. -55, -35, 5, 35, 65, 95
#define PRESS_INCREMENT	400.0F     // 150 to 1550 yields 1400mBar --> 1400/4 = 350, e.g. 150, 500, 850, 1200


const temp_comp_t compLut[MAX_TEMP_POINTS] =
	{
			{
					.tempVal = -50.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
					        .compVal = 1.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 1.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 1.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 1.4
						},
					}
			},
			{
					.tempVal = -30.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 2.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 2.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 2.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 2.4
						},
					}
			},
			{
					.tempVal = -10.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 3.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 3.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 3.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 3.4
						},
					}
			},
			{
					.tempVal = 10.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 4.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 4.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 4.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 4.4
						},
					}
			},
			{
					.tempVal = 30.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 5.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 5.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 5.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 5.4
						},
					}
			},
			{
					.tempVal = 50.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 6.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 6.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 6.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 6.4
						},
					}
			},
			{
					.tempVal = 80.0F,
					.pcompTable =
					{
						{
							.pressureVal = 150.0F,
							.compVal = 7.1,
						},
						{
							.pressureVal = 500.0F,
							.compVal = 7.2,
						},
						{
							.pressureVal = 850.0F,
							.compVal = 7.3
						},
						{
							.pressureVal = 1200.0F,
							.compVal = 7.4
						},
					}
			},
	};



/* Helper function (test only) */
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
#define UNIT_TEST

void AssertValues(float coeff)
{
#ifdef UNIT_TEST
   static int iteration = 0;

   const float coeffsTable[MAX_VALUES] =
   {
		   1.1F, 1.2F, 1.3F, 1.4F,
		   2.1F, 2.2F, 2.3F, 2.4F,
		   3.1F, 3.2F, 3.3F, 3.4F,
		   4.1F, 4.2F, 4.3F, 4.4F,
		   5.1F, 5.2F, 5.3F, 5.4F,
		   6.1F, 6.2F, 6.3F, 6.4F,
		   7.1F, 7.2F, 7.3F, 7.4F
   };
   const float delta = 0.001F;

   float value = coeffsTable[iteration];
   assert( (value - delta) <= coeff && coeff <= (value + delta) );
   printf("Test-iteration no.%d\n", iteration);
   ++iteration;
   if (iteration == MAX_VALUES)
   {
	   printf("Test finished OK.\n");
   }
#endif
}


/************************************** MAIN ***********************************/
int main(void)
{
    float fval = 0.0F;
    float tVal = -55.0F;

	/* Iterative test */
	for (uint8_t i=0; i<MAX_TEMP_POINTS; i++)
	{
		float pVal = 100.0F;

		for (uint8_t j=0; j<MAX_PRESSURE_POINTS; j++)
		{
			fval = GetCoeff(compLut, tVal, pVal);
			printf("Coefficient value at temp=%0.2f and pressure=%0.2f: %0.2f\n", tVal, pVal, fval);

			AssertValues(fval);

			pVal += PRESS_INCREMENT;
		}
		tVal += TEMP_INCREMENT;
	}

	return EXIT_SUCCESS;
}
