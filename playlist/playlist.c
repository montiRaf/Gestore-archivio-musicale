/*
 * playlist.c
 *
 *  Created on: 24 mag 2016
 *      Author: Martemucci, Monti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "playlist.h"

track_t inserisci_dettagli(void){

	track_t temp;

	printf("Inserisci artista ---> ");
	gets(temp.artista);
	printf("Inserisci titolo ---> ");
	gets(temp.titolo);
	printf("Inserisci genere ---> ");
	gets(temp.genere);

	temp.stelle = 0;

	return temp;
}

int ricerca_titolo(track_t *lista, int dim_lista, char titolo[])
{
	int i, pos = NOT_FOUND ;

	for( i = 0 ; i < dim_lista && pos == NOT_FOUND ; i++ ){

		if( strcmp(lista[i].titolo, titolo) == 0 )
			pos = i ;
	}

	return pos;
}

void ricerca_genere(track_t *lista, int dim_lista)
{
	int i, j, flag = NOT_FOUND ;
	char genere[MAXDIM];
	char stelle[6];

	printf("Inserisci il genere da ricercare (Pop, Rock, Metal, Latin, R&B)\n");
	printf("---> ");
	gets(genere);

	// conversione in minuscolo
	for(i = 0 ; genere[i] != '\0' ; i++ )
		genere[i] = tolower(genere[i]);

	if( (strcmp(genere, "pop") == 0) 	||
		(strcmp(genere, "rock") == 0) 	||
		(strcmp(genere, "metal") == 0)	||
		(strcmp(genere, "latin") == 0) 	||
		(strcmp(genere, "r&b") == 0) ){

		printf("\n");
		fprintf(stdout, "%-30s%-30s%-30s%-30s\n", "ARTISTA", "TITOLO", "GENERE", "VALUTAZIONE" );

		for( i = 0 ; i < dim_lista ; i++){

			if( strcmp(lista[i].genere, genere) == 0 ){

				// conversione da numero a stelle '*'
				strcpy(stelle, " ");

				if( lista[i].stelle > 0){

					for(j = 0 ; j < lista[i].stelle ; j++)
						stelle[j] = '*';

					stelle[j] = '\0';
				}

				fprintf(stdout, "%-30s%-30s%-30s%-30s\n",
									lista[i].artista, lista[i].titolo, lista[i].genere, stelle);
				flag = 1 ;	//almeno una e' stata trovata
			}
		}

		if ( flag == NOT_FOUND )
			printf("Non e' stata trovata alcuna traccia\n");
	}
	else{
		printf("Errore! Il genere inserito non esiste in archivio\n");
	}
}

void crea_playlist(track_t *lista, track_t *playlist, int dim_lista, int dim_playlist)
{
	int i, m ;
	char titolo[MAXDIM];

	printf("Inserisci i titoli dei brani da aggiungere:\n");

	i = 0 ;
	while( i < dim_playlist){

		printf("Brano n.%d ---> ", i+1);
		gets(titolo);

		m = ricerca_titolo(lista, dim_lista, titolo);

		if( m != NOT_FOUND ){
			strcpy(playlist[i].artista, lista[m].artista);
			strcpy(playlist[i].titolo, lista[m].titolo);
			strcpy(playlist[i].genere, lista[m].genere);

			//massimo 5 stelle
			if (lista[m].stelle < 5){
				lista[m].stelle = lista[m].stelle + 1 ;
			}

			playlist[i].stelle = lista[m].stelle ;
			i++ ;
		}
		else{
			printf("Errore! Brano non presente in archivio\n");
			printf("Ripeti inserimento\n\n");
		}
	}
}

void stampa_lista(track_t *lista, int dim_lista)
{
	int i, j ;
	char stelle[6];

	fprintf(stdout, "%-30s%-30s%-30s%-30s\n", "ARTISTA", "TITOLO", "GENERE", "VALUTAZIONE" );

	for( i = 0 ; i < dim_lista ; i++){

		strcpy(stelle, " ");

		if( lista[i].stelle > 0 ){

			for(j = 0 ; j < lista[i].stelle ; j++)
				stelle[j] = '*' ;

			stelle[j] = '\0' ;
		}

		fprintf(stdout, "%-30s%-30s%-30s%-30s\n",
							lista[i].artista, lista[i].titolo, lista[i].genere, stelle);
	}
}

void ordina_tracks(track_t *lista, int dim_lista)
{
	int i, j ;
	bool pass ;
	track_t *sort = NULL, temp ;

	sort = (track_t*) malloc(sizeof(track_t) * dim_lista);

	for(i = 0 ; i < dim_lista ; i++){
		sort[i] = lista[i] ;
	}

	pass = true ;
	for(i = dim_lista-1 ; i > 0 && pass == true ; i--){

		pass = false ;
		for( j = 0 ; j < i ; j++){

			if( sort[j].stelle < sort[j+1].stelle){
				pass = true ;
				temp = sort[j];
				sort[j] = sort[j+1];
				sort[j+1] = temp;
			}
		}
	}

	stampa_lista(sort, dim_lista);
}
