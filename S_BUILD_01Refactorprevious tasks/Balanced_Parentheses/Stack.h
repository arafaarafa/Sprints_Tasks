#ifndef STACK_H
#define STACK_H

#include "std_types.h"

#define STACK_SIZE 10
typedef struct {
    uint8_t elements[STACK_SIZE];
    int8_t top;

} ST_stack_t;



/*
*   -Description-
*- create empty stack by init top by -1
*
*   -Input-output parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*
*   -Return-
*- void
*
*/
void createEmptyStack(ST_stack_t *stack);


/*
*   -Description-
*-this function push element to created stack
*
*   -Input parameters -
*-1-variable to hold data to push in stack (uint8_t data)
*
*
*   -Input-output parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*   -Return-
*- the type of return 8 bits integer
*   -Return cases-
*-1- (-1) the element didn't push because the stack full
*-2- (0) otherwise
*/
int8_t push(ST_stack_t *stack, uint8_t data);



/*
*   -Description-
*-this function pop element from stack
*
*
*   -Output parameters -
*-1-it holds the poped value (uint8_t *data)

*   -Input-output parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*   -Return-
*-1- (-2) there isn't element to pop
*-2- (0) otherwise
*/
int8_t pop(ST_stack_t *stack, uint8_t *data);


/*
*   -Description-
*-this function print all elements and it's status
*
*
*   -Input parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*   -Return-
*-1- (-2) the stack is empty
*-2- (-1) the stack is full
*-3- (0) otherwise
*/
int8_t printStack(ST_stack_t *stack);



/*
*   -Description-
*-this function get top data of stack
*
*
*   -Input parameters -
*-1-pointer to stack (ST_stack_t *stack)

*   -Output parameters -
*-1-it holds the top value of stack (uint8_t *topData)
*
*   -Return-
*-1- (-2) the stack is empty
*-2- (0) otherwise
*/
int8_t getStackTop(ST_stack_t *stack, uint8_t *topData);



/*
*   -Description-
*-this function get state of stack if it is empty or not
*
*
*   -Input parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*   -Return-
*-1- (-2) the stack is empty
*-2- (0) otherwise
*/
int8_t isEmpty(ST_stack_t *stack);

/*
*   -Description-
*-this function get state of stack if it is full or not
*
*
*   -Input parameters -
*-1-pointer to stack (ST_stack_t *stack)
*
*   -Return-
*-1- (-1) the stack is full
*-2- (0) otherwise
*/
int8_t isFull(ST_stack_t *stack);

#endif // STACK_H
