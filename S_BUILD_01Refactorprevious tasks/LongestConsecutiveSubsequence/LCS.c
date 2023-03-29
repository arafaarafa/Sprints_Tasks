#include "LCS.h"

int8_t lcsGetSize(int32_t * array, uint8_t arraySize, uint32_t *sizeofLCS){
    int8_t ret_state= insertionSort(array,arraySize);
    int8_t LCS=1;
    int8_t LCS_tmp = 1;
    if(ret_state == 0){
            for(int8_t i = 0; i< arraySize; i++){
                if(array[i+1] - array[i]== 1){
                    LCS_tmp++;
                    if(LCS < LCS_tmp)
                        LCS = LCS_tmp;
                }else{
                    LCS_tmp = 1;
                }
            }

        if(LCS == 1)
            ret_state = -3;
    }
    *sizeofLCS = LCS;
    return ret_state;


}
