#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

void my_malloc_test(){
    printf("\nRunning my_malloc_test....\n");
    mem_init();
    void *ptr[50];
    for(int i = 0; i < 50; i++){
        ptr[i] = my_malloc(1);
    }
    memory_stat();
    restore_memory();
    printf("\nmy_malloc_test Complete\n");
}

void my_free_test(){
    printf("\nRunning my_free_test....\n");
    mem_init();
    void *ptr[50];
    for(int i = 0; i < 50; i++){
        ptr[i] = my_malloc(1);
    }

    for(int i = 0; i < 50; i++){
        my_free(ptr[i]);
    }
    memory_stat();
    restore_memory();
    printf("\nmy_free_test Complete\n");
}

void simple_test1(){
    printf("\nRunning simple_test1....\n");
    mem_init();
    void *ptr6 = my_malloc(1);
    void *ptr5 = my_malloc(2000);
    void *ptr7 = my_malloc(500);
    void *ptr3 = my_malloc(200);
    my_free(ptr7);
    my_free(ptr3);
    my_free(ptr6);
    my_free(ptr5);
    void *ptr2 = my_malloc(200);
    my_free(ptr2);
    memory_stat();
    restore_memory();
    printf("\nsimple_test1 Complete\n");
}

void simple_test2(){
    printf("\nRunning simple_test2....\n");
    mem_init();
    void *ptr1 = my_malloc(1000);
    void *ptr2 = my_malloc(2000);
    void *ptr3 = my_malloc(5000);
    void *ptr4 = my_malloc(2000);
    void *ptr5 = my_malloc(20000);
    my_free(ptr1);
    my_free(ptr2);
    my_free(ptr3);
    my_free(ptr4);
    my_free(ptr5);
    memory_stat();
    restore_memory();
    printf("\nsimple_test2 Complete\n");
}

void stress_test1(){
    printf("\nRunning stress_test1....\n");
    mem_init();
    void *ptr[25000];
    for(int i = 0; i < 25000; i++){
        ptr[i] = my_malloc(1);
    }

    for(int i = 0; i < 25000; i++){
        my_free(ptr[i]);
    }
    memory_stat();
    restore_memory();
    printf("\nstress_test1 Complete\n");
}

void stress_test2(){
    printf("Running stress_test2....\n");
    mem_init();
    int success = 0;
    void *ptr[25000];
    for(int i = 0; i < 25000; i++){
        ptr[i] = my_malloc(1);
        if(ptr[i] != NULL){
            success++;
        }else{
            break;
        }
    }
    for(int i = 0; i < 200; i++){
        my_free(ptr[i]);
    }
    memory_stat();
    for(int i = 0; i < 200; i++){
        ptr[i] = my_malloc(1000);
        if(ptr[i] != NULL){
            success++;
        }else{
            break;
        }
    }
    memory_stat();
    for(int i = 0; i < success; i++){
        my_free(ptr[i]);
    }
    memory_stat();
    restore_memory();
    printf("\nstress_test2 Complete\n");
}

void stress_test3(){
    printf("Running stress_test3....\n");
    mem_init();
    int success = 0;
    void *ptr[35000];
    for(int i = 0; i < 35000; i++){
        ptr[i] = my_malloc(1);
    }
    for(int i = 0; i < 200; i++){
        my_free(ptr[i]);
    }
    for(int i = 0; i < 201; i++){
        ptr[i] = my_malloc(1);
    }
    for(int i = 0; i < 35000; i++){
        my_free(ptr[i]);
    }
    memory_stat();
    restore_memory();
    printf("\nstress_test3 Complete\n");
}

int main(void){

    my_malloc_test();
    my_free_test();
    simple_test1();
    simple_test2();
    stress_test1();
    stress_test2();
    stress_test3();

    return 0;
}