#include "list.h"
#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct to represent a block of memory

Memory memory;

void mem_init() {
    memory.size = MEMORY_SIZE;
    memory.headBlock = malloc((MEMORY_SIZE));
    memory.CurrentBlock = memory.headBlock;
    memory.CurrentBlock->Allocatedsize = MEMORY_SIZE;
    memory.CurrentBlock->status = FREE;
    memory.CurrentBlock->startBlock = (char*)memory.headBlock;
    memory.CurrentBlock->endBlock = (char*)memory.headBlock + MEMORY_SIZE;
    memory.CurrentBlock->prev = NULL;
    memory.CurrentBlock->next = NULL;
}

void* my_malloc(size_t size) {
    if (size <= 0 || size > memory.size) {
        printf("Invalid size or not enough memory\n");
        return NULL;
    }

    MemoryBlock *block = memory.headBlock;

    while (block != NULL) {
        // printf("%p %zu\n", block, sizeof(MemoryBlock));
        if (block->status == FREE && block->Allocatedsize >= size) {
            MemoryBlock *allocatedBlock = block;
            allocatedBlock->status = ALLOCATED;
            allocatedBlock->Allocatedsize = MEMORY_SIZE  - size;
            
            MemoryBlock *newBlock = (MemoryBlock*)((char*)allocatedBlock + size + sizeof(MemoryBlock));
            newBlock->status = FREE;
            newBlock->Allocatedsize = MEMORY_SIZE  - size;
            newBlock->startBlock = (char*)allocatedBlock;
            newBlock->endBlock = (char*)allocatedBlock + size;
            newBlock->prev = allocatedBlock;
            newBlock->next = allocatedBlock->next;
            newBlock->requestedSize = size;

            allocatedBlock->next = newBlock;
            if (newBlock->next != NULL) {
                newBlock->next->prev = newBlock;
            }

            memory.size -= size;
            memory.CurrentBlock = newBlock;
            // printf("----\n");
            return allocatedBlock->startBlock;
        }
        block = block->next;
    }
    printf("No available block of sufficient size\n");
    return NULL;
}

void my_free(void* ptr){

}

void memory_status(){
    printf("Memory Size: %zu\n\n", memory.size);
    Memory temp = memory;
    
    while(temp.CurrentBlock->prev != NULL){
        temp.CurrentBlock = temp.CurrentBlock->prev;
    }
    
    while(temp.CurrentBlock->next != NULL){
        temp.CurrentBlock = temp.CurrentBlock->next;
        printf("Current: %p\nstart: %p\nEnd: %p\nAllocated block Size: %zu\nRequested size: %zu\n\n",temp.CurrentBlock, temp.CurrentBlock->startBlock, temp.CurrentBlock->endBlock, temp.CurrentBlock->Allocatedsize, temp.CurrentBlock->requestedSize);
    }
}