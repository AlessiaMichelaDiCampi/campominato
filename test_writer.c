#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "field_parser.h"
#include "field_writer.h"

void print_matrix(field* f, int x, int y){
	int i, j;
	if(!f) return;
	for(i = 0; i < x; i++){
		for(j = 0; j < y; j++){
			switch(((*f)[i][j]).value){
				case -1:
					printf("%c ", (char)254);
					break;
				case 0:
					printf("%c ", (char)178);
					break;
				default:
					printf("%d ", ((*f)[i][j]).value);
					break;
			}
		}
		printf("\n");
	}
}

int main(){
	field *zone;
	int *width, *height;
	width = (int*)malloc(sizeof(int));
	height = (int*)malloc(sizeof(int));
	zone = (field*)malloc(sizeof(field));
	printf("Starting parse...\n");
	zone = parse("save.txt", width, height);
	printf("Parse done.\nParse result: \n");
	print_matrix(zone, *width, *height);
	if(save(zone, *width, *height, "save.txt")) printf("Write success.\n");
	else printf("Write fail\n");
	return 0;
}