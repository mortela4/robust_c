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


typedef bool (*validator_func_t)(int,int,int) ;
typedef bool (*validator_func_t)(int,int,int) ;

static inline bool is_valid_int(int input, int max, int min)
{
	return (input<max) && (input>min);
}

static inline bool is_valid_float(float input, int max, int min)
{
	return (input<max) && (input>min);
}


typedef struct
{
	int val;
	int max;
	int min;
	validator_func_t validate;
} qualified_value_t;

/// Possibly extend with this??
//typedef struct
//{
//	qualified_value_t* qvalPtr;
//} context_t;


qualified_value_t *MakeContext(const int max, const int min)
{
	static qualified_value_t qval =
	{
			.val = 0,
			.validate = is_valid_int
	};

	qval.max = max;
	qval.min = min;

	return &qval;
}


bool SetVal(qualified_value_t *ctx, int ival)
{
	int max = ctx->max;
	int min = ctx->min;

	bool status = ctx->validate(ival, max, min);

	if ( status )
	{
		printf("Setting value to %d\n", ival);
		ctx->val = ival;
	}
	else
	{
		printf("Value=%d is NOT valid - could not set!\n", ival);
	}

	return status;
}


int GetVal(const qualified_value_t *ctx)
{
	return ctx->val;
}


int main(void)
{
	qualified_value_t *context = MakeContext(MAX_VAL, MIN_VAL);

	int ival = 55;

	SetVal(context, ival);

	ival = -76;

	SetVal(context, ival);

	printf("Value is now: %d\n", GetVal(context));

	ival = -73;

	SetVal(context, ival);

	printf("Value is now: %d\n", GetVal(context));

	return EXIT_SUCCESS;
}
