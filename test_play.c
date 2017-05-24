#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "play.h"
#include "field_parser.h"

/*
 * '#' : coperta
 * '@' : mina
 * ' ' : vuota
 * Altrimenti è numero
 */
char cell_value(cell *c){
	if(!c) return '';
	if(c -> state == COVERED) return '#';
	if(c -> value < 0) return ' ';
	if(c -> value == MINE) return '@';
	return c -> value + '0';
}

void print_field(field *f, int width, int heigth){
	int i, j;
	if(width <= 0 || heigth <= 0 || !f) return;
	for(i = 0; i < width; i++){
		for(j = 0; j < heigth; j++)
			printf("%c ",cell_value(&((*f)[i][j])));
		printf("\n");
	}
}

int main(){
	field *zone;
	int width, heigth, end_game = 0, id, n_turn = 1, rollbacks = 5, jump_distance = 0, end_as_winnner;
	char command_buffer[20];
	stack turns;
	flip **proxy;
	turns = NULL;
	zone = (field*)malloc(sizeof(field));
	zone = parse("test_parse.txt", &width, &height);
	while(!end_game){
		print_field(zone, width, heigth);
		printf("\nTurno %d\nRollbacks: %d\nInserire comando: \n", n_turn, rollbacks);
		scanf("%s %d %d", command_buffer,&id); //parso il comando e i parametri (id è cell_id se scopro o flaggo, altrimenti ignorato )
		if(strcmp(command_buffer, "bare") == 0){
			proxy = bare(zone, width, heigth, id, &turns);
			if(proxy[0] -> value == MINE) end_game == 1;
		}
		else if (strcmp(command_buffer, "flag") == 0)
			flag(zone, id);
		else if(strcmp(command_buffer, "rollback") && rollbacks > 0){
			rollback(zone, n_turn - jump_distance, turns);
			rollbacks--;
			jump_distance++;
		}
		else printf("Comando sconosciuto");
		if(win(zone, width, heigth)){
			end_game = 1;
			end_as_winnner = 1;
		}
		if(loss(zone, width, heigth)){
			end_game = 1;
			end_as_winnner = 0;
		}
	}
	if(end_as_winnner) printf("HAI VINTO\n");
	else printf("HAI PERSO\n");
}