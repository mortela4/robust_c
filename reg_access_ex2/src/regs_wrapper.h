#ifndef REGS_WRAPPER_H_
#define REGS_WRAPPER_H_

#include <inttypes.h>
#include <stdbool.h>
//
#include "regs.h"


/* Crazy macros ... */
#define WRITE_REG(x,y) 	WriteReg((void *)&x, sizeof(x), (void *)&y, (sizeof(y.regVal)))
#define READ_REG(x,y)   ReadReg((void *)&x, sizeof(x), (void *)&y, (sizeof(y.regVal)))
#define REG_INFO(y)     RegInfo((void *)&y, (sizeof(y.regVal)))


bool WriteReg(void *val, size_t varSize, void *reg, size_t regSize);
bool ReadReg(void *val, size_t varSize, void *reg, size_t regSize);
void RegInfo(void *reg, size_t regSize);


#endif /* REGS_WRAPPER_H_ */
