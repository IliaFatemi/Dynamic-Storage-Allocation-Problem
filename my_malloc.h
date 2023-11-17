#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

#define MEMORY_SIZE 25000 // Size of the memory block

enum memStat {FREE, ALLOCATED};

struct MemoryBlock{
    size_t size;
    int status;
    struct MemoryBlock *next;
};

typedef struct {
    size_t size;
    struct MemoryBlock *block;
    List *allocated_block;
} Memory;

// char MEMORY[MEMORY_SIZE];

void *my_malloc(size_t size);
void my_free(void *ptr);
void mem_init();

void* create_new_block(size_t memSize);

void memory_status(void);
void print_allocated(void);

#endif