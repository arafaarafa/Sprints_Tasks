#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stddef.h>
#include "std_types.h"


/*
*   -Description-
*-this function sort array of integers by insertion sort algorithm
*   -Input parameters -
*-1-variable to hold array size (uint8_t arraySize)
*
*   -Input-output parameters -
*-1-pointer to array of integer (int32_t *array)
*
*   -Return-
*- the type of return 8 bits integer
*   -Return cases-
*-1- (-1) if the array empty
*-2- (-2) if the array isn't size between 0 and 10
*-3- (0) otherwise
*/
int8_t insertionSort(int32_t *array, uint8_t arraySize);

/*
*   -Description-
*-this function print the array
*   -Input parameters -
*-1-pointer to array of integer (int32_t *array)
*-2-variable to hold array size (uint8_t arraySize)
*
*   -Return-
*- the type of return VOID
*
*/
void printArray(int32_t *array, uint8_t arraySize);



#endif // INSERTION_SORT_H
