#ifndef STACK_H
#define STACK_H

void init(list l);
int push(list l, turn t);
node pop(list l, int cell_id);
node peek(list l, int cell_id);
int count(list l);
void destroy(list l);

#endif