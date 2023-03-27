#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "balancedparantheths.h"
int main()
{
    uint8_t *expression= "{(3+2)}";
    printf("TEST CASE (1)\" {(3+2)} \":  %d\n",isBalancedParanthethes(expression));

    expression = "{((3+2)}";
    printf("TEST CASE (2)\" {((3+2)} \":  %d\n",isBalancedParanthethes(expression));

    expression = "[(3+2)]";
    printf("TEST CASE (3)\" [(3+2)] \":  %d\n",isBalancedParanthethes(expression));

    expression = "{(3+2)/((3+3)*(15-10))}";
    printf("TEST CASE (4)\" {(3+2)/((3+3)*(15-10))} \":  %d\n",isBalancedParanthethes(expression));

    expression = "(3+2)/((3+3)*(15-10))";
    printf("TEST CASE (5)\" (3+2)/((3+3)*(15-10)) \":  %d\n",isBalancedParanthethes(expression));


    expression = "{{3+2)/((3+3)*(15-10)))";
    printf("TEST CASE (6)\" {{3+2)/((3+3)*(15-10))) \":  %d\n",isBalancedParanthethes(expression));

    expression = "{{3+2(/((3+3)*(15-10))}";
    printf("TEST CASE (7)\" {{3+2(/((3+3)*(15-10))} \":  %d\n",isBalancedParanthethes(expression));

    expression = "{(3+2)/((3+3(*)15-10))}";
    printf("TEST CASE (8)\" {(3+2)/((3+3(*)15-10))} \":  %d\n",isBalancedParanthethes(expression));

    expression = "})3+2)/((3+3)*(15-10))}";
    printf("TEST CASE (9)\" })3+2)/((3+3)*(15-10))} \":  %d\n",isBalancedParanthethes(expression));

    expression = "{(3+2)/(<3+3>*(15-10))}";
    printf("TEST CASE (10)\" {(3+2)/(<3+3>*(15-10))} \":  %d\n",isBalancedParanthethes(expression));
    return 0;
}
