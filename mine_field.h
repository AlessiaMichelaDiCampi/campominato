#ifndef MINE_FIELD_H
#define MINE_FIELD_H

void clrscr();
void game_menu();
int new_match();
int load_match();
int pre_play(field *battlefield, int width, int heigth);
int play(field *battlefield, int width, int heigth, int rollbacks);
void print_field(field *battlefield, int width, int heigth, char *instructions);

#endif