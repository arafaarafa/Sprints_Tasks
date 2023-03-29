#include "insertion_sort.h"



int8_t insertionSort(int32_t *array, uint8_t arraySize){
    uint8_t ret_state= -1;
    if(array != NULL && (arraySize != 0 && arraySize<=10)){
            int32_t tmp_data;
            int8_t empty_pos = 0;
            for(int8_t i = 1; i<arraySize; i++){
                int32_t tmp_data =array[i];
                empty_pos = i;
                for(int8_t x = i-1; x>=0; x--){
                    if(tmp_data< array[x]){
                        array[empty_pos] = array[x];
                        empty_pos = x;
                    }

                }
                array[empty_pos] = tmp_data;
            }
           ret_state = 0;
    }else{
        ret_state= -2;
    }
    return ret_state;

}
void printArray(int32_t *array, uint8_t arraySize){

    for(int8_t i = 0; i< arraySize; i++){
        printf("%d ", array[i]);

    }
    printf("\n");

}
