#include <stdio.h>
#include <stdlib.h>
//
#include "regs_wrapper.h"


/* Top-level helpers */
bool WriteReg(void *val, size_t varSize, void *reg, size_t regSize)
{
	bool status = false;

	if (regSize != varSize)
	{
		printf("Fail - size mismatch - cannot WRITE!\n");
		printf("variable size = %d-bits, register size = %d-bits\n\n", (int)varSize*8, (int)regSize*8);
	}
	else
	{
		printf("WRITE-size OK ...\n");

		switch (regSize)
		{
		case 1: status = WriteReg8((uint8_t *)val, (reg8_t *)reg); break;
		case 2: status = WriteReg16((uint16_t *)val, (reg16_t *)reg); break;
		case 4: status = WriteReg32((uint32_t *)val, (reg32_t *)reg); break;
		default: printf("Write ERROR - only 8/16/32-bit registers supported!\n"); break;
		}
	}

	return status;
}

bool ReadReg(void *val, size_t varSize, void *reg, size_t regSize)
{
	if (regSize != varSize)
	{
		printf("Fail - size mismatch - cannot READ!\n");
		printf("variable size = %d-bits, register size = %d-bits\n\n", (int)varSize*8, (int)regSize*8);

		return false;
	}
	else
	{
		printf("OK to READ ...\n");

		switch (regSize)
		{
		case 1: ReadReg8((uint8_t *)val, (reg8_t *)reg); break;
		case 2: ReadReg16((uint16_t *)val, (reg16_t *)reg); break;
		case 4: ReadReg32((uint32_t *)val, (reg32_t *)reg); break;
		default: printf("Read ERROR - only 8/16/32-bit registers supported!\n\n"); break;
		}

		return true;
	}
}

void RegInfo(void *reg, size_t regSize)
{
	printf("regSize = %d bytes\n", (int)regSize);
	switch (regSize)
		{
		case 1: RegInfo8((reg8_t *)reg); break;
		case 2: RegInfo16((reg16_t *)reg); break;
		case 4: RegInfo32((reg32_t *)reg); break;
		default: printf("Read ERROR - only 8/16/32-bit registers supported!\n"); break;
		}
	printf("\n\n");
}


