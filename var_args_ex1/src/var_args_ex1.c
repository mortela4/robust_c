/*
 ============================================================================
 Name        : var_args_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char buf[100];

const char errorHeader[] = "ERROR: ";

#define  DEBUG_PRINT(...)  {snprintf(buf, sizeof(buf), __VA_ARGS__); printf("%s\r\n", buf);}
#define  ERROR_LOG(...)    {strncpy(buf, errorHeader, sizeof(errorHeader)); \
	                        snprintf(buf+sizeof(errorHeader)-1, sizeof(buf)-sizeof(errorHeader), __VA_ARGS__); \
	                        printf("%s\r\n", buf);}

int main(void)
{
	int errNo = -7;
	char errMsg[] = "memory corruption!";

	DEBUG_PRINT("ERROR no.%d", errNo);
	DEBUG_PRINT("Message: %s", errMsg);
	DEBUG_PRINT("Log: %s %d-%d", "message no", 1, 254);

	ERROR_LOG(" message no.%d, from line=%d in function: %s", 5, __LINE__, __FUNCTION__);

	return EXIT_SUCCESS;
}
