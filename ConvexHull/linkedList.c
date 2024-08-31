/*
    Skeleton written by Grady Fitzpatrick for 
    COMP20007 Assignment 1 2024 Semester 1
    
    Implementation details for module which contains doubly-linked list 
        specification data structures and functions.
    
    Implemented by <YOU>
*/

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct linkedListNode{
    struct Point *point;
    struct linkedListNode *prev;
    struct linkedListNode *next;
};

struct linkedList{
    struct linkedListNode *head;
    struct linkedListNode *tail;
};

/* Print out each value in the list from the first value to the final value.
    Each value is printed with the format "(x, y) " where x is the x value
    set when inserting the item and y is the y value set when inserting 
    the item. */
void traverseRingForward(struct linkedList *list){
    struct linkedListNode *curr = list->head;
    while(curr != NULL) {
        printf("(%Lf, %Lf) ", curr->point->x, curr->point->y);
        curr = curr->next;
    }
}

/* Print out first the first item of the list, then print out each value in 
    the list from the final value to the second value.
    Each value is printed with the format "(x, y) " where x is the x value
    set when inserting the item and y is the y value set when inserting 
    the item. */
void traverseRingBackwards(struct linkedList *list){
    struct linkedListNode *curr = list->tail;
    printf("(%Lf, %Lf) ", list->head->point->x, list->head->point->y);
    while(curr != list->head) {
        printf("(%Lf, %Lf) ", curr->point->x, curr->point->y);
        curr = curr->prev;
    }
}

/* Return a new empty list. */
struct linkedList *newList(void){
    struct linkedList *list;
    list = (struct linkedList*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->tail = NULL;
    return list;
}

/* Insert the given x, y pair at the head of the list */
void insertHead(struct linkedList *list, long double x, long double y){
    struct linkedListNode *newNode = makeNewNode(x, y);
    newNode->next = list->head;
    if(list->head != NULL) {
        list->head->prev = newNode;
    }
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = list->head;
    }
}

/* Insert the given x, y pair at the tail of the list */
void insertTail(struct linkedList *list, long double x, long double y){
    struct linkedListNode *newNode = makeNewNode(x, y);
    /* If the linked list is empty */
    if(list->head == NULL) {
        list->head = list->tail = newNode;
    }
    else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

/* Removing the tail node */
void deleteTail(struct linkedList *list) {
    free(list->tail->point);
    struct linkedListNode *curr = list->tail->prev;
    free(list->tail);
    curr->next = NULL;
    list->tail = curr;
}

/* Free all items in the given list. */
void freeList(struct linkedList *list){
    struct linkedListNode *curr = list->head;
    while(curr != NULL) {
        struct linkedListNode *nextNode = curr->next;
        free(curr->point);
        free(curr);
        curr = nextNode;
    }
}

/* Create new linked list node */
struct linkedListNode *makeNewNode(long double xcoord, long double ycoord) {
    struct linkedListNode *newNode;
    newNode = (struct linkedListNode*)malloc(sizeof(*newNode));
    newNode->prev = newNode->next = NULL;
    newNode->point = (struct Point*)malloc(sizeof(struct Point));
    newNode->point->x = xcoord;
    newNode->point->y = ycoord;
    return newNode;
}
