#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <bar.h>


/*
La funzione stampa_mete prende in input un puntatore a una struttura Menu e stampa a schermo le mete disponibili per la prenotazione, mostrando il nome, la gradazione e il prezzo
*/
void stampa_mete();

/*
@param menu - un puntatore a una struttura Menu che rappresenta il menu delle bottiglie del bar.
La funzione prenotaTavolo prende in input un puntatore a una struttura Menu e permette all'utente di prenotare un tavolo, chiedendo il nome del cliente, la data
*/
void prenotaTavolo(Menu* menu);

#endif


