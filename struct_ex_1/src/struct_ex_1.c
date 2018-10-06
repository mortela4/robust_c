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


bool is_valid_int(int input)
{
	return (input<MAX_VAL) && (input>MIN_VAL);
}


typedef struct
{
	int val;
	validator_func_t validate;
} qualified_value_t;


int main(void)
{
	qualified_value_t qval = {.val = 0, .validate = is_valid_int};

	int ival = 55;

	if ( qval.validate(ival) )
	{
		printf("Setting value to %d\n", ival);
		qval.val = ival;
	}
	else
	{
		printf("Value=%d is NOT valid - could not set!\n", ival);
	}

	ival = -76;

	if ( qval.validate(ival) )
	{
		printf("Setting value to %d\n", ival);
		qval.val = ival;
	}
	else
	{
		printf("Value=%d is NOT valid - could not set!\n", ival);
	}

	return EXIT_SUCCESS;
}
