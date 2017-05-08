#include <stdio.h>
#include <stdlib.h>
#include "structures.c"
#include "stack.h"

/*
 * Instantiates a new stack by setting its head to NULL
 */
void init(stack l){
	l = NULL;
}

/*
 * Pushes a turn into the given stack
 */
int push(stack l, turn t){
    if (l == NULL)
    {
        l =(struct node *)malloc(1*sizeof(struct node));
        l->ptr = NULL;
        l->info = t;
    }
    else
    {
        temp =(struct node *)malloc(1*sizeof(struct node));
        temp->ptr = top;
        temp->info = t;
        l = temp;
    }
    return 1;
}

turn pop(stack l)
{
    stack temp;
    turn gone;
    temp = (struct node *)malloc(1*sizeof(struct node));
    gone = (struct node *)malloc(1*sizeof(struct turn));
    temp = l;
    if (temp == NULL) return NULL;
    temp = temp->ptr;
    gone = l -> info;
    free(l);
    l = temp;
    return gone;
}

turn peek(stack l){
    if(l == NULL) return NULL;
    return l -> info;
}

int count(stack l){
    int count = 0;
    while((*l) -> ptr != NULL) count++;
    return count;
}

void destroy(stack l)
{
	stack top1;
	top1 = (struct node *)malloc(1*sizeof(struct node));
    top1 = l;
 
    while (top1 != NULL)
    {
        top1 = l->ptr;
        free(l);
        l = top1;
        top1 = top1->ptr;
    }
    free(top1);
    l = NULL;
}