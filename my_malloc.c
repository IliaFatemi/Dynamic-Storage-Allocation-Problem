#include "list.h"
#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000 // Size of the memory block

// Struct to represent a block of memory
typedef struct {
    void *start;
    size_t size;
    bool free;
} MemoryBlock;

MemoryBlock memoryBlock;

void *my_malloc(size_t size){}

void my_free(void *ptr){}

void mem_init(){}