/*
 ============================================================================
 Name        : reg_access_ex1.c
 Author      : ml
 Version     :
 Copyright   : 
 Description : generic register access w. size-checking
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//
#include <inttypes.h>
#include <stdbool.h>
//
#include "regs_wrapper.h"


/******************************************** TESTING ... **********************************/

/* Actual registers */
reg32_t controlReg = { 0, 0xFFFFFFF0, false};
reg16_t statusReg = {0, 0xFFFFFFF8, true};
reg8_t dataReg = {0, 0xFFFFFFFC, false};


int main(void)
{
	uint8_t tst8 = 0x52;
	uint16_t tst16 = 0xACDC;
	uint32_t tst32 = 0xDEADBEEF;

	/* Checks: */
	REG_INFO(controlReg);
	REG_INFO(statusReg);
	REG_INFO(dataReg);

	/* Positive test */
	WRITE_REG(tst32, controlReg);
	printf("ControlReg-value is now = 0x%08X\n\n", controlReg.regVal);
	controlReg.regVal = 0xABCDEF77;  // Cheating - writes directly to register ...
	READ_REG(tst32, controlReg);
	printf("tst32-value is now = 0x%08X\n\n", tst32);

	/* Negative test */
	WRITE_REG(tst8, statusReg);
	printf("statusReg-value is now = 0x%04X\n\n", statusReg.regVal);  // unchanged ...
	statusReg.regVal = 0x1234;  // Cheating - writes directly to register (which actually is READONLY) ...
	READ_REG(tst8, statusReg);

	/* Positive again ... */
	READ_REG(tst16, statusReg);
	printf("tst16-value is now = 0x%04X\n\n", tst16);
	printf("... and statusReg-value is also = 0x%04X\n\n", statusReg.regVal);

	/* Negative - on READONLY condition ... */
	tst16 = 0xDCAC;
	WRITE_REG(tst16, statusReg);
	printf("statusReg-value is still = 0x%04X\n\n", statusReg.regVal);

	return EXIT_SUCCESS;
}
