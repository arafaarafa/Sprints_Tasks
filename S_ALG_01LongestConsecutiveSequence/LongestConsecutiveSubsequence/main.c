#include <stdio.h>
#include <stdlib.h>

#include "insertion_sort.h"
#define GET_ARRRAY_SIZE(ARR)    sizeof(ARR)/sizeof(ARR[0])

void check_ret(int8_t ret_state, int32_t *array ,uint8_t size, uint32_t sizeofLCS);
int main()
{
    uint32_t sizeofLCS;
    uint8_t array_size;
    int8_t ret_state;


    int32_t array_TestCase1[] = {9,0,7,5,3,8,-10,4,2,1};
    int32_t array_TestCase3[] = {9,0,7,5,3,8,-10,4,2,1,6,12};
    int32_t array_TestCase4[] = {0,1,2,3,4,5,6,7,8,9};
    int32_t array_TestCase5[] = {2,8,4,10,6,20,16,12,14,16};


    printf("TEST CASE 1:\n");
    array_size = GET_ARRRAY_SIZE(array_TestCase1);
    printArray(array_TestCase1,array_size);
    ret_state = lcsGetSize(array_TestCase1, array_size, &sizeofLCS);
    check_ret(ret_state,array_TestCase1, array_size, sizeofLCS);
    printf("***************************************\n\n\n\n\n");
    printf("TEST CASE 3:\n");
    array_size = GET_ARRRAY_SIZE(array_TestCase3);
    printArray(array_TestCase3,array_size);
    ret_state = lcsGetSize(array_TestCase3, array_size, &sizeofLCS);
    check_ret(ret_state,array_TestCase3, array_size, sizeofLCS);
    printf("***************************************\n\n\n\n\n");
    printf("TEST CASE 4:\n");
    array_size = GET_ARRRAY_SIZE(array_TestCase4);
    printArray(array_TestCase4,array_size);
    ret_state = lcsGetSize(array_TestCase4, array_size, &sizeofLCS);
    check_ret(ret_state,array_TestCase4, array_size, sizeofLCS);
    printf("***************************************\n\n\n\n\n");
    printf("TEST CASE 5:\n");
    array_size = GET_ARRRAY_SIZE(array_TestCase5);
    printArray(array_TestCase5,array_size);
    ret_state = lcsGetSize(array_TestCase5, array_size, &sizeofLCS);
    check_ret(ret_state,array_TestCase5, array_size, sizeofLCS);
    printf("***************************************\n\n\n\n\n");





    return 0;
}
void check_ret(int8_t ret_state, int32_t *array, uint8_t size, uint32_t sizeofLCS){
    if(ret_state == -1){
            printf("The array is empty\n");
    }else if(ret_state == -2){
            printf("The array size is 0 or >10\n");
    }else if(ret_state == -3){
            printf("There is not LCS\n");
    }else if(ret_state == 0){
            printf("the array after sorting\n");
            printArray(array, size);
            printf("The LCS : %d\n", sizeofLCS);
    }else{

    }
}
