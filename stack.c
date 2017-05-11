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
 * Pushes a turn into the given stack
 l = node*
 temp = node*
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

turn* peek(stack *l){
    turn* fake;
    fake = (turn*)NULL;
    if(!(*l)) return fake;
    fake = (turn*)malloc(sizeof(turn));
    fake -> turn_number = (*l) -> info.turn_number;
    fake -> cell_id = (*l) -> info.cell_id;
    return fake;
}

int count(stack *l){
    int count = 0;
    node* iterator = *l;
    while(iterator){
        count++;
        iterator = iterator -> ptr;
    }     
    return count;
}

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
