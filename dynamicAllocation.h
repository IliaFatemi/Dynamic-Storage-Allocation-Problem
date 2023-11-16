#ifndef _DYNAMICALLOCATION_H_
#define _DYNAMICALLOCATION_H_
#include <stdlib.h>

void *my_malloc(size_t size);
void my_free(void *ptr);
void mem_init();

#endif