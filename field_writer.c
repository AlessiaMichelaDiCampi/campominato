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
	output = (char*)malloc(sizeof(char) * MAX_FIELD_LENGTH * MAX_FIELD_LENGTH);
	if(!f) return FALSE; /* se il campo passato non esiste non si generano files. */
	if(!path){ /* se non è impostata una path di default, scrivo su un file arbitrario */
		actual_path = (char*)malloc(sizeof(char) * 100);
		actual_path = "output.txt";
	}
	else actual_path = path;
	/*output = "";*/
	sprintf(output, "%d,%d\n\n", width, heigth);
	for(i = 0; i < width; i++)
		for(j = 0; j < heigth; j++){
			if((*f)[i][j].value == 0){
				sprintf(output + strlen(output), "%d,%d\n", i, j);
			}
		}
	destination = fopen(actual_path, "w");
	if(!destination) {
		return FALSE;
	}
	if(!fprintf(destination, "%s", output) && strlen(output) > 0){
		free(actual_path);
		free(output);
		return FALSE;
	}
	fclose(destination);
	if(!path) free(actual_path);
	free(output);
	return TRUE;
}
