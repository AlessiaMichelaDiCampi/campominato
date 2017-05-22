#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

flip** bare(field *battlefield, int width, int heigth, int cell_id, stack *history);
int flag(field *battlefield, int cell_id);
int* rollback(field *battlefield, int rollback_target, stack *history);
void bare_neighbours(field *battlefield, int x, int y, int width, int heigth, stack *history, flip **flips);

/*
 * La funzione scopre il valore di una cella nella struttura dati.
 * NOTA: perchè non serve cercare l'id? Perchè siccome gli id vengono
 * generati sequenzialmente, alla fine l'id di una cella equivale al suo
 * indice se il campo fosse un array e non una matrice. Quindi anzichè cercare
 * è sufficiente la conversione da indice di array a indice di matrice.
 *
 * Return: per comodità d'uso, senza costringere l'implementazione ad alto livello
 * a ricercare la cella per estrarne il valore, restituiamo il campo 'value' della
 * struct cell.
 */
flip** bare(field *battlefield, int width, int heigth, int cell_id, stack *history){
	int pos_x, pos_y, turn_number;
	flip** flips; /* funge da array di azioni che la grafica deve effettuare per pareggiarsi con lo stato del sistema */
	turn *temp_turn;
	flips = (flip**)malloc(sizeof(flip*) * (width * heigth));
	pos_x = cell_id % width;
	pos_y = cell_id / width;
	(*battlefield)[pos_x][pos_y].state = 1;
	/* push del turno effettuato (anzichè farmi passare il turno attuale, controllo l'ultimo push e incremento) */
	turn_number = (peek(&history) -> turn_number) + 1;
	temp_turn = (turn*)malloc(sizeof(turn));
	temp_turn -> turn_number = turn_number;
	temp_turn -> cell_id = cell_id;
	push(&history, temp_turn);
	/* carichiamo nell'array di flips il dato della casella svuotata */
	(*flips) = (flip*)malloc(sizeof(flip));
	(*flips) -> cell_id = cell_id;
	(*flips) -> value = (*battlefield)[pos_x][pos_y].value;
	/* ora è necessario un controllo: se è una cella vuota si flippano tutte quelle attorno che sono vuote */
	if((*battlefield)[pos_x][pos_y].value < 0) bare_neighbours(battlefield, pos_x, pos_y, width, heigth, history, flips + 1);
	return flips;
}

void bare_neighbours(field *battlefield, int x, int y, int width, int heigth, stack *history, flip **flips){
	turn *temp;
	if((*battlefield)[x][y].value == 0) return;
	if((*battlefield)[x][y].state == 1) return; /* onde evitare di rompersi i maroni a capire se dalla posizione attuale devo chiamare solo a destra
												 * o solo a sinistra o quel che è, ognuno chiama tutti quelli attorno. Se sono già scoperti terminano.
												 */
	/* se non è una mina, allora deve scoprirsi, registrarsi nello stack dei turni, registrarsi nell'array restituito e chiamare tutti i vicini a sua volta. */
	temp = (turn*)malloc(sizeof(turn));
	temp -> cell_id = (*battlefield)[x][y].id;
	temp -> turn_number = peek(&history) -> turn_number;
	push(&history, temp);
	(*flips) = (flip*)malloc(sizeof(flip));
	(*flips) -> cell_id = (*battlefield)[x][y].id;
	(*flips) -> value = (*battlefield)[x][y].value;
	flips++;
	if(x - 1 > 0){
		bare_neighbours(battlefield, x - 1, y, width, heigth, history, flips);
		if(y - 1 > 0) bare_neighbours(battlefield, x - 1, y - 1, width, heigth, history, flips);
		if(y + 1 < heigth) bare_neighbours(battlefield, x - 1, y + 1, width, heigth, history, flips);
	}
	if(x + 1 < width){
		bare_neighbours(battlefield, x + 1, y, width, heigth, history, flips);
		if(y - 1 > 0) bare_neighbours(battlefield, x + 1, y - 1, width, heigth, history, flips);
		if(y + 1 < heigth) bare_neighbours(battlefield, x + 1, y + 1, width, heigth, history, flips);
	}
	if(y - 1 > 0) bare_neighbours(battlefield, x, y - 1, width, heigth, history, flips);
	if(y + 1 < heigth) bare_neighbours(battlefield, x, y + 1, width, heigth, history, flips);
}

int flag(field *battlefield, int cell_id, int width, int heigth){
	int x, y;
	x = cell_id % width;
	y = cell_id / width;
	(*battlefield)[x][y].flagged = !((*battlefield)[x][y].flagged);
	return (*battlefield)[x][y].flagged;
}

int* rollback(field *battlefield, int rollback_target, stack *history){
	int *ids, x, y;
	turn *pop;
	ids = (int*)malloc(sizeof(int) * width * heigth);
	while(peek(&history) -> turn_number >= rollback_target){
		pop = pop(&history);
		*ids = pop -> cell_id;
		x = *ids % width;
		y = *ids / width;
		(*battlefield)[x][y].state = 0;
		ids++;
	}
	return ids;
}