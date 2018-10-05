/*
 ============================================================================
 Name        : var_args_ex2.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


typedef enum
{
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3
} log_level_t;
const log_level_t LOG_LEVEL = INFO;
const char *levelPrefix[] = {"DEBUG: ", "INFO; ", "WARN: ", "ERROR: "};

char buf[100];
unsigned int msgCnt = 0;


void Logger(log_level_t logLevel, char *format, ...)
{
   va_list args;

   const char *prefix = levelPrefix[logLevel];
   int prefixSize = 0;

   if (LOG_LEVEL>logLevel)
   {
	   return; // PASS
   }

   prefixSize = strlen(prefix);
   strncpy(buf, prefix, prefixSize);

   va_start(args, format);
   vsnprintf(buf+prefixSize-1, sizeof(buf)-prefixSize, format, args);
   va_end(args);

   ++msgCnt;

   printf("%s\r\n", buf);	// Test print - use UartTx(buf) instead, or whatever ...
}

/* Wrapper */


int main ()
{
   Logger(INFO, " message no.%d, from line=%d in function: %s", msgCnt, __LINE__, __FUNCTION__);
   Logger(DEBUG, " message no.%d, from line=%d in function: %s", msgCnt, __LINE__, __FUNCTION__);
   Logger(WARN, " message no.%d, from line=%d in function: %s", msgCnt, __LINE__, __FUNCTION__);
   Logger(ERROR, " message no.%d, from line=%d in function: %s", msgCnt, __LINE__, __FUNCTION__);

   return(0);
}

