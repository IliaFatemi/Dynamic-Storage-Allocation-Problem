#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void){
    mem_init();

    void *ptr1 = my_malloc(50);
    void *ptr2 = my_malloc(200);
    void *ptr3 = my_malloc(100);


    my_free(ptr1);
    my_free(ptr2);
    my_free(ptr3);

    int available_blocks = count_free_blocks();
    printf("Available free blocks: %d\n", available_blocks);


    return 0;
}