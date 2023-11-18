#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void){
    mem_init();

    void *ptr1 = my_malloc(sizeof(char)); 
    void *ptr2 = my_malloc(4);
    void *ptr3 = my_malloc(2);
    void *ptr5 = my_malloc(2000);
    void *ptr4 = my_malloc(25000);

    memory_status();

    return 0;
}