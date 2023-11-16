#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_
#include <stdlib.h>

void *my_malloc(size_t size);
void my_free(void *ptr);
void mem_init();

int count_free_blocks();

#endif