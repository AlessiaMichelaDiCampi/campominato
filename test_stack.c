#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "stack.h"

void print_stack_debug(stack l){
	node* iterator;
	iterator = (node*)malloc(sizeof(node));
	iterator = l;
	if(!iterator){
		printf("Stack empty\n");
		return;
	} 
	printf("Print stack:\n");
	while(iterator){
		printf("\tTurn: info.turn_number -> %d, info.cell_id -> %d\n",iterator -> info.turn_number, iterator -> info.cell_id);
		iterator = iterator -> ptr;
	}
}

int main(){
	stack s;
	turn *t1, *t2, *t5;
	t1 = (turn*)malloc(sizeof(turn));
	t2 = (turn*)malloc(sizeof(turn));
	t5 = (turn*)malloc(sizeof(turn));
	t1 -> turn_number = 1;
	t1 -> cell_id = 10;
	t2 -> turn_number = 1;
	t2 -> cell_id = 12;
	s = NULL;
	printf("Initialized stack\n");
	print_stack_debug(s);
	printf("Pushing t1: turn_number -> %d, cell_id -> %d\n", t1 -> turn_number, t1 -> cell_id);
	push(&s, t1);
	print_stack_debug(s);
	printf("Pushing t2: turn_number -> %d, cell_id -> %d\n", t2 -> turn_number, t2 -> cell_id);
	push(&s, t2);
	print_stack_debug(s);
	printf("Count = %d", count(&s));
	t5 = pop(&s);
	printf("Pop operation, popped turn: turn_number -> %d, cell_id -> %d\n", t5 -> turn_number, t5 -> cell_id);
	print_stack_debug(s);
	t5 = peek(&s);
	printf("Peek operation, peeked turn: turn_number -> %d, cell_id -> %d\n", t5 -> turn_number, t5 -> cell_id);
	print_stack_debug(s);
	printf("Pop of last item\n");
	t5 = pop(&s);
	print_stack_debug(s);
	printf("Pop on empty stack\n");
	t5 = pop(&s);
	printf("Peek on empty stack\n");
	t5 = peek(&s);
	printf("Push of 1 item\n");
	push(&s, t1);
	push(&s, t2);
	print_stack_debug(s);
	printf("Destroy\n");
	destroy(&s);
	print_stack_debug(s);
	return 0;
}