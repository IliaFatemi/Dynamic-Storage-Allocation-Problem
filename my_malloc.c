#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Memory memory;
int NUM_BUSY_BLOCKS = 0, NUM_FREE_BLOCKS = 0, ALLOCATED_NODES = 0, FAILED_NODES = 0, DEALLOCATED_NODES = 0;;

void mem_init() {
    memory.size = MEMORY_SIZE;
    memory.headBlock = malloc(sizeof(MemoryBlock)*MEMORY_SIZE);
    memory.CurrentBlock = memory.headBlock;
    memory.CurrentBlock->requestedSize = 0;
    memory.CurrentBlock->allocatedSize = 0;
    memory.CurrentBlock->status = FREE;
    memory.CurrentBlock->startBlock = (char*)memory.headBlock + sizeof(MemoryBlock);
    memory.CurrentBlock->endBlock = (char*)memory.headBlock + MEMORY_SIZE;
    memory.CurrentBlock->prev = NULL;
    memory.CurrentBlock->next = NULL;
}

void* my_malloc(size_t size) {
    // Check for valid size and available memory...
    if (size <= 0 || size + sizeof(MemoryBlock) > memory.size) {
        printf("Invalid size or not enough memory\n");
        FAILED_NODES++;
        return NULL;
    }

    size_t totalRequestedSize = size + sizeof(MemoryBlock);
    MemoryBlock *block = memory.headBlock;

    while (block != NULL) {
        if (block->status == FREE && block->endBlock - block->startBlock == size) {
            // If the free block exactly matches the requested size, allocate it without creating a new free block
            block->status = ALLOCATED;
            block->requestedSize = size;
            block->allocatedSize = size;
            NUM_BUSY_BLOCKS++;

            memory.CurrentBlock = block->next;
            ALLOCATED_NODES++;
            return block->startBlock;
        }else if (block->status == FREE && block->endBlock - block->startBlock >= totalRequestedSize) {
            // If there's enough space in the free block to accommodate the requested size and a new free block
            MemoryBlock *allocatedBlock = block;
            allocatedBlock->status = ALLOCATED;
            allocatedBlock->requestedSize = size;
            allocatedBlock->allocatedSize = block->endBlock - block->startBlock;
            memory.CurrentBlock = allocatedBlock;
            NUM_BUSY_BLOCKS++;
            ALLOCATED_NODES++;

            // Calculate remaining free block size after allocation
            size_t remainingFreeSize = allocatedBlock->allocatedSize - totalRequestedSize;

            if (remainingFreeSize > sizeof(MemoryBlock)) {
                // Create a new free block only if remaining space is more than the size of a MemoryBlock
                MemoryBlock *newFreeBlock = (MemoryBlock*)((char*)allocatedBlock + totalRequestedSize);
                newFreeBlock->status = FREE;
                newFreeBlock->requestedSize = 0;
                newFreeBlock->allocatedSize = remainingFreeSize - sizeof(MemoryBlock);
                newFreeBlock->startBlock = (char*)newFreeBlock + sizeof(MemoryBlock);
                newFreeBlock->endBlock = allocatedBlock->endBlock;
                newFreeBlock->prev = allocatedBlock;
                newFreeBlock->next = allocatedBlock->next;
                allocatedBlock->endBlock = (char*)allocatedBlock + totalRequestedSize;
                allocatedBlock->allocatedSize = totalRequestedSize;
                

                if (allocatedBlock->next != NULL) {
                    allocatedBlock->next->prev = newFreeBlock;
                }

                allocatedBlock->next = newFreeBlock;
            }
            memory.size = (memory.size - size - sizeof(MemoryBlock));
            memory.CurrentBlock = allocatedBlock;

            return allocatedBlock->startBlock;
        }
        block = block->next;
    }
    FAILED_NODES++;
    printf("No available block of sufficient size\n");
    return NULL;
}

