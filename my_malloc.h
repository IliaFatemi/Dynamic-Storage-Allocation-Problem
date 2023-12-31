#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

#define MEMORY_SIZE 1000000

enum memStat {FREE, ALLOCATED};

typedef struct MemoryBlock{
    size_t allocatedSize;
    size_t requestedSize;
    int status;
    void *startBlock;
    void *endBlock;
    struct MemoryBlock *prev;
    struct MemoryBlock *next;
} MemoryBlock;

typedef struct {
    size_t size;
    struct MemoryBlock *CurrentBlock;
    struct MemoryBlock *headBlock; 
} Memory;


void *my_malloc(size_t size);
void my_free(void *ptr);
void mem_init(void);

void memory_stat(void);
void print_blocks(void);
void reset_memory_allocation(void);

#endif