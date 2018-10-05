#ifndef REGS_H_
#define REGS_H_

#include <stdint.h>
#include <stdbool.h>


#define PRINT_INFO()

typedef uint32_t reg_addr_t;
typedef struct
{
	uint8_t regVal;
	reg_addr_t regAddr;
	bool readOnly;
} reg8_t;
typedef struct
{
	uint16_t regVal;
	reg_addr_t regAddr;
	bool readOnly;
} reg16_t;
typedef struct
{
	uint32_t regVal;
	reg_addr_t regAddr;
	bool readOnly;
} reg32_t;


bool WriteReg8(uint8_t *val, reg8_t *reg);
void ReadReg8(uint8_t *var, reg8_t *reg);
void RegInfo8(reg8_t *reg);
//
bool WriteReg16(uint16_t *val, reg16_t *reg);
void ReadReg16(uint16_t *var, reg16_t *reg);
void RegInfo16(reg16_t *reg);
//
bool WriteReg32(uint32_t *val, reg32_t *reg);
void ReadReg32(uint32_t *var, reg32_t *reg);
void RegInfo32(reg32_t *reg);


#endif /* REGS_H_ */