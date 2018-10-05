#ifndef MEMACCESS_WRAPPER_H_
#define MEMACCESS_WRAPPER_H_

#include <inttypes.h>
#include <stdbool.h>
//

#include "memaccess.h"


/* Crazy macros ... */
#define WRITE_MEM(x,y) 	WriteMem((void *)&x, sizeof(x), (void *)&y, (sizeof(y.memVal)))
#define READ_MEM(x,y)   ReadMem((void *)&x, sizeof(x), (void *)&y, (sizeof(y.memVal)))
#define MEM_INFO(y)     MemInfo((void *)&y, (sizeof(y.memVal)))


bool WriteMem(void *val, size_t varSize, void *mem, size_t memSize);
bool ReadMem(void *val, size_t varSize, void *mem, size_t memSize);
void MemInfo(void *mem, size_t memSize);


#endif /* MEMACCESS_WRAPPER_H_ */
