#ifndef PLAY_H
#define PLAY_H

flip** bare(field *battlefield, int width, int heigth, int cell_id, stack *history);
int flag(field *battlefield, int cell_id, int width, int heigth);
int* rollback(field *battlefield, int rollback_target, stack *history, int width);
int win(field *f, int width, int heigth);
int loss(field *f, int width, int heigth);


#endif