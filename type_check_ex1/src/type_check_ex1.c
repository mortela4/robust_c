/*
 ============================================================================
 Name        : type_check_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : type-checking in C, using macros.
 Note		 : type mismatch will produce warning only when casting -
 	 	 	 	 due to C limitations.
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


float IntFloatMult(int Ki, float Kf)
{
	return Ki * Kf;
}


int main(void)
{
	int y = 5000;
	void *q = CHECKED_VOID_TYPE(int, &y);	// OK

	float z = 50;
	//void *y = CHECKED_VOID_TYPE(int, &z);	// produces warning ... ("conflicting types for 'y'")
	void *p = CHECKED_VOID_TYPE(float, &z);

	float fltProduct1 = IntFloatMult(*(int *)q, *(float *)p);

	printf("Result 1 = %.5f\n", fltProduct1);
	assert((int)fltProduct1 == 250000);			// OK

	// Now failing to check yields horrible results ...
	int tst = 50;
	void *u = &tst;

	float fltProduct2 = IntFloatMult(*(int *)q, *(float *)u);

	printf("Result 2 = %f\n", fltProduct2);	// Result2 = 0.0 (w. GCC6.x at least ...)
	assert((int)fltProduct2 == 250000);		// Fails ...

	return EXIT_SUCCESS;
}
