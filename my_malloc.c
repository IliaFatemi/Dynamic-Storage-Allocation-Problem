#include "list.h"
#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct to represent a block of memory

Memory memory;

void mem_init() {
    memory.size = MEMORY_SIZE;
    memory.block = malloc(MEMORY_SIZE);
    memory.block->status = FREE;
    memory.block->next = NULL;
    memory.allocated_block = List_create();
}

void* my_malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }
    if (size > memory.size){
        printf("No space to allocate this data\n");
        return NULL;
    }

    void *tmp = memory.block;
    if(List_count(memory.allocated_block) == 0){
        memory.block->status = ALLOCATED;
        memory.block->size = size;
        memory.block->next = tmp - size;
        List_append(memory.allocated_block, memory.block);
        memory.size -= size;
        memory.block = memory.block->next;
        printf("temp: %p\nnew: %p\nsize: %zu\n", tmp, memory.block, size);
        memory.block->status = FREE;
        memory.block->next = NULL;
        return tmp;
    }else if (memory.block->status == FREE){
        memory.block->status = ALLOCATED;
        memory.block->size = size;
        memory.block->next = tmp - size;
        List_append(memory.allocated_block, memory.block);
        memory.size -= size;
        memory.block = memory.block->next;
        memory.block->next = NULL;
        memory.block->status = FREE;
        return tmp;
    }
    return NULL;
}

void my_free(void* ptr) {

}



void print_allocated(){
    printf("%p %d %zu\n", &memory.block, memory.block->status, memory.block->size);
}

void memory_status(){
    printf("Memory size: %zu\n", memory.size);
    printf("Allocated Data: %d\n", List_count(memory.allocated_block));
    printf("%p\n", List_first(memory.allocated_block));
    for(int i = 1; i < List_count(memory.allocated_block); i++){
        printf("%p\n", List_next(memory.allocated_block));
    }
}