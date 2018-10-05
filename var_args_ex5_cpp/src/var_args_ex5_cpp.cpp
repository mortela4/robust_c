//============================================================================
// Name        : var_args_ex4_cpp.cpp
// Author      : ml
// Version     :
// Copyright   : 
// Description : varargs in C++ (>=C++11) shows use of variadic template.
//               (contrasts use of varargs in plain "C" ...)
//============================================================================

#include <iostream>
#if CPP_CXX20
#include <experimental>		// Only found in C++20 ('Modules TS')
#endif
//
#include <stdio.h>
#include <string.h>

using namespace std;

#define DLOG(x,...)	Logging(NULL, 0, NULL, x, NULL)
#define SLOG(x,...)	Logging(NULL, 0, NULL, x, __VA_ARGS__)
#define ELOG(x,...)	Logging(__FILE__, __LINE__, __FUNCTION__, x, __VA_ARGS__)


#if CPP_CXX20
template<typename... Args>
void Logging(std::experimental::source_location loc = std::experimental::source_location::current(), const char *format, Args... args)
{
	char buf[100];

	snprintf(buf, sizeof(buf), "LOG: file: %s\tline: %d\tfunction: %s()", loc.file_name, loc.line, loc.function_name);

	// Test prefix output ...
	printf("%s", buf);

    snprintf(buf, sizeof(buf), format, args...);

    // Test message output ...
    printf("%s\r\n", buf);
}
#else
// Using template w. default arguments:
template<typename... Args>
void Logging(const char *fileName = NULL, const int lineNo = 0, const char *funcName = NULL, const char *format = NULL, Args... args)
{
	static char buf[100];

	if (fileName != NULL)
	{
		snprintf(buf, sizeof(buf), "LOG: file: %s\tline: %d\tfunction: %s()\tmessage: ", fileName, lineNo, funcName);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%s", "LOG: message: ");
	}

	// Test prefix output ...
	printf("%s", buf);

    snprintf(buf, sizeof(buf), format, args...);

    // Test output ...
    printf("%s\r\n", buf);
}
#endif


int main()
{
  int a = 2;

  SLOG("%s\n", "test");
  SLOG("%s %d %d %p\n", "second test", 2, a, &a);
  DLOG("And - no varargs at all!");

  ELOG("%s\n", "test");
  ELOG("%s %d %d %p\n", "second test", 2, a, &a);
  ELOG("And - no varargs at all!", NULL);          // NULL to make preprocessor happy (when expanding LOG()-macro)

  return 0;
}
