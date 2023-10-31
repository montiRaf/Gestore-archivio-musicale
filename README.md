# Gestore-archivio-musicale
Questo programma, creato come progetto universitario per l'esame di Laboratorio di Informatica, permette di gestire un archivio musicale, contenente brani musicali di diversi artisti, generi e loro valutazioni.

## Funzionalità di base: ##

* Inserimento di un nuovo brano nell'archivio
* Ricerca di un brano per titolo
* Visualizzazione dei brani per genere
* Creazione e visualizzazione di una playlist
* Classificazione dei brani per valutazione

### Note: ###
Il programma è stato sviluppato in linguaggio C.
Il programma utilizza un file di testo per memorizzare i dati dell'archivio.

## Esempio di utilizzo: ##

$ ./gestione_archivio

*******   GESTIONE DI UN ARCHIVIO MUSICALE   *******

----  Creazione archivio  ----

Inserisci dimensione archivio
---> 5

Inserisci i dati del brano n.1

Artista: Fabrizio De André
Titolo: La canzone di Marinella
Genere: Cantautore
Valutazione: 5

Inserisci i dati del brano n.2

Artista: Lucio Battisti
Titolo: Pensieri e parole
Genere: Pop
Valutazione: 4

Inserisci i dati del brano n.3

Artista: Vasco Rossi
Titolo: Vita spericolata
Genere: Rock
Valutazione: 3

Inserisci i dati del brano n.4

Artista: Laura Pausini
Titolo: Incancellabile
Genere: Pop
Valutazione: 2

Inserisci i dati del brano n.5

Artista: Tiziano Ferro
Titolo: Xdono
Genere: Pop
Valutazione: 1

----   RICERCA BRANO PER TITOLO   ----

Inserisci il titolo del brano
---> Pensieri e parole

Brano n.2

ARTISTA       TITOLO        GENERE       VALUTAZIONE
Lucio Battisti  Pensieri e parole  Pop           4

----   VISUALIZZAZIONE BRANI PER GENERE   ----

Genre: Cantautore

ARTISTA       TITOLO        GENERE       VALUTAZIONE
Fabrizio De André  La canzone di Marinella  Cantautore  5

Genre: Pop

ARTISTA       TITOLO        GENERE       VALUTAZIONE
Lucio Battisti  Pensieri e parole  Pop           4
Laura Pausini  Incancellabile  Pop           2
Tiziano Ferro  Xdono  Pop           1

----   CREAZIONE E VISUALIZZAZIONE PLAYLIST   ----

Inserisci dimensione playlist
---> 2

Inserisci i brani da inserire nella playlist
---> 1
---> 2

Playlist n.1

ARTISTA       TITOLO        GENERE       VALUTAZIONE
Fabrizio De André  La canzone di Marinella  Cantautore  5
Lucio Battisti  Pensieri e parole  Pop           4
