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


// Using inline functions for type-checking only:
static inline int *IntIntPtr(int *var)
{
	return var;
}

static inline float *FloatFloatPtr(float *var)
{
	return var;
}

static inline void *VoidIntPtr(int *var)
{
	return (void *)var;
}

static inline void *VoidFloatPtr(float *var)
{
	return (void *)var;
}


// Test func ...
float IntFloatMult(int Ki, float Kf)
{
	return Ki * Kf;
}


int main(void)
{
	int y = 5000;
	float x = 5000.0;

	int *q = IntIntPtr(&y);	// OK
	//int *p = IntIntPtr(&x);	// Warning ...
	float *k = FloatFloatPtr(&x);


	float product = IntFloatMult(*q, *k);
	printf("Int-Float product = %.5f\n", product);
	assert((int)product == 25000000);			// OK

	void *v1 = VoidIntPtr(&y);	// OK
	void *v2 = VoidFloatPtr(&x); // OK

	product = IntFloatMult(*(int *)v1, *(float *)v2);
	printf("Int-Float product2 = %.5f\n", product);
	assert((int)product == 25000000);			// OK

	void *v3 = VoidIntPtr(&x);	// not OK ...
	void *v4 = VoidFloatPtr(&y); // not OK ...

	product = IntFloatMult(*(int *)v3, *(float *)v4);
	printf("Int-Float product3 = %.5f\n", product);
	assert((int)product == 25000000);			// FAIL! (produces 0.0)

	return EXIT_SUCCESS;
}
