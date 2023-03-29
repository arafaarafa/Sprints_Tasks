#ifndef LCS_H
#define LCS_H
#include "std_types.h"
#include "insertion_sort.h"


/*
*   -Description-
*-this function get the longest consecutive subsequence
*
*   -Input parameters -
*-1-variable to hold array size (uint8_t arraySize)
*
*   -Output parameters -
*-1-it holds the LCS value as return (uint32_t *sizeofLCS)

*   -Input-output parameters -
*-1-pointer to array of integer (int32_t *array)
*
*   -Return-
*- the type of return 8 bits integer
*   -Return cases-
*-1- (-1) if the array empty
*-2- (-2) if the array isn't size between 0 and 10
*-3- (-3) if there isn't LCS
*-3- (0) otherwise
*/
int8_t lcsGetSize(int32_t * array, uint8_t arraySize, uint32_t *sizeofLCS);

#endif // LCS_H
