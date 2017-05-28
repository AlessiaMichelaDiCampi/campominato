#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "stack.h"

void bare(field *battlefield, int width, int heigth, int x, int y, stack *history);
int flag(field *battlefield, int x, int y, int width, int heigth);
void rollback(field *battlefield, int rollback_target, stack *history, int width);
void bare_ric(field *battlefield, int x, int y, int width, int heigth, stack *history);

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
void bare(field *battlefield, int width, int heigth, int x, int y, stack *history){
	int turn_number;
	turn *temp_turn;
	/* push del turno effettuato (anzichè farmi passare il turno attuale, controllo l'ultimo push e incremento) */
	turn_number = (peek(history) -> turn_number) + 1;
	temp_turn = (turn*)malloc(sizeof(turn));
	temp_turn -> turn_number = turn_number;
	temp_turn -> cell_id = y * width + x;
	push(history, temp_turn);
	/* ora è necessario un controllo: se è una cella vuota si flippano tutte quelle attorno che sono vuote */
	if((*battlefield)[x][y].value < 0) bare_ric(battlefield, x, y, width, heigth, history);
	else (*battlefield)[x][y].state = 1;
}

/*
 * Chiamata che ricorsivamente scopre tutti i vicini di una cella vuota finchè non incontra numeri. Tutte le caselle
 * scoperte sono caricate nell'array **flips
 */
void bare_ric(field *battlefield, int x, int y, int width, int heigth, stack *history){
	turn *temp;
	if((*battlefield)[x][y].value == MINE) return;
	if((*battlefield)[x][y].state == FLIPPED) return; /* onde evitare di rompersi i maroni a capire se dalla posizione attuale devo chiamare solo a destra
												 * o solo a sinistra o quel che è, ognuno chiama tutti quelli attorno. Se sono già scoperti terminano.
												 */
	/* se non è una mina, allora deve scoprirsi, registrarsi nello stack dei turni, registrarsi nell'array restituito e chiamare tutti i vicini a sua volta. */
	(*battlefield)[x][y].state = FLIPPED;
	temp = (turn*)malloc(sizeof(turn));
	temp -> cell_id = (*battlefield)[x][y].id;
	temp -> turn_number = peek(history) -> turn_number;
	push(history, temp);
	if((*battlefield)[x][y].value > 0) return;
	if(x - 1 > 0){
		bare_ric(battlefield, x - 1, y, width, heigth, history);
		if(y - 1 > 0) bare_ric(battlefield, x - 1, y - 1, width, heigth, history);
		if(y + 1 < heigth) bare_ric(battlefield, x - 1, y + 1, width, heigth, history);
	}
	if(x + 1 < width){
		bare_ric(battlefield, x + 1, y, width, heigth, history);
		if(y - 1 > 0) bare_ric(battlefield, x + 1, y - 1, width, heigth, history);
		if(y + 1 < heigth) bare_ric(battlefield, x + 1, y + 1, width, heigth, history);
	}
	if(y - 1 > 0) bare_ric(battlefield, x, y - 1, width, heigth, history);
	if(y + 1 < heigth) bare_ric(battlefield, x, y + 1, width, heigth, history);
}

/*
 * Funzione che flagga la casella richiesta e ritorna il suo attuale stato di flag.
 */
int flag(field *battlefield, int x, int y, int width, int heigth){
	(*battlefield)[x][y].flagged = !((*battlefield)[x][y].flagged);
	return (*battlefield)[x][y].flagged;
}

/*
 * Funzione che annulla tutte le mosse fino a quella richiesta esclusa (rollback al turno 5 = rollback alla fine del turno 5).
 * Restituisce l'array degli id delle caselle da ricoprire
 */
void rollback(field *battlefield, int rollback_target, stack *history, int width){
	int id, x, y;
	turn *popd;
	while(peek(history) -> turn_number >= rollback_target){
		popd = pop(history);
		id = popd -> cell_id;
		y = id % width;
		x = id / width;
		(*battlefield)[x][y].state = COVERED;
	}
}

int win(field *f, int width, int heigth){
	int victoryConditionsMatched = TRUE, i, j;
	for(i = 0; i < width && victoryConditionsMatched; i++)
		for(j = 0; j < heigth && victoryConditionsMatched; j++)
			victoryConditionsMatched = ((*f)[i][j].state == COVERED && (*f)[i][j].value == MINE) || ((*f)[i][j].state == FLIPPED && (*f)[i][j].value != MINE);
	return victoryConditionsMatched;
}

int loss(field *f, int width, int heigth){
	int lossConditionMatched = FALSE, i, j;
	for(i = 0; i < width && !lossConditionMatched; i++)
		for(j = 0; j < heigth && !lossConditionMatched; j++)
			lossConditionMatched = (*f)[i][j].value == MINE && (*f)[i][j].state == FLIPPED;
	return lossConditionMatched;
}