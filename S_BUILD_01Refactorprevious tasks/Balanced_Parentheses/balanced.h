#ifndef BALANCED_PARANTHETHES_H
#define BALANCED_PARANTHETHES_H

#include "Stack.h"
#include "std_types.h"

#define DIFF_BETWEEN_ASCII_ROUND_BRACKETS 1
#define DIFF_BETWEEN_ASCII_CURLY_BRACKETS 2





/*
*   -Description-
*-this function check if expression has balanced perantheses or not
*
*
*   -Input parameters -
*-1-pointer to array  (uint8_t *expression)
*
*   -Return-
*-1- (-2) the stack is empty
*-2- (-1) the expression isn't balanced
*-3- (0) otherwise
*/

int8_t isBalancedParanthethes(uint8_t *expression);

#endif // BALANCED_PARANTHETHES_H
