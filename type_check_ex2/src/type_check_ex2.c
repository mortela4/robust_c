/*
 ============================================================================
 Name        : type_check_ex2.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : using type-check macros in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//
#include <assert.h>


/// Check if void-pointer original type is as assumed
#define CHECKED_VOID_TYPE(original_type, p) ((void*) (1 ? p : (original_type*) 0))
/// Similar for INTs:
#define CHECKED_INT_TYPE(original_type, p) ((int*) (1 ? p : (original_type*) 0))
/// And FLOATs:
#define CHECKED_FLOAT_TYPE(original_type, p) ((float*) (1 ? p : (original_type*) 0))

/// Simplifications:
#define CHECK_INT_INT(p)		CHECKED_INT_TYPE(int,p)			// left-hand and right-hand types should be INT
#define CHECK_FLOAT_FLOAT(p)	CHECKED_FLOAT_TYPE(float,p)		// left-hand and right-hand types should be FLOAT


float IntFloatMult(int Ki, int Kf)
{
	return Ki * Kf;
}


int main(void)
{
	int y = 5000;
	float x = 5000.0;
	int *q = CHECK_INT_INT(&y);	// OK
	//float *p = CHECK_INT_INT(&y);	// Fails compilation (if warning=error) ...
	//float *z = CHECK_FLOAT_FLOAT(&y);	// Fails compilation (if warning=error) ...
	float *k = CHECK_FLOAT_FLOAT(&x);	// OK


	float product = IntFloatMult(*q, *k);
	printf("Result = %.5f\n", product);
	assert((int)product == 25000000);			// OK

	return EXIT_SUCCESS;
}
