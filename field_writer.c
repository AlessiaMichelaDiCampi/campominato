#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "structures.h"

/*
 * La funzione save apre il file con il percorso relativo o assoluto
 * specificato nella stringa path e scrive i dati del campo *f come
 * da specifiche richieste. Se il file già esiste, è sovrascritto.
 * Restituisce TRUE se la scrittura avviene con successo o FALSE se
 * non è possibile aprire lo stream in scrittura.
 * Lo stream viene aperto solo alla fine della funzione per ridurre al
 * minimo il tempo di lock sul file.
 * Di conseguenza, importo unistd.h per utilizzare la funzione access al
 * fine di valutare l'esistenza del file.
 */
int save(field *f, int width, int heigth, char *path){
	FILE *destination;
	char *actual_path, *output;
	int i, j;
	i = j = 0;
	if(!f) return FALSE; /* se il campo passato non esiste non si generano files. */
	if(!path){ /* se non è impostata una path di default, scrivo su un file arbitrario */
		actual_path = (char*)malloc(sizeof(char) * 10);
		actual_path = "output.txt";
	}
	else actual_path = path;
	output = (char*)malloc(sizeof(char) * 200);
	output = "";
	strcat(output, i + j + "\n\n");
	for(i = 0; i < width; i++)
		for(j = 0; j < heigth; j++){
			if((*f)[i][j].value == 0)
				strcat(output, i + j + "\n");
		}
	destination = fopen(actual_path, "w");
	if(!destination) return FALSE;
	if(!fprintf(destination, actual_path) && strlen(output) > 0) return FALSE;
	fclose(destination);
	return TRUE;
}