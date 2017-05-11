#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "stack.h"

/*
 * Instantiates a new stack by setting its head to NULL
 */
void init(stack l){
	l = NULL;
}

/*
 * Given a stack pointer and a turn pointer, it inserts the
 * data pointed by the turn pointer into the stack.
 * NOTE: this function is a NOP if either the stack pointer
 * is NULL or the turn pointer is NULL 
 */
void push(stack* l, turn* t){
    node* temp;
    if(!temp) return;
    if (!(*l))
    {
        (*l) =(node*)malloc(sizeof(node));
        (*l)->ptr = NULL;
        (*l)->info.turn_number = t -> turn_number;
        (*l)->info.cell_id = t -> cell_id;
    }
    else
    {
        temp =(node*)malloc(sizeof(node));
        temp->ptr = *l;
        temp->info.turn_number = t -> turn_number;
        temp->info.cell_id = t -> cell_id;
        (*l) = temp;
    }
}

/*
 * Removes the last inserted item and returns a pointer to it.
 * Returns NULL if the stack is empty.
 */
turn* pop(stack* l)
{
    node* temp;
    turn* gone;
    temp = (node*)malloc(sizeof(node));
    temp = (*l);
    gone = (turn*)NULL;
    if (!temp) return gone;
    gone = (turn*)malloc(sizeof(turn));
    temp = temp->ptr;
    *gone = (*l) -> info;
    free(*l);
    *l = temp;
    return gone;
}

/*
 * Returns the last inserted item of the stack without
 * removing it. Returns NULL if the stack is empty.
 */
turn* peek(stack *l){
    turn* fake;
    fake = (turn*)NULL;
    if(!(*l)) return fake;
    fake = (turn*)malloc(sizeof(turn));
    fake -> turn_number = (*l) -> info.turn_number;
    fake -> cell_id = (*l) -> info.cell_id;
    return fake;
}

/*
 * Returns the number of items in the given stack.
 */
int count(stack *l){
    int count = 0;
    node* iterator = *l;
    while(iterator){
        count++;
        iterator = iterator -> ptr;
    }     
    return count;
}

/*
 * Destroys a list. Destruction means freeing every cell of memory
 * given to the stack and nullifying the pointer.
 */
void destroy(stack* l)
{
	node* top1;
	top1 = (node*)malloc(sizeof(node));
    top1 = *l;

    while (top1)
    {
        top1 = (*l)->ptr;
        free(*l);
        (*l) = top1;
        top1 = top1->ptr;
    }
    free(top1);
    *l = NULL;
}
