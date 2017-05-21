#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "field_parser.h"
#include "field_writer.h"

int main(){
	field *zone;
	int *width, *heigth;
	width = (int*)malloc(sizeof(int));
	heigth = (int*)malloc(sizeof(int));
	zone = (field*)malloc(sizeof(field));
	zone = parse("test_parse.txt", width, heigth);
	if(save(zone, *width, *heigth, "save.txt")) printf("Written successfully\n");
	else printf("Write fail\n");
	return 0;
}