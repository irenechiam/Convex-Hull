/*
    Written by Grady Fitzpatrick for 
    COMP20007 Assignment 1 2024 Semester 1
    
    Header for module which contains convex hull 
        specification data structures and functions.
*/

#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "stack.h"
#include "linkedList.h"
#include "problem.h"

struct solution;

struct solution {
    struct linkedList *convexHull;
    int operationCount;
};

/* Part A - perform Jarvis' March to construct a convex
    hull for the given problem. */
struct solution *jarvisMarch(struct problem *p);

/* Part B - perform Graham's Scan to construct a convex
    hull for the given problem. */
struct solution *grahamScan(struct problem *p);

/* Frees solution structure and all contained information. */
void freeSolution(struct solution *s);

/* Swapping values */
void swap(long double *x, long double *y);

#endif

