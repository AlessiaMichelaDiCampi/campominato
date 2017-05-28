#ifndef FIELD_PARSER_H
#define FIELD_PARSER_H
#include "structures.h"

field* parse(char* filename, int *width, int *heigth);
void set_numbers_around(field *f, int x, int y, int width, int heigth);

#endif