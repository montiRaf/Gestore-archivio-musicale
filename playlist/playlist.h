/*
 * playlist.h
 *
 *  Created on: 24 mag 2016
 *      Author: Martemucci, Monti
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#define MAXDIM 30
#define NOT_FOUND -1

typedef struct{
	char artista[MAXDIM];
	char titolo[MAXDIM];
	char genere[MAXDIM];
	int stelle;
}track_t;

track_t inserisci_dettagli(void);
int ricerca_titolo(track_t *lista, int dim_lista, char titolo[]);
void ricerca_genere(track_t *lista, int dim_lista);
void crea_playlist(track_t *lista, track_t *playlist, int dim_lista, int dim_playlist);
void stampa_lista(track_t *lista, int dim_lista);
void ordina_tracks(track_t *lista, int dim_lista);

#endif /* PLAYLIST_H_ */
