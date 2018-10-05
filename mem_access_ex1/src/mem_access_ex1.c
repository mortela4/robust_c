/*
 ============================================================================
 Name        : mem_access_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : generic memister access w. size-checking
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//
#include <inttypes.h>
#include <stdbool.h>
//

#include "memaccess_wrapper.h"


/******************************************** TESTING ... **********************************/

/* Actual memory addresses */
mem32_t memaddr32 = { 0, 0xFFFFFFF0};	// Can be accesses by 8-/16-/32-bit LHS-variables
mem16_t memaddr16 = {0, 0xFFFFFFF6};		// Can be accesses by 8- and 16-bit LHS-variables (but NOT 32-bit)
mem8_t memaddr8 = {0, 0xFFFFFFF3};		// Can only be accesses by 8-bit LHS-variables


int main(void)
{
	uint8_t tst8 = 0x52;
	uint16_t tst16 = 0xACDC;
	uint32_t tst32 = 0xDEADBEEF;

	/* Checks: */
	MEM_INFO(memaddr32);
	MEM_INFO(memaddr16);
	MEM_INFO(memaddr8);

	/* Positive test */
	WRITE_MEM(tst32, memaddr32);
	printf("ControlReg-value is now = 0x%08X\n\n", memaddr32.memVal);
	memaddr32.memVal = 0xABCDEF77;  // Cheating - writes directly to memaddr ...
	READ_MEM(tst32, memaddr32);
	printf("tst32-value is now = 0x%08X\n\n", tst32);

	/* Negative ... */
	WRITE_MEM(tst32, memaddr16);
	printf("memaddr16-value is still = 0x%04X\n\n", memaddr16.memVal);

	/* Positive test */
	WRITE_MEM(tst8, memaddr16);
	printf("memaddr16-value is now = 0x%04X\n\n", memaddr16.memVal);  // unchanged ...
	memaddr16.memVal = 0x1234;  // Cheating - writes directly to memaddr  ...
	READ_MEM(tst8, memaddr16);
	printf("8-bit access to 16-bit aligned address i legal!:-) tst8 is now = 0x%02X\n\n", tst8);  // changed ...

	/* Positive again ... */
	READ_MEM(tst16, memaddr16);
	printf("tst16-value is now = 0x%04X\n\n", tst16);
	printf("... and memaddr16-value is also = 0x%04X\n\n", memaddr16.memVal);

	/* Negative ... */
	tst16 = 0xDCAC;
	WRITE_MEM(tst16, memaddr8);
	printf("memaddr8-value is still = 0x%02X\n\n", memaddr8.memVal);

	return EXIT_SUCCESS;
}
