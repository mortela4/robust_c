/*
 ============================================================================
 Name        : struct_ex_1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_VAL		75
#define MIN_VAL		-75

typedef bool (*validator_func_t)(int) ;


static inline bool is_valid_int(int input)
{
	return (input<MAX_VAL) && (input>MIN_VAL);
}


typedef struct
{
	int val;
	validator_func_t validate;
} qualified_value_t;


int SetGetVal(const int* ref)
{
	static qualified_value_t qval = {.val = 0, .validate = is_valid_int};

	if (ref != NULL)
	{
		// It's a SET:
		int ival = *ref;

		if ( qval.validate(ival) )
		{
			printf("Setting value to %d\n", ival);
			qval.val = ival;
		}
		else
		{
			printf("Value=%d is NOT valid - could not set!\n", ival);
		}
	}

	return qval.val;
}


int main(void)
{

	int ival = 55;

	(void)SetGetVal(&ival);

	ival = -76;

	(void)SetGetVal(&ival);

	printf("Value is now: %d\n", SetGetVal(NULL));	// Problem w. "C" - we use NULL to signify operation ... (not good)

	return EXIT_SUCCESS;
}
