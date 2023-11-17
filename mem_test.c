#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void){
    mem_init();

    void *ptr1 = my_malloc(sizeof(int)); 
    void *ptr2 = my_malloc(sizeof(1000));

    memory_status();

    return 0;
}