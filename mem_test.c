#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main(void){
    mem_init();

    // void *ptr8[25000];

    // for (int i = 1; i <= 25000; i++){
    //     ptr8[i] = my_malloc(i);
    //     if(ptr8[i] == NULL){
    //         printf("failed at %d\n", i);
    //         break;
    //     }
    // }


    // void *ptr1 = my_malloc(sizeof(char)); 

    void *ptr6 = my_malloc(1);
    void *ptr5 = my_malloc(2000);
    void *ptr7 = my_malloc(500);
    // void *ptr4 = my_malloc(2000); 
    void *ptr3 = my_malloc(200);

    print_blocks();
    memory_stat();  


    my_free(ptr7);
    print_blocks();
    memory_stat();

    my_free(ptr3);
    print_blocks();
    memory_stat();

    // printf("FOR 2000\n");
    my_free(ptr6);
    print_blocks();
    memory_stat();

    my_free(ptr5);
    print_blocks();
    memory_stat();
    void *ptr2 = my_malloc(200);

        print_blocks();
    memory_stat();

    return 0;
}