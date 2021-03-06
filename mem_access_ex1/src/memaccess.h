#ifndef MEMACCESS_H_
#define MEMACCESS_H_

#include <stdint.h>
#include <stdbool.h>


#define PRINT_INFO()

typedef uint32_t mem_addr_t;
typedef struct
{
	uint8_t memVal;
	mem_addr_t memAddr;
} mem8_t;
typedef struct
{
	uint16_t memVal;
	mem_addr_t memAddr;
} mem16_t;
typedef struct
{
	uint32_t memVal;
	mem_addr_t memAddr;
	bool readOnly;
} mem32_t;


void WriteMem8(uint8_t *val, mem8_t *mem);
void ReadMem8(uint8_t *var, mem8_t *mem);
void MemInfo8(mem8_t *mem);
//
void WriteMem16(uint16_t *val, mem16_t *mem);
void ReadMem16(uint16_t *var, mem16_t *mem);
void MemInfo16(mem16_t *mem);
//
void WriteMem32(uint32_t *val, mem32_t *mem);
void ReadMem32(uint32_t *var, mem32_t *mem);
void MemInfo32(mem32_t *mem);


#endif /* MEMACCESS_H_ */
