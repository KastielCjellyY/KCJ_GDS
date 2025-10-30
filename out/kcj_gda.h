#ifndef __KCJ_GDS_H__
#include <stdbool.h>
#include <malloc.h>
#include <stdint.h>


#define __STACK_INIT_CAP 8

#define STACK_MKTYPE(t) \
 \
typedef struct { \
t* items; \
size_t current; \
size_t capacity; \
} t##_stack; \
 \
bool t##_stack_psuh(t##_stack* stack, t el) { \
if (stack->current == stack->capacity) { \
t* newItems = realloc(stack->items, sizeof(t) * (stack->capacity == 0? __STACK_INIT_CAP : stack->capacity * 2)); \
if (newItems == NULL) \
return false; \
stack->capacity *= 2; \
stack->items = newItems; \
} \
stack->items[stack->current++] = el; \
return true; \
} \
 \
bool t##_stack_pop(t##_stack* stack, t* el) { \
if (stack->current == 0) { \
return false; \
} \
*el = stack->items[--stack->current]; \
return true; \
} \


#define __KCJ_GDS_H__
#endif
