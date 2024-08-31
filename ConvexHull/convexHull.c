/*
    Skeleton written by Grady Fitzpatrick for 
    COMP20007 Assignment 1 2024 Semester 1
    
    Header for module which contains convex hull 
        specification data structures and functions.

    Implemented by <YOU>
*/
#include "linkedList.h"
#include "problem.h"
#include "convexHull.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum orientationResult {
    COLLINEAR = 0,
    CLOCKWISE = 1,
    COUNTERCLOCKWISE = 2
};

/* Finds the orientation between the three given points - calculates the angle between 
    the Middle-First vector and Middle-Final vector - if the Middle-First vector is zero-length,
    the gradient of the Middle-Final vector is instead used. */
enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal);

enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal){
    assert(idxFirst >= 0 && idxFirst < p->numPoints);
    assert(idxMiddle >= 0 && idxMiddle < p->numPoints);
    assert(idxFinal >= 0 && idxFinal < p->numPoints);

    /* Use cross-product to calculate turn direction. */
    long double p0x = p->pointsX[idxFirst];
    long double p0y = p->pointsY[idxFirst];

    long double p1x = p->pointsX[idxMiddle];
    long double p1y = p->pointsY[idxMiddle];

    long double p2x = p->pointsX[idxFinal];
    long double p2y = p->pointsY[idxFinal];

    /* Cross product of vectors P1P0 & P1P2 */
    long double crossProduct = (p0x - p1x) * (p2y - p1y) - (p0y - p1y) * (p2x - p1x);

    if(crossProduct == 0){
        if(idxFirst == idxMiddle){
            /* Special case where we are only looking for positive slope of P1P2. */
            if(p2x == p1x){
                /* Special case: dx = 0, vertical */
                if(p2y < p1y){
                    /* Directly upwards */
                    return COUNTERCLOCKWISE;
                } else if(p2y == p1y){
                    /* Same point. */
                    return COLLINEAR;
                } else {
                    return CLOCKWISE;
                }
            }
            long double m = (p2y - p1y) / (p2x - p1x);
            if(m >= 0){
                return COUNTERCLOCKWISE;
            } else {
                return CLOCKWISE;
            }
            
        }
        return COLLINEAR;
    } else if(crossProduct > 0){
        return CLOCKWISE;
    } else {
        return COUNTERCLOCKWISE;
    }
}

struct solution *jarvisMarch(struct problem *p){
    /* Part A - perform Jarvis' March to construct a convex
    hull for the given problem. */
    struct linkedList *hull = newList();
    struct solution *s = (struct solution *) malloc(sizeof(struct solution));
    assert(s);
    s->operationCount = 0;
    
    /* Checking if number of points < 3 */
    if ((p->numPoints) < 3) {
        s->convexHull = hull;
        return s;
    }

    /* Finding the leftmost point */
    int leftMost = 0;
    for(int i = 1; i < (p->numPoints); i++) {
        if((p->pointsX)[i] < (p->pointsX)[leftMost]) {
            leftMost = i;
        }
    }

    int currPoint = leftMost, nextPoint;
    /* Inserting the points into the convex hull */
    do {
        insertTail(hull, (p->pointsX)[currPoint], (p->pointsY)[currPoint]);

        /* Getting the next point from a circular set of points */
        nextPoint = (currPoint + 1) % (p->numPoints);
        for(int i = 0; i < (p->numPoints); i++) {
            s->operationCount++;
            /* If a more counterclockwise point is found */
            if(orientation(p, currPoint, nextPoint, i) == COUNTERCLOCKWISE) {
                nextPoint = i;
            }
        }
        currPoint = nextPoint;
    } while(currPoint != leftMost);

    s->convexHull = hull;
    return s;
}

struct solution *grahamScan(struct problem *p){
    /* Part B - perform Graham's Scan to construct a convex
    hull for the given problem. */
    struct linkedList *hull = newList();
    struct solution *s = (struct solution *) malloc(sizeof(struct solution));
    assert(s);
    s->operationCount = 0;

    /* Checking if number of points < 3 */
    if ((p->numPoints) < 3) {
        s->convexHull = hull;
        return s;
    }

    /* Finding the point with the lowest y-coordinate */
    int lowest = 0;
    for(int i = 1; i < (p->numPoints); i++) {
        if((p->pointsY)[i] < (p->pointsY)[lowest]) {
            lowest = i;
        }
    }

    // Swapping the lowest to the front of the arrays
    swap(&p->pointsX[lowest], &p->pointsX[0]);
    swap(&p->pointsY[lowest], &p->pointsY[0]);

    /* Sorting the remaining points based on their polar angles with respect to lowest point */
    int min_idx = 0;
    double angle1, angle2;
    for(int i = 1; i < (p->numPoints) - 1; i++) {
        min_idx = i;
        angle1 = atan(((p->pointsY)[i] - (p->pointsY)[0]) / ((p->pointsX)[i] - (p->pointsX)[0]));
        if (angle1 < 0) {
            angle1 = M_PI + angle1;
        }
        for(int j = i + 1; j < (p->numPoints); j++) {
            angle2 = atan(((p->pointsY)[j] - (p->pointsY)[0]) / ((p->pointsX)[j] - (p->pointsX)[0]));
            if (angle2 < 0) {
                angle2 = M_PI + angle2;
            }
            s->operationCount++;
            if(angle2 < angle1) {
                min_idx = j;
                angle1 = angle2;
            }
        }
        if(min_idx != i) {
            swap(&(p->pointsX)[min_idx], &(p->pointsX)[i]);
            swap(&(p->pointsY)[min_idx], &(p->pointsY)[i]);
        }
    }

    /* Making and pushing points into the stack */
    struct stack *mainStack = createStack((p->pointsX)[0], (p->pointsY)[0], 0);
    push(&mainStack, (p->pointsX)[1], (p->pointsY)[1], 1);
    push(&mainStack, (p->pointsX)[2], (p->pointsY)[2], 2);

    /* Checking the number of points in the stack */
    int pointCount = 3;
    for(int i = 3; i < (p->numPoints); i++) {
        while(orientation(p, getSecondTop(mainStack), getTop(mainStack), i) != COUNTERCLOCKWISE) {
            pop(&mainStack);
            pointCount--;
        }
        push(&mainStack, (p->pointsX)[i], (p->pointsY)[i], i);
        pointCount++;
    }

    /* Inserting the stacks into the doubly linked list */
    struct stack *curr = mainStack;
    for(int i = 0; i < pointCount - 1; i++) {
        insertTail(hull, curr->point->x, curr->point->y);
        curr = curr->below;
    }
    insertHead(hull, curr->point->x, curr->point->y);

    s->convexHull = hull;
    return s;
}

void freeSolution(struct solution *s){
    if(! s){
        return;
    }
    if(s->convexHull){
        freeList(s->convexHull);
    }
    free(s);
}

/* Swapping the values */
void swap(long double *x, long double *y){
    long double temp = *x;
	*x = *y;
	*y = temp;
}


