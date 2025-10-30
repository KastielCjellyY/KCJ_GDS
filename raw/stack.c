// @inclStart
#include <malloc.h>
#include <stdint.h>
#include <stdbool.h>
// @inclEnd

#define __STACK_INIT_CAP 8

typedef int t;

typedef struct {
    t* items;
    size_t current;
    size_t capacity;
} t_1__stack;

bool t_1__stack_psuh(t_1__stack* stack, t el) {
    if (stack->current == stack->capacity) {
        t* newItems = realloc(stack->items, sizeof(t) * (stack->capacity == 0? __STACK_INIT_CAP : stack->capacity * 2));
        if (newItems == NULL) 
            return false;
        stack->capacity *= 2;
        stack->items = newItems;
    }
    stack->items[stack->current++] = el;
    return true;
}

bool t_1__stack_pop(t_1__stack* stack, t* el) {
    if (stack->current == 0) {
        return false;
    }
    *el = stack->items[--stack->current];
    return true;
}