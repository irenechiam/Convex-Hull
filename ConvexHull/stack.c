/*
    Written by William Sutherland for 
    COMP20007 Assignment 1 2023 Semester 1
    Modified by Grady Fitzpatrick
    
    Implementation for module which contains
        stack-related data structures and 
        functions.
*/
#include "linkedList.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct stack *createStack(long double xcoord, long double ycoord, int idx) {
    struct stack *s = (struct stack *) malloc(sizeof(struct stack));
    assert(s);
    s->point = (struct Point*)malloc(sizeof(struct Point));
    s->point->x = xcoord;
    s->point->y = ycoord;
    s->index = idx;
    s->below = NULL;
    return s;
}

void pop(struct stack **s) {
    free((*s)->point);
    struct stack *b = (*s)->below;
    free(*s);
    *s = b;
}

void push(struct stack **s, long double xcoord, long double ycoord, int idx) {
    if (!s || !*s) {
        *s = createStack(xcoord, ycoord, idx);
        assert(s);
    }
    
    struct stack *top = createStack(xcoord, ycoord, idx);
    assert(s);
    top->below = *s;
    *s = top;
}

void freeStack(struct stack *s) {
    for (struct stack *curr = s; curr != NULL; s = curr) {
        free(curr->point);
        curr = curr->below;
        free(s);
    }
}

/* Getting the index of the top stack */
int getTop(struct stack *s) {
    return s->index;
}

/* Getting the index of the second top stack */
int getSecondTop(struct stack *s) {
    struct stack *curr = s->below;
    return curr->index;
}

