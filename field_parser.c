#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

field* parse(char* filename, int *width, int *heigth);
void set_numbers_around(field *f, int x, int y, int width, int heigth);

field* parse(char* filename, int *width, int *heigth){
	FILE *source;
	field* parsed;
	char *useless;
	int *max_x, *max_y, *buff_pos_x, *buff_pos_y, id_distributor = 0, i, j, fail;
	parsed = (field*)malloc(sizeof(field));
	max_x = (int*)malloc(sizeof(int));
	max_y = (int*)malloc(sizeof(int));
	buff_pos_x = (int*)malloc(sizeof(int));
	buff_pos_y = (int*)malloc(sizeof(int));
	useless = (char*)malloc(sizeof(int));
	*buff_pos_x = *buff_pos_y = 0;
	source = fopen(filename, "r");
	if(!source)	return NULL;
	/* parso prima numero di righe e di colonne, o restituisco null se il file non è nel formato appropriato */
	if(!fscanf(source, "%d,%d", max_x, max_y)) return NULL;
	*width = *max_x;
	*heigth = *max_y;
	/* Questa operazione solleva un warning in compilazione. E' una questione nota, ma ho bisogno di parsare 
	 * la linea vuota dopo width e height.
	 */
	fscanf(source, "", useless);
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
	 * i valori di casella attorno a quella mina. Se il file non è nel formato
	 * appropriato viene restituito NULL. Se invece una mina risulta essere
	 * fuori dal campo semplicemente non viene inserita.
	 */
	fail = FALSE;
	while(!feof(source) && !fail){
		if(!fscanf(source, "%d,%d", buff_pos_x, buff_pos_y)) fail = TRUE;
		if(*buff_pos_x < *max_x && *buff_pos_y < *max_y){
			set_numbers_around(parsed, *buff_pos_x, *buff_pos_y, *width, *heigth);
			(*parsed)[*buff_pos_x][*buff_pos_y].value = 0;
		}
	}
	if(fail) return NULL;
	fclose(source);
	return parsed;
}
void set_numbers_around(field *f, int x, int y, int width, int heigth){
	int offset_x, offset_y, min_x, min_y, max_x, max_y;
	min_x = x == 0 ? 0 : -1;
	max_x = x == width - 1 ? 0 : 1;
	for(offset_x = min_x; offset_x <= max_x; offset_x++){
		min_y = y == 0 ? 0 : -1;
		max_y = y == heigth - 1 ? 0 : 1;
		for(offset_y = min_y; offset_y <= max_y; offset_y++){
			if((*f)[x + offset_x][y + offset_y].value > 0) (*f)[x + offset_x][y + offset_y].value++;
			else if ((*f)[x + offset_x][y + offset_y].value < 0) (*f)[x + offset_x][y + offset_y].value = 1;
		}
	}
}