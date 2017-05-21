#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

field* parse(char* filename, int *width, int *heigth);
void set_numbers_around(field *f, int x, int y);

field* parse(char* filename, int *width, int *heigth){
	FILE *source;
	field* parsed;
	char *useless;
	int *max_x, *max_y, *buff_pos_x, *buff_pos_y, id_distributor = 0, i, j;
	parsed = (field*)malloc(sizeof(field));
	max_x = (int*)malloc(sizeof(int));
	max_y = (int*)malloc(sizeof(int));
	buff_pos_x = (int*)malloc(sizeof(int));
	buff_pos_y = (int*)malloc(sizeof(int));
	useless = (char*)malloc(sizeof(int));
	*buff_pos_x = *buff_pos_y = 0;
	source = fopen(filename, "r");
	if(!source)	return NULL;
	/* parso prima numero di righe e di colonne */
	fscanf(source, "%d,%d", max_x, max_y);
	*width = *max_x;
	*heigth = *max_y;
	fscanf(source, "%s", useless);
	/* inizializzo tutte le caselle con contenuto nullo */
	for(i = 0; i < *max_x; i++)
		for(j = 0; j < *max_y; j++){
			(*parsed)[i][j].value = -1;
			(*parsed)[i][j].id = id_distributor;
			(*parsed)[i][j].state = FALSE;
			(*parsed)[i][j].flagged = FALSE;
			id_distributor++;
		}
	/* Qui inizia la parte veramente intelligente: per ogni riga parsata,
	 * andiamo ad aggiungere una mina in quel punto e ad aggiornare tutti
	 * i valori di casella attorno a quella mina
	 */
	while(!feof(source)){
		fscanf(source, "%d,%d", buff_pos_x, buff_pos_y);
		set_numbers_around(parsed, *buff_pos_x, *buff_pos_y);
		(*parsed)[*buff_pos_x][*buff_pos_y].value = 0;
	}
	fclose(source);
	return parsed;
}
void set_numbers_around(field *f, int x, int y){
	int offset_x, offset_y;
	for(offset_x = -1; offset_x <= 1; offset_x++){
		for(offset_y = -1; offset_y <= 1; offset_y++){
			if((*f)[x + offset_x][y + offset_y].value > 0) (*f)[x + offset_x][y + offset_y].value++;
			else if ((*f)[x + offset_x][y + offset_y].value < 0) (*f)[x + offset_x][y + offset_y].value = 1;
		}
	}
}