/*
    Written by William Sutherland for 
    COMP20007 Assignment 1 2023 Semester 1
    Modified by Grady Fitzpatrick
    
    Header for module which contains stack-related
        data structures and functions.
*/
#ifndef STACK_H
#define STACK_H

#include "linkedList.h"

/* The data structure of the stack */
struct stack;

struct stack {
    struct Point *point;
    struct stack *below;
    int index;
};

/* Creates the stack */
struct stack *createStack(long double xcoord, long double ycoord, int idx);

/* Note that you are passing a pointer to the pointer of the stack
   into the below arguments */

/* Pops an item from the stack and returns the void pointer */
void pop(struct stack **s);

/* Push an item to the top of the stack */
void push(struct stack **s, long double xcoord, long double ycoord, int idx);

/* Frees the memory associated with the stack */
void freeStack(struct stack *s);

/* Getting the index of the top stack */
int getTop(struct stack *s);

/* Getting the index of the second top stack */
int getSecondTop(struct stack *s);

#endif
