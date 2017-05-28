#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "play.h"
#include "field_parser.h"
#include "field_generator.h"
#include "field_writer.h"
#include "mine_field.h"
#include "stack.h"

#define SHELL_WIDTH 80
#define STRING_LENGTH 200

int main(){
	/*
	 * Definizione delle variabili "globali"
	 * quit: flag che indica se l'applicazione e' aperta on in fase di chiusura
	 * end_game: flag che indica se l'attuale partita e' ancora attiva o e' persa
	 * width: la larghezza del campo corrente
	 * heigth: l'altezza del campo corrente
	 * menu_decision: contiene i'input fornito dal menu' principale (0, 1 ,2);
	 * command_buffer: stringa contenente l'ultimo comando parsato.
	 * battlefield: l'attuale campo di battaglia
	 * history: stack dei turni passati
	 * patch: risultato di una brutta storia. Per qualche motivo, lo stack funziona perfettamente nel file di test
	 *		  ma va in vacca quando poi viene utilizzato dalle funzioni di play. Questo pero' non avviene se lo stack
	 *		  ha almeno un elemento. Allora ne pushiamo uno fittizio mentre cerco il bug (che deve essere in qualche
	 *		  pop o peek effettuati dalla funzione rollback a giudicare da dove si blocca il modulo di test realizzato)
	 */
	int quit;
	char menu_decision;

	quit = FALSE;

	while(!quit){
		clrscr();
		game_menu();
		menu_decision = getchar();
		switch(menu_decision){
			case '0':
				quit = TRUE;
				break;
			case '1':
				quit = new_match();
				break;
			case '2':
				quit = load_match();
				break;
			default:
				break;
		}
	}
	return 0;
}

void clrscr()
{
    system("clear");
}

void game_menu(){
	int i;
	for(i = 0; i < SHELL_WIDTH; i++)
		printf("*");
	for(i = 0; i < 5; i++)
		printf("\n");
	printf("\t\t\t\t      CAMPO MINATO\n");
	for(i = 0; i < 4; i++)
		printf("\n");
	printf("0)Esci\n1)Nuova Partita\n2)Carica Da File");
	for(i = 0; i < 10; i++)
		printf("\n");
	for(i = 0; i < SHELL_WIDTH; i++)
		printf("*");
	printf("\n");
}

int new_match(){
	int n_mines, width, heigth;
	char w[20], h[20], m[20];
	field *battlefield;
	clrscr();
	do{
		printf("Inserire la dimensione del campo (formato 'w h' dove w:larghezza e h:altezza, min 0, max 100) : ");
		scanf("%s %s", w, h);
		width = atoi(w);
		heigth = atoi(h);
	}
	while(width <= 0 || width > 100 || heigth <= 0 || heigth > 100);
	do{
		printf("\nInserire il numero di mine nel campo (0 < x < %d)", width * heigth);
		scanf("%s", m);
		n_mines = atoi(m);
	}while(n_mines <= 0 || n_mines >= width * heigth);
	
	battlefield = generate(width, heigth, n_mines);
	return pre_play(battlefield, width, heigth);
}

int load_match(){
	int width, heigth;
	char path[STRING_LENGTH];
	field *battlefield;
	printf("Inserisci il nome del file: ");
	scanf("%s", path);
	battlefield = parse(path, &width, &heigth);
	while(!battlefield){
		printf("\nIl file indicato non esiste. Inserire il nome del file: ");
		scanf("%s", path);
		battlefield = parse(path, &width, &heigth);
	}
	return pre_play(battlefield, width, heigth);
}

int pre_play(field *battlefield, int width, int heigth){
	int rollbacks;
	printf("\nIn questa versione del gioco e' possibile annullare le proprie mosse.\nQuesto puo' essere fatto secondo le seguenti regole:\n\t1)Il numero di annullamenti e' limitato e viene impostato dal giocatore a inizio partita;\n\t2)Ogni volta che viene utilizzata la feature, si e' costretti ad annullare sempre piu' mosse\nInserire il numero di annullamenti: ");
	scanf("%d", &rollbacks);
	while(rollbacks < 0){
		printf("Il numero di annullamenti deve essere >= 0\nInserire il numero di annullamenti: ");
		scanf("%d", &rollbacks);
	}
	return play(battlefield, width, heigth, rollbacks);
}

