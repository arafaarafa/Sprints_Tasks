#include "stack.h"


void createEmptyStack(ST_stack_t *stack){

    for(int i=0 ; i<STACK_SIZE; i++){
        stack->elements[i]=0;
    }
    stack->top = -1;

}

int8_t push(ST_stack_t *stack, uint8_t data){
    int8_t ret_state = -1;
    if(isFull(stack) != -1){
        stack->top++;
        stack->elements[stack->top] = data;
        ret_state = 0;
    }
    return ret_state;
}

int8_t pop(ST_stack_t *stack, uint8_t *data){

    int8_t ret_state = -2;
    if(isEmpty(stack) != -2){

        *data = stack->elements[stack->top];
        stack->top--;
        ret_state = 0;
    }
    return ret_state;

}

int8_t printStack(ST_stack_t *stack){
    int8_t flag_to_print = 0;
    int8_t ret_state = -2;
    if(isFull(stack) == -1){
        ret_state = -1;
        flag_to_print=1;
    }else if(isEmpty(stack) == -2){
        ret_state = -2;
    }else{
        ret_state = 0;
        flag_to_print=1;
    }


    if(flag_to_print){
        for(int8_t i= stack->top; i > -1; i--){
        printf("%c\n",stack->elements[i]);
        }
    }else{
    }


    return ret_state;

}

int8_t getStackTop(ST_stack_t *stack, uint8_t *topData){

    int8_t ret_state = -2;

    if(isEmpty(stack) != -2){

        *topData = stack->elements[stack->top];
        ret_state = 0;
    }
    return ret_state;
}

int8_t isEmpty(ST_stack_t *stack){
    int8_t ret_state = -2;
    if(stack->top != -1){
        ret_state=0;
    }
    return ret_state;

}
int8_t isFull(ST_stack_t *stack){
    int8_t ret_state = -1;
    if(stack->top != (STACK_SIZE-1)){
        ret_state=0;
    }
    return ret_state;
}
