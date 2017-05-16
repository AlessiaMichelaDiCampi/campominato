#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

field* parse(char* filename){
	FILE *source;
	field* parsed;
	int max_x, max_y, buff_pos_x = 0, buff_pos_y = 0, id_distributor = 0, i, j;
	parsed = (field*)malloc(sizeof(field));
	source = fopen(filename, "r");
	/* parso prima numero di righe e di colonne */
	fscanf(source, "%d,%d", max_x, max_y);
	fscanf(source, "%s");
	/* inizializzo tutte le caselle con contenuto nullo */
	for(i = 0; i < max_x; i++)
		for(j = 0; j < max_y; j++){
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
		set_numbers_around(parsed, buff_pos_x, buff_pos_y);
		(*parsed)[buff_pos_x][buff_pos_y].value = 0;
	}
	fclose(source);
}
void set_numbers_around(field* f, int x, int y){
	int offset_x, offset_y;
	for(offset_x = -1; offset_x <= 1; offset_x++){
		for(offset_y = -1; offset_y <= 1; offset_y++){
			if((*parsed)[x + offset_x][y + offset_y].value > 0) (*parsed)[x + offset_x][y + offset_y].value++;
			else if ((*parsed)[x + offset_x][y + offset_y].value < 0) (*parsed)[x + offset_x][y + offset_y].value = 1;
		}
	}
}