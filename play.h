#ifndef PLAY_H
#define PLAY_H

flip** bare(field *battlefield, int width, int heigth, int cell_id, stack *history);
int flag(field *battlefield, int cell_id);
int* rollback(field *battlefield, int rollback_target);

#endif