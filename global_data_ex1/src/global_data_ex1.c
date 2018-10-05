/*
 ============================================================================
 Name        : global_data_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


char globalString[25];     // illegal!
int globalInt = 0;         // compliant
int globalInt2;			   // illegal! (but probably safe ...) Default init value for integers =0 (for ALL compilers?)
float globalFloat;		   // illegal! (but probably safe ...) Default init value for floats =0.0F (for ALL compilers?)
float globalFloats[1000000];  // Probably safe - every element in array gets default value = 0.0F ... (but, can't rely on it!)


void SetGlobal(char *src)
{
    strncpy(globalString, src, sizeof(globalString));
}

void PrintGlobal(void)
{
   printf("%s", globalString);   // UNSAFE unless ‘SetGlobal()’ is called first!
}

void CheckGlobal(void)
{
	if (globalInt2 > 0)
	{
		printf("positive OK ...\n");
	}
	else if (globalInt2 < 0)
	{
		printf("negative OK ...\n");
	}
	else
	{
		printf("Zero value ...\n");
	}
}

void CheckGlobalFloat(void)
{
	if (globalFloat == 0)
	{
		printf("Zero value (0.0) ...\n");
	}
	else if (globalFloat < 0)
	{
		printf("Nonzero, negative value: %.5f\n", globalFloat);
	}
	else
	{
		printf("Nonzero, positive value: %.5f\n", globalFloat);
	}
}


int main(void)
{
	PrintGlobal();	// May be UNSAFE!

	CheckGlobal();
	CheckGlobal();
	CheckGlobal();

	++globalInt2;
	CheckGlobal();

	printf("globalInt2 should now be positive - right?\n");
	globalInt2 = 1;
	CheckGlobal();

	globalInt2 = -1;
	CheckGlobal();

	CheckGlobalFloat();
	CheckGlobalFloat();
	CheckGlobalFloat();

	globalFloat = 1;
	CheckGlobalFloat();

	globalFloat = -1;
	CheckGlobalFloat();

	// Check array elements:
	printf("globalFloats[254600] = %.5f\n", globalFloats[254600]);
	printf("globalFloats[768124] = %.5f\n", globalFloats[768124]);

	SetGlobal("This is IT!\n");
	PrintGlobal();	// safe now ...

	printf("Made it here (safely?) ...\n");

	return EXIT_SUCCESS;
}