void my_free(void* ptr) {
    int neighborCheck = 0;
    bool addMemoryFromNextBlock = true, prevBlockAddedToMem = false;
    if (ptr == NULL) {
        printf("Cannot free NULL pointer\n");
        return;
    }

    // Calculate the MemoryBlock pointer associated with the given pointer
    MemoryBlock *block = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));

    if (block->status != ALLOCATED) {
        printf("Trying to free unallocated memory\n");
        return;
    }

    // Merge adjacent free blocks
    MemoryBlock *prevBlock = block->prev;
    MemoryBlock *nextBlock = block->next;

    size_t endOfMemory = (nextBlock->allocatedSize)+sizeof(MemoryBlock) - sizeof(MemoryBlock);

    if(endOfMemory == nextBlock->allocatedSize){
        addMemoryFromNextBlock = false;
    }

    if (prevBlock != NULL && prevBlock->status == FREE) {
        // Merge with the previous block
        neighborCheck++;
        memory.size += (block->allocatedSize);
        prevBlock->next = nextBlock;
        prevBlock->endBlock = block->endBlock;
        prevBlock->allocatedSize = prevBlock->allocatedSize + block->allocatedSize;
        prevBlockAddedToMem = true;
        NUM_BUSY_BLOCKS--;
        if (nextBlock != NULL) {
            nextBlock->prev = prevBlock;
        }
        // block = prevBlock;
    }

    if (nextBlock != NULL && nextBlock->status == FREE) {
        // Merge with the next block
        neighborCheck++;
        if(addMemoryFromNextBlock){
            memory.size += block->allocatedSize;
        }
        if(!prevBlockAddedToMem){
            memory.size += block->allocatedSize;
            NUM_BUSY_BLOCKS--;
        }

        block->next = nextBlock->next;
        block->endBlock = nextBlock->endBlock;
        block->allocatedSize = block->allocatedSize + nextBlock->allocatedSize;
        if (block->next != NULL) {
            block->next->prev = block;
        }
        // block = nextBlock;
    }

    if(neighborCheck != 1 && neighborCheck != 2){

        memory.size += block->allocatedSize;
        NUM_BUSY_BLOCKS--;
        NUM_FREE_BLOCKS++;
    }

    // Preserve the links between blocks if only a free block in the middle is removed
    if (prevBlock != NULL && prevBlock->status == ALLOCATED && nextBlock != NULL && nextBlock->status == ALLOCATED) {
        prevBlock->next = block;
        nextBlock->prev = block;
    }

    // Merge free blocks after deallocation if there's allocated memory in between
    if (prevBlock != NULL && prevBlock->status == FREE && nextBlock != NULL && nextBlock->status == FREE) {
        prevBlock->endBlock = nextBlock->endBlock;
        prevBlock->allocatedSize = prevBlock->endBlock - prevBlock->startBlock;
        prevBlock->next = nextBlock->next;
        NUM_FREE_BLOCKS--;
        if (nextBlock->next != NULL) {
            nextBlock->next->prev = prevBlock;
            NUM_FREE_BLOCKS--;
        }
    }

    // Mark the block as free
    block->status = FREE;
    block->requestedSize = 0;
    DEALLOCATED_NODES++;
}



void memory_stat(){
    printf("----------------------------SUMARY---------------------------\n");
    printf("Memory Size:" COLOR_GREEN " %.2LF%% %zu (bytes)\n" COLOR_RESET, ((long double)memory.size/(long double)MEMORY_SIZE)*100, memory.size);
    printf("Memory used:" COLOR_GREEN " %.2LF%% %zu (bytes)\n" COLOR_RESET,((long double)(MEMORY_SIZE - memory.size)/(long double)MEMORY_SIZE)*100, MEMORY_SIZE - memory.size);
    printf("Busy Blocks:" COLOR_GREEN " %.2f%% %d (blocks)\n" COLOR_RESET,((double)NUM_BUSY_BLOCKS/(double)(NUM_BUSY_BLOCKS+NUM_FREE_BLOCKS))*100, NUM_BUSY_BLOCKS);
    printf("Free Blocks:" COLOR_GREEN " %.2f%% %d (blocks)\n" COLOR_RESET, ((double)NUM_FREE_BLOCKS/(double)(NUM_BUSY_BLOCKS+NUM_FREE_BLOCKS))*100, NUM_FREE_BLOCKS);
    printf("Allocated:" COLOR_GREEN " %d (nodes)\n" COLOR_RESET, ALLOCATED_NODES);
    printf("Deallocated:" COLOR_GREEN " %d (nodes)\n" COLOR_RESET, DEALLOCATED_NODES);
    printf("Failed:" COLOR_GREEN " %d (nodes)\n" COLOR_RESET, FAILED_NODES);
    printf("Allocation Success Rate:" COLOR_GREEN " %.2f%%\n" COLOR_RESET, (double)ALLOCATED_NODES/(double)(ALLOCATED_NODES+FAILED_NODES)*100);
    printf("Deallocation Success Rate:" COLOR_GREEN " %.2f%%\n" COLOR_RESET, (double)DEALLOCATED_NODES/(double)(ALLOCATED_NODES)*100);
}

void print_blocks(void){
    int blockNum = 1;
    printf("\n\n  Current\t Block Start\tBlock End\tAllocated Size\tRequested Size\tBlock Status\tPrev Block\tNext Block\n");
    printf("  -------\t -----------\t---------\t--------------\t-------------\t------------\t----------\t----------\n");
    while(memory.CurrentBlock->prev != NULL){
        memory.CurrentBlock = memory.CurrentBlock->prev;
    }
    while(memory.CurrentBlock->next != NULL){
        
        if(memory.CurrentBlock->status == FREE){
            printf("%d %p %p %p\t%zu\t\t%zu\t\tFREE\t\t%p\t%p\n",blockNum, memory.CurrentBlock, memory.CurrentBlock->startBlock, memory.CurrentBlock->endBlock, memory.CurrentBlock->allocatedSize, memory.CurrentBlock->requestedSize, memory.CurrentBlock->prev, memory.CurrentBlock->next);
        }else{
            printf("%d %p %p %p\t%zu\t\t%zu\t\tBUSY\t\t%p\t%p\n",blockNum, memory.CurrentBlock, memory.CurrentBlock->startBlock, memory.CurrentBlock->endBlock, memory.CurrentBlock->allocatedSize, memory.CurrentBlock->requestedSize, memory.CurrentBlock->prev, memory.CurrentBlock->next);
        }
            memory.CurrentBlock = memory.CurrentBlock->next;
        blockNum++;
    }
    printf("\n\n");
}