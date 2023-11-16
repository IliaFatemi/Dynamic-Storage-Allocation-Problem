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

void* my_malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    MemoryBlock *current = &memory_block;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            // Split the block if it's larger than the requested size
            if (current->size > size + sizeof(MemoryBlock)) {
                MemoryBlock *newBlock = (MemoryBlock *)((char *)current->start + size);
                newBlock->start = (char *)current->start + size + sizeof(MemoryBlock);
                newBlock->size = current->size - size - sizeof(MemoryBlock);
                newBlock->free = true;

                current->size = size;
            }

            current->free = false;
            return current->start;
        }
        current = (MemoryBlock *)(((char *)current->start) + current->size + sizeof(MemoryBlock));
        if ((char *)current >= (char *)memory_block.start + memory_block.size) {
            current = NULL; // Reached end of memory block
        }
    }

    return NULL; // Memory allocation failed
}

void my_free(void *ptr){
    if (ptr == NULL) {
        return;
    }

    MemoryBlock *block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
    block->free = true;

    // Coalesce adjacent free blocks
    MemoryBlock *current = &memory_block;
    while (current != NULL) {
        if (current->free) {
            MemoryBlock *next = (MemoryBlock *)(((char *)current->start) + current->size + sizeof(MemoryBlock));
            if ((char *)next < (char *)memory_block.start + memory_block.size && next->free) {
                current->size += next->size + sizeof(MemoryBlock);
            }
        }
        if ((char *)current >= (char *)memory_block.start + memory_block.size) {
            break; // Reached end of memory block
        }
        current = (MemoryBlock *)(((char *)current->start) + current->size + sizeof(MemoryBlock));
    }
}
