#include <stdio.h>
#include "out/kcj_gda.h"

STACK_MKTYPE(int)

int main(void) {
    int_stack stack = {0};

    int_stack_psuh(&stack, 1);
    int_stack_psuh(&stack, 2);
    int_stack_psuh(&stack, 3);
    int_stack_psuh(&stack, 4);

    int el;
    while (int_stack_pop(&stack, &el)) {
        printf("%d\n", el);
    }
    return 0;
}