int play(field *battlefield, int width, int heigth, int rollbacks){
	char command_buffer[STRING_LENGTH];
	char *instructions;
	stack history;
	turn *t;
	int jump_distance = 1, n_turn = 1, end_game = FALSE, end_reason, lose, x, y, wanna_leave; /* end_reason: FALSE -> persa, TRUE -> vinta */
	instructions = "Istruzioni: ci sono tre comandi disponibili:\n\t1)Scopri cella: scrivere 'scopri x y' dove x,y sono le coordinate;\n\t2)Metti/togli la bandierina: scrivere 'bandierina x y' dove x e y sono le coordinate\n\t3)Annulla mossa: scrivi 'annulla'";
	t = (turn*)malloc(sizeof(turn));
	t -> cell_id = 0;
	t -> turn_number = 0;
	push(&history, t);
	lose = FALSE;
	wanna_leave = FALSE;
	while(!end_game){
		clrscr();
		if(!loss(battlefield, width, heigth)) wanna_leave = FALSE;
		else printf("Hai scoperto una mina. Qualsiasi mossa diversa da annulla implica la sconfitta.\n");
		print_field(battlefield, width, heigth, instructions);
		printf("\nTurno %d\nAnnullamenti: %d\nNumero di turni di annulla: %d\nInserire comando: ", n_turn, rollbacks, jump_distance);
		scanf("%s", command_buffer);
		if(strcmp(command_buffer, "scopri") == 0 && !loss(battlefield, width, heigth)){
			scanf("%d %d", &y, &x);
			if(!((*battlefield)[x][y].flagged) && !((*battlefield)[x][y].state == FLIPPED) && x < width && y < heigth){
				bare(battlefield, width, heigth, x, y, &history);
				n_turn++;
			}
		}
		else if(strcmp(command_buffer, "bandierina") == 0 && !loss(battlefield, width, heigth)){
			scanf("%d %d", &y, &x);
			if((*battlefield)[x][y].state == COVERED) flag(battlefield, x, y, width, heigth);
		}
		else if(strcmp(command_buffer, "annulla") == 0){
			if(n_turn - jump_distance > 0 && rollbacks > 0){
				n_turn -= jump_distance;
				jump_distance++;
				rollbacks--;
				rollback(battlefield, n_turn, &history, width);
			}
		}
		else if(strcmp(command_buffer, "chiudi") == 0) return 1;
		else printf("Comando Sconosciuto o non legale\n");
		lose = loss(battlefield, width, heigth) && (rollbacks <= 0);
		if(win(battlefield, width, heigth)){
			end_game = TRUE;
			end_reason = TRUE;
		}
		if(lose || (loss(battlefield, width, heigth) && wanna_leave)){
			end_reason = FALSE;
			end_game = TRUE;
		}
		if(loss(battlefield, width, heigth) && !wanna_leave) wanna_leave = TRUE;
	}
	clrscr();
	print_field(battlefield, width, heigth, instructions);
	end_reason == TRUE ? printf("HAI VINTO\n") : printf("HAI PERSO\n");
	printf("Premi per continuare...");
	getchar();
	return 0;
}

void print_field(field *battlefield, int width, int heigth, char *instructions){
	int i, j;
	printf("%s\n", instructions);
	printf("    ");
	for(i = 0; i < heigth; i++) printf("%d ", i);
	printf("\n    ");
	for(i = 0; i < heigth; i++) printf("__");
	printf("\n");
	for(i = 0; i < width; i++){
		printf("%d  |", i);
		for(j = 0; j < heigth; j++){
			if((*battlefield)[i][j].flagged)
				printf("%c", 'F');
			else if((*battlefield)[i][j].state == 0)
				printf("%c", '#');
			else if((*battlefield)[i][j].value == 0)
				printf("%c", '@');
			else if((*battlefield)[i][j].value == -1)
				printf("%c", ' ');
			else
				printf("%d", (*battlefield)[i][j].value);
			printf(" ");
		}
		printf("\n");
	}
}
