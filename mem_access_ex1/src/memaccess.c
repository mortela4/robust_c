#include "memaccess.h"

#include <stdio.h>
#include <stdlib.h>
//


/* Handy macros */
#define PRINT_MEM_INFO(x,y)	{ \
								printf("MEM-ADDR INFO:\n"); \
								printf("==============\n"); \
								printf("Memory address: 0x%08X\n", mem->memAddr); \
								printf("Memory value: 0x%0" #y "X\n", mem->memVal); \
							}
// Shortcuts:
#define PRINT_MEM_INFO_8	PRINT_MEM_INFO(8,2)
#define PRINT_MEM_INFO_16	PRINT_MEM_INFO(16,4)
#define PRINT_MEM_INFO_32	PRINT_MEM_INFO(32,8)


/* Low-level helpers */
void WriteMem8(uint8_t *val, mem8_t *mem)
{
	mem->memVal = *val;

}
void ReadMem8(uint8_t *var, mem8_t *mem)
{
	*var = mem->memVal;
}
void MemInfo8(mem8_t *mem)
{
	PRINT_MEM_INFO_8;
}


void WriteMem16(uint16_t *val, mem16_t *mem)
{
	mem->memVal = *val;
}
void ReadMem16(uint16_t *var, mem16_t *mem)
{
	*var = mem->memVal;
}
void MemInfo16(mem16_t *mem)
{
	PRINT_MEM_INFO_16;
}


void WriteMem32(uint32_t *val, mem32_t *mem)
{
	mem->memVal = *val;
}
void ReadMem32(uint32_t *var, mem32_t *mem)
{
	*var = mem->memVal;
}
void MemInfo32(mem32_t *mem)
{
	PRINT_MEM_INFO_32;
}

