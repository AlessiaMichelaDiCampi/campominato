#ifndef STACK_H
#define STACK_H

void init(stack l);
void push(stack* l, turn* t);
turn* pop(stack *l);
turn* peek(stack *l);
int count(stack *l);
void destroy(stack *l);

#endif
