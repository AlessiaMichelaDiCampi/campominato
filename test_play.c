#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "play.h"
#include "field_parser.h"

/*
 * '?' : mi passano null (quando succede?)
 * '#' : coperta
 * '@' : mina
 * ' ' : vuota
 * 'F' : flag
 * Altrimenti è numero
 */
char cell_value(cell *c){
	if(!c) return '?';
	if(c -> flagged == TRUE) return 'F';
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

/*
 * Per debug, stampiamo lo stack dei turni ad ogni turno
 */
void print_stack_debug(stack l){
	node* iterator;
	iterator = (node*)malloc(sizeof(node));
	iterator = l;
	if(!iterator){
		printf("Stack empty\n");
		return;
	} 
	printf("Print stack:\n");
	while(iterator){
		printf("\tTurn: info.turn_number -> %d, info.cell_id -> %d\n",iterator -> info.turn_number, iterator -> info.cell_id);
		iterator = iterator -> ptr;
	}
}


int main(){
	field *zone;
	int width, heigth, end_game = 0, x, y, n_turn = 1, rollbacks = 5, jump_distance = 1, end_as_winnner;
	char command_buffer[20];
	stack turns;
	turns = NULL;
	zone = (field*)malloc(sizeof(field));
	zone = parse("test_parse.txt", &width, &heigth);
	printf("Campo caricato da test_parse.txt.\nIstruzioni: ci sono tre comandi disponibili:\n\t1)Scopri cella: scrivere 'bare x y' dove x,y sono le coordinate;\n\t2)Metti la bandierina: scrivere 'flag x y' dove x e y sono le coordinate\n\t3)Annulla mossa: scrivi 'rollback 0 0'\n");
	while(!end_game){
		print_field(zone, width, heigth);
		printf("\nTurno %d\nRollbacks: %d\nInserire comando: \n", n_turn, rollbacks);
		scanf("%s %d %d", command_buffer,&x, &y); /*parso il comando e i parametri (id è cell_id se scopro o flaggo, altrimenti ignorato )*/
		if(strcmp(command_buffer, "bare") == 0) {
			if((*zone)[x][y].state != FLIPPED && !(*zone)[x][y].flagged){
				bare(zone, width, heigth, x, y, &turns);
				n_turn++;
				printf("Cella %d,%d scoperta\n", x, y);
			}
			else if((*zone)[x][y].state == FLIPPED) printf("Cella %d,%d già scoperta\n", x, y);
			else printf("Non e' possibile scoprire la cella flaggata %d,%d\n", x, y);
		}
		else if (strcmp(command_buffer, "flag") == 0){
			if((*zone)[x][y].state == COVERED){
				flag(zone, x, y, width, heigth);
				if((*zone)[x][y].flagged) printf("Bandierina posizionata su %d,%d\n", x, y);
				else printf("Bandierina rimossa da %d,%d\n", x, y);
			}
			else printf("Bandierina non posizionata su %d,%d: la cella e' gia' scoperta\n");
		} 
		else if(strcmp(command_buffer, "rollback") == 0){
			if(n_turn - jump_distance > 0 && rollbacks > 0){
				n_turn = n_turn - jump_distance;
				rollback(zone, n_turn, &turns, width);
				rollbacks--;
				jump_distance++;
				printf("Rollback di %d turni. Rollback rimanenti: %d\n", jump_distance - 1, rollbacks);
			}
			else printf("Impossibile annullare mossa. Turno: %d, rollbacks: %d, jump_distance:%d\n", n_turn, rollbacks, jump_distance);
		}
		else printf("Comando sconosciuto\n");
		if(win(zone, width, heigth)){
			end_game = 1;
			end_as_winnner = 1;
		}
		if(loss(zone, width, heigth)){
			end_game = 1;
			end_as_winnner = 0;
		}
		print_stack_debug(turns);
	}
	print_field(zone, width, heigth);
	if(end_as_winnner) printf("HAI VINTO\n");
	else printf("HAI PERSO\n");
	return 0;
}