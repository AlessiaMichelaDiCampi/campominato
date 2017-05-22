#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "structures.h"

#define SEED_GENERATION_CONST 0x18A639B7

uint64_t xorshift128plus(void);
void init(void);
field* generate(int width, int heigth, int mines);
void initialize_field(field *f, int width, int heigth);

uint64_t state[2];

/*
 * Inizializzo il seed di generazione di numeri
 * pseudo-casuali. Entrambi i valori DEVONO essere
 * diversi da 0
 */
void random_init(void){
	state[0] = (uint64_t)(time(NULL) * SEED_GENERATION_CONST);
	state[1] = state[0] ^ SEED_GENERATION_CONST;
}

uint64_t xorshift128plus(void){
	uint64_t x = state[0];
	uint64_t const y = state[1];
	state[0] = y;
	x ^= x << 23;
	state[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return imaxabs(state[1] + y);
}

field* generate(int width, int heigth, int mines){
	field *generating;
	int proxy, proxy_x, proxy_y, offset_x, offset_y;
	int min_x, max_x, min_y, max_y; /* A cosa servono? Quando riempio l'intorno di una mina con i numeri, se la mina è sul bordo rischio di sforare dalla matrice.
									 * Onde evitare questo casino, ad ogni iterazione del ciclo valuto se è necessario escludere numeri prima o dopo.
									 */
	if(width > MAX_FIELD_LENGTH || heigth > MAX_FIELD_LENGTH || mines > width * heigth || mines == 0 || width == 0 || heigth == 0) return NULL; /* se non sono input validi non genero nulla */
	generating = (field*)malloc(sizeof(field));
	initialize_field(generating, width, heigth);
	random_init();
	while(mines){
		proxy = abs(xorshift128plus()) % (width * heigth);
		proxy_x = proxy % width;
		proxy_y = proxy / width;
		if((*generating)[proxy_x][proxy_y].value != 0){
			min_x = proxy_x == 0 ? 0 : -1;
			max_x = proxy_x == width - 1 ? 0 : 1;
			for(offset_x = min_x; offset_x <= max_x; offset_x++){
				min_y = proxy_y == 0 ? 0 : -1;
				max_y = proxy_y == heigth - 1 ? 0 : 1;
				for(offset_y = min_y; offset_y <= max_y; offset_y++){
					if((*generating)[proxy_x + offset_x][proxy_y + offset_y].value > 0) (*generating)[proxy_x + offset_x][proxy_y + offset_y].value++;
					else if ((*generating)[proxy_x + offset_x][proxy_y + offset_y].value < 0) (*generating)[proxy_x + offset_x][proxy_y + offset_y].value = 1;
				}
			}
			(*generating)[proxy_x][proxy_y].value = 0;
			mines--;
		}
	}
	return generating;
}

void initialize_field(field *f, int width, int heigth){
	int id = 0, i, j;
	for(i = 0; i < width; i++)
		for(j = 0; j < heigth; j++){
			(*f)[i][j].value = -1;
			(*f)[i][j].id = id;
			(*f)[i][j].state = FALSE;
			(*f)[i][j].flagged = FALSE;
			id++;
		}
}