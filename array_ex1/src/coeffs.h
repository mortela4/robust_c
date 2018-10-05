#ifndef COEFFS_H_
#define COEFFS_H_

#define MAX_TEMP_POINTS		4
#define MAX_PRESSURE_POINTS	3

#define TEMP_DIV			(256/(MAX_TEMP_POINTS))
#define PRESS_DIV			(256/(MAX_PRESSURE_POINTS))


typedef struct
{
	float p1;
	float p2;
} coeff_pair_t;


float GetCoeff(const float coeffTable[MAX_TEMP_POINTS][MAX_PRESSURE_POINTS], uint8_t tempVal, uint8_t pressVal);


#endif /* COEFFS_H_ */
