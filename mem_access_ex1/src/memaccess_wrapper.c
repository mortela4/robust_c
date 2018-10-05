#include "memaccess_wrapper.h"

#include <stdio.h>
#include <stdlib.h>
//


/* Top-level helpers */
bool WriteMem(void *val, size_t varSize, void *mem, size_t memSize)
{
	bool status = true;

	if (varSize > memSize)
	{
		printf("Fail - size mismatch - cannot WRITE atomic!\n");
		printf("variable size = %d-bits, memory address is %d-bit aligned.\n\n", (int)varSize*8, (int)memSize*8);
		status = false;
	}
	else
	{
		if (varSize < memSize)
		{
			printf("WARNING: WRITE-size mismatch - variable location smaller than address alignment! (truncation OK?)\n");
		}
		else
		{
			printf("WRITE-size OK (size match) ...\n");
		}
		/* VARIABLE size determines actual type of access */
		switch (varSize)
		{
		case 1: WriteMem8((uint8_t *)val, (mem8_t *)mem); break;
		case 2: WriteMem16((uint16_t *)val, (mem16_t *)mem); break;
		case 4: WriteMem32((uint32_t *)val, (mem32_t *)mem); break;
		default: printf("Write ERROR - only 8/16/32-bit access supported!\n"); status = false; break;
		}
	}

	return status;
}

bool ReadMem(void *val, size_t varSize, void *mem, size_t memSize)
{
	bool status = true;

	if (varSize > memSize)
	{
		printf("Fail - size mismatch - cannot READ atomic!\n");
		printf("variable size = %d-bits, memory address is %d-bit aligned.\n\n", (int)varSize*8, (int)memSize*8);
		status = false;
	}
	else
	{
		if (varSize < memSize)
		{
			printf("WARNING: READ-size mismatch - variable location smaller than address alignment! (truncation OK?)\n");
		}
		else
		{
			printf("READ-size OK (size match) ...\n");
		}
		/* VARIABLE size determines actual type of access */
		switch (varSize)
		{
		case 1: ReadMem8((uint8_t *)val, (mem8_t *)mem); break;
		case 2: ReadMem16((uint16_t *)val, (mem16_t *)mem); break;
		case 4: ReadMem32((uint32_t *)val, (mem32_t *)mem); break;
		default: printf("Read ERROR - only 8/16/32-bit access supported!\n\n"); status = false; break;
		}
	}

	return status;
}

void MemInfo(void *mem, size_t memOffset)
{
	printf("memSize = %d bytes\n", (int)memOffset);
	switch (memOffset)
		{
		case 1: MemInfo8((mem8_t *)mem); break;
		case 2: MemInfo16((mem16_t *)mem); break;
		case 4: MemInfo32((mem32_t *)mem); break;
		default: printf("Read ERROR - only 8/16/32-bit memory address steps supported!\n"); break;
		}
	printf("\n\n");
}


