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

MemoryBlock memory_block;

void mem_init(){
    memory_block.start = malloc(MEMORY_SIZE);
    if(memory_block.start == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    memory_block.size = MEMORY_SIZE;
    memory_block.free = true;
}

void *my_malloc(size_t size){}

void my_free(void *ptr){}
