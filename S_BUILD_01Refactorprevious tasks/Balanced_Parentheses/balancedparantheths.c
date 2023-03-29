#include "balancedparantheths.h"

int8_t isBalancedParanthethes(uint8_t *expression){
    int8_t ret_state = -2;

    ST_stack_t stack;
    createEmptyStack(&stack);
    int8_t iterator = 0;
    while(expression[iterator] != '\0'){

        if(expression[iterator] == '{' || expression[iterator] == '('){
                push(&stack, expression[iterator]);
                ret_state = -1;

           }

        if(expression[iterator] == '}' || expression[iterator] == ')'){
                uint8_t tmp ;
                uint8_t stack_state ;
                stack_state = pop(&stack, &tmp);
                if((stack_state !=-2) && (((tmp+DIFF_BETWEEN_(_)) == expression[iterator])||((tmp+DIFF_BETWEEN_{_}) == expression[iterator]))){
                    ret_state = 0;
                }else{
                    ret_state = -1;
                    break;
                }

        }

        iterator++;
    }
    if(isEmpty(&stack) != -2){
        ret_state = -1;
    }

    return ret_state;
}
