/*
 * menu.c
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

#define DIM 2

void stampa_menu(void);
void scrivi_file(FILE *f, track_t *lista, int dim_lista);

int main(void)
{
	int dim_archivio, dim_playlist, num_playlist = 0 ;
	int i, scelta, err, pos ;
	char s[DIM+1], titolo[MAXDIM],stelle[6];
	track_t *archivio = NULL, *playlist = NULL ;
	FILE *cfPtr = NULL ;

	printf("*******   GESTIONE DI UN ARCHIVIO MUSICALE   *******\n\n");

	printf("----  Creazione archivio  ----\n\n");
	printf("Inserisci dimensione archivio\n");
	printf("---> ");
	scanf("%d", &dim_archivio);

	// svuota buffer
	while( getchar() != '\n' )
		;

	archivio = (track_t*) malloc((sizeof(track_t)) * dim_archivio);

	printf("\n");
	// carica i dati nell'archivio
	for( i = 0 ; i < dim_archivio ; i++ ){

		printf("Brano n.%d\n", i+1);
		archivio[i] = inserisci_dettagli();
		printf("\n");
	}

	// carica l'archivio nel file
	if( (cfPtr = fopen("archivio.txt", "w")) == NULL ){
		printf("\"Archivio.txt\" non e' stato aperto!\n");
	}
	else{
		fprintf(cfPtr, "*******   ARCHIVIO MUSICALE   *******\n\n");
		scrivi_file(cfPtr, archivio, dim_archivio);

		fclose(cfPtr);
	}

	// menu di scelta operazioni
	do{
		system("CLS");
		stampa_menu();

		printf("\n");
		printf("Effettua la tua scelta: ");
		scanf("%d", &scelta);
		printf("\n");

		/* Inizio struttura di controllo per permettere la scelta della
		 * funzione desiderabile
		 */

		switch(scelta)
		{
		case 1:
			printf("----   RICERCA BRANO PER TITOLO   ----\n\n");

			printf("Inserisci il titolo del brano\n");
			printf("---> ");

			while(getchar() != '\n')
				;

			gets(titolo);
			printf("\n");

			pos = ricerca_titolo(archivio, dim_archivio, titolo);

			if( pos != NOT_FOUND ){

				printf("Brano n.%d\n", pos+1);
				fprintf(stdout, "%-30s%-30s%-30s%-30s\n", "ARTISTA", "TITOLO", "GENERE", "VALUTAZIONE");

				// conversione da numero a stelle '*'
				strcpy(stelle, " ");

				if( archivio[pos].stelle > 0 ){

					for( i = 0 ; i < archivio[pos].stelle ; i++ )
						stelle[i] = '*';

					stelle[i] = '\0';
				}

				fprintf(stdout, "%-30s%-30s%-30s%-30s\n",
										archivio[pos].artista, archivio[pos].titolo, archivio[pos].genere, stelle);

				printf("\n");
			}
			else{
				printf("Traccia non presente in archivio\n");
			}
			break ;

		case 2:
			printf("----   VISUALIZZAZIONE BRANI PER GENERE   ----\n\n");

			while(getchar() != '\n')
				;

			ricerca_genere(archivio, dim_archivio);
			printf("\n");
			break;

		case 3:
			printf("----   CREAZIONE E VISUALIZZAZIONE PLAYLIST   ----\n\n");

			printf("Inserisci dimensione playlist\n");
			printf("---> ");
			scanf("%d", &dim_playlist);

			while( getchar() != '\n')
				;

			playlist = (track_t*) malloc((sizeof(track_t)) * dim_playlist);

			crea_playlist(archivio, playlist, dim_archivio, dim_playlist);

			num_playlist++ ;

			// scrivi la playlist sul file
			if( (cfPtr = fopen("archivio.txt", "a")) == NULL ){
				printf("\"Archivio.txt\" non e' stato aperto\n");
			}
			else{
				fprintf(cfPtr, "\n");
				fprintf(cfPtr, "*******   PLAYLIST n.%d   *******\n\n", num_playlist);
				scrivi_file(cfPtr, playlist, dim_playlist);

				fclose(cfPtr);
			}

			stampa_lista(playlist, dim_playlist);
			break;

		case 4:
			printf("----   CLASSIFICAZIONE BRANI   ----\n\n");

			ordina_tracks(archivio, dim_archivio);

			while(getchar() != '\n' )
				;
			break;

		default:
			printf("Errore! Operazione non valida\n\n");

			while ( getchar() != '\n' )
				;
			break;
		}

		printf("\n");
		printf("Si desidera tornare al Menu'?\n");
		printf("[SI] - Torna al menu'\n");
		printf("[NO] - Termina il programma\n\n");

		printf("---> ");

		// lettura scelta dell'utente
		do{

			err = 0 ;
			gets(s);

			//conversione in maiuscolo
			for(i = 0 ; s[i] != '\0' ; i++)
				s[i] = toupper(s[i]);

			if( strlen(s) == 0 ){

				printf("Errore! Non hai inserito alcuna risposta\n");
				printf("Ripeti ---> ");
				err = 1 ;
			}
			else if( strlen(s) > DIM ){

				printf("Errore! Risposta non valida\n");
				printf("Ripeti ---> ");
				err = 1 ;
			}
			else if( strcmp(s, "SI") != 0 && strcmp(s, "NO") != 0 ){

				printf("Errore! Risposta non valida\n");
				printf("Ripeti ---> ");
				err = 1 ;
			}
		} while( err == 1 );

	} while( strcmp(s, "SI") == 0 );

	// terminazione programma
	system("pause");
	return 0;
}

void stampa_menu(void)
{
	printf("\n");
	printf("*********************************************************************\n");
	printf("*                               MENU'                               *\n");
	printf("*********************************************************************\n");
	printf("*              [1] - Ricerca brano per titolo                       *\n");
	printf("*              [2] - Visualizzazione brani per genere               *\n");
	printf("*              [3] - Creazione e visualizzazione playlist           *\n");
	printf("*              [4] - Classificazione brani                          *\n");
	printf("*********************************************************************\n");
}

void scrivi_file(FILE *f, track_t *lista, int dim_lista)
{
	int i, j ;
	char stelle[6];

	fprintf(f, "%-30s%-30s%-30s%-30s\n", "ARTISTA", "TITOLO", "GENERE", "VALUTAZIONE");

	for(i = 0 ; i < dim_lista ; i++){

		strcpy(stelle, " ");
		// conversione da numero a stelle '*'
		if( lista[i].stelle > 0 ){

			for(j = 0 ; j < lista[i].stelle ; j++){
				stelle[j] = '*' ;
			}
			stelle[j] = '\0';
		}
		fprintf(f, "%-30s%-30s%-30s%-30s\n",
							lista[i].artista, lista[i].titolo, lista[i].genere, stelle);
	}
}
