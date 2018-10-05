#ifndef LUT_COEFFS_H_
#define LUT_COEFFS_H_


#include <inttypes.h>


#define MAX_TEMP_POINTS		7
#define MAX_PRESSURE_POINTS	4

#define MAX_VALUES			(MAX_TEMP_POINTS*MAX_PRESSURE_POINTS)



typedef struct
{
	float p1;
	float p2;
} coeff_pair_t;

typedef struct
{
	float pressureVal;
	float compVal;
} pressure_comp_t;

typedef struct
{
	float tempVal;
	pressure_comp_t pcompTable[MAX_PRESSURE_POINTS];
} temp_comp_t;


/***** PROTOs *****/
float GetCoeff(const temp_comp_t *coeffTable, float tempVal, float pressVal);


#endif /* LUT_COEFFS_H_ */
