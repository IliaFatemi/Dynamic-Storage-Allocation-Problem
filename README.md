# The General Dynamic Storage Allocation Problem
Author: Ilia Fatemi<br>
Assignment 3<br>
Course: CMPT 300 for Fall 2023<br>
Professor: Harinder Khangura<br>

## Algorithm Overview
1. <b>Initialization (`mem_init()`):</b>
   - Initializes the memory system by allocating an initial memory block of size `MEMORY_SIZE`.
   - The initial memory block is set with `malloc(sizeof(MemoryBlock) * MEMORY_SIZE)`
2. <b>Allocation (`my_malloc(size_t size)`):</b>
   - Allocates memory for a requested size.
   - Searches for free blocks in the memory to accommodate the requested size. When and if found, it will check to see if there is a free block and it will mark it as allocated. If space is available but larger than requested, split the block into an allocated block and a new free block.
   - Uses First Fit approach to allocating blocks.
   - Tracks allocated, free, and failed allocations
3. <b>Deallocation (`my_free(void *ptr)`):</b>
   - Frees memory associated with the given pointer
   - Merges adjacent free blocks if possible to avoid fragmentation.
   - Updates block statuses and sizes after deallocation.

## Data Structures Used
1. <b>`Memory` Structure:</b>
    - Holds metadata for each block in memory
    - Attributes:
      - `size_t size`: Total size of the memory block.
      - `struct MemoryBlock* CurrentBlock`: Pointer to the current memory block being processed
      - `struct MemoryBlock* headBlock`: Pointer to the head of the memory block list.
       
2. <b>`MemoryBlock` Structure:</b>
    - This holds the metadata for each block in memory.
    - Attributes:
      - `size_t allocatedSize`: Total size of the memory block.
      - `size_t requestedSize`: requested size
      - `void* startBlock`: Pointer to the start of the block
      - `void* endBlock`: Pointer to the end of the block.
      - `struct MemoryBlock* prev`: Pointer to the previous block.
      - `struct MemoryBlock* next`: Pointer to the next block.

## First-Fit Algorithm
`my_malloc(size_t size)` uses the First Fit approach algorithm for memory allocation. It iterates through the linked list of memory blocks, looking for a free block that can accommodate the requested size. Once a suitable free block is found:

- If the block exactly matches the requested size, it's allocated without creating a new free block.
- If the free block size is larger than the requested size, it's split into an allocated block and a new.
free block if the remaining free space is sufficient.

This approach allocates memory using the first available block that meets the size requirements, which aligns with the first fit strategy.

## Handling Memory Fragmentation
1. <b>Splitting Blocks:</b>
    - <b>Allocation:</b> When a requested size doesn't match an available block precisely, the code attempts to split a larger free block into two:
      - One allocated block matching the requested size.
      - A new free block representing the remaining space.
    - <b>Deallocation:</b> After freeing a block, the code merges with adjacent free blocks to prevent unnecessary fragmentation.

2. <b>Merging Blocks:</b>
    - <b>Deallocation:</b> Upon freeing memory, the code checks neighboring blocks:
      - If both previous and next blocks are free, they are merged into a single larger free block.
      - If only one neighboring block is free, it merges the free block with the deallocated block to prevent isolated free spaces.

3. <b>Optimizing Memory Usage:</b>
    - <b>Optimizing Memory Usage:</b>
      - <b>Allocation:</b> If there's sufficient space in a free block to fulfill a requested size, it utilizes that block rather than creating new ones.
      - <b>Deallocation:</b> Merges contiguous free blocks to create larger free blocks and reduce fragmentation.

## Time Complexity
1. `my_malloc`: The time complexity is linear O(N) concerning the number of blocks in the memory.
2. `my_free`: The time complexity is constant O(1) because it directly manipulates adjacent blocks without iterating through all blocks.

## Other
1. To change the memory size, `MEMORY_SIZE` is defined in `my_malloc.h` file.
2. `memory_stat()` will provide a summary and statistics of the memory.
3. `print_blocks()` will provide a table that summarizes the current state of modified blocks.
4. `reset_memory_allocation()` will reset the memory values and deallocating the `malloc()` created in `mem_init()`.
  






















