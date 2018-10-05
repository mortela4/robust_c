/*
 ============================================================================
 Name        : var_args_ex3.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : Logging function example
 ============================================================================
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#define LOG_DBG(x,...)	Logger(DEBUG, __FILE__, __FUNCTION__, __LINE__, x, __VA_ARGS__)
#define LOG_INFO(x,...)	Logger(INFO, __FILE__, __FUNCTION__, __LINE__, x, __VA_ARGS__)
#define LOG_WARN(x,...)	Logger(WARN, __FILE__, __FUNCTION__, __LINE__, x, __VA_ARGS__)
#define LOG_ERR(x,...)	Logger(ERROR, __FILE__, __FUNCTION__, __LINE__, x, __VA_ARGS__)


typedef enum
{
	DEBUG = 0,
	INFO = 1,
	WARN = 2,
	ERROR = 3
} log_level_t;
const log_level_t LOG_LEVEL = INFO;
const char *levelPrefix[] = {"DEBUG: ", "INFO: ", "WARN: ", "ERROR: "};

char buf[255];


void Logger(log_level_t logLevel, const char *fileName, const char *funcName, int lineNum, char *format, ...)
{
	static unsigned int msgCnt = 0;
    static const char *header = " log-entry: %d\tfunction: %s()\tfile: %s\tline: %d\tmessage: ";

    va_list args;

    const char *prefix = levelPrefix[logLevel];
    int prefixSize = 0;

    // Suppress messages below setting for LOG_LEVEL:
    if (LOG_LEVEL>logLevel)
    {
	   return; // PASS
    }

    prefixSize = strlen(prefix);
    strncpy(buf, prefix, prefixSize);
    // Construct header as "<Level> - msg.no: <msgCnt>, function: <funcName>(), file: <fname>, line: <lineNum>: "
    snprintf(buf+prefixSize-1, sizeof(buf)-prefixSize, header, msgCnt, funcName, fileName, lineNum);
    // Test print header - use UartTx(buf) instead, or whatever ...
    printf("%s", buf);

    // Construct user message (overwrite existing buffer):

    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    ++msgCnt;

    printf("%s\r\n", buf);	// Test print user message - use UartTx(buf) instead, or whatever ...
}


int main ()
{
	int testNo = 1;

	LOG_INFO("This is test %d - type %s", testNo, "INFO");
	++testNo;
	LOG_DBG("This is test %d - type %s", testNo, "DEBUG");
	++testNo;
	LOG_WARN("This is test %d - type %s", testNo, "WARNING");
	++testNo;
	LOG_ERR("This is test %d - type %s", testNo, "ERROR");

	// No args - just a msg:
	LOG_INFO("This a simple message ...", NULL);

    return(0);
}

