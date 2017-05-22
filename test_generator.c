#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "field_generator.h"

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
	printf("Starting generation...\n");
	zone = generate(9, 9, 60);
	printf("Generation done.\nGeneration result: \n");
	print_matrix(zone, 9, 9);
	return 0;
}