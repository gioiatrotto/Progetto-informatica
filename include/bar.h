
#ifndef BAR_H
#define BAR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Bottiglia{
    char nome[50];
    float gradazione;
    float prezzo;
    struct Bottiglia* next;
}Bottiglia;

typedef struct {
    Bottiglia* testa;
    int lunghezza;
} Menu;

/*
La funzione restituisce un puntatore a una struttura Menu,
che rappresenta il menu delle bottiglie del bar.
La struttura Menu contiene un puntatore alla testa di una lista di bottiglie e un intero che rappresenta
la lunghezza della lista.
*/
Menu* creaMenu();

/*
@param menu - un puntatore a una struttura Menu che rappresenta il menu delle bottiglie del bar.
La funzione stampa_menu_bottiglie prende in input un puntatore a 
una struttura Menu e stampa a schermo il menu delle bottiglie, 
mostrando il nome, la gradazione e il prezzo di ogni bottiglia presente nel menu.
*/
void stampa_menu_bottiglie(Menu* menu);



/*
  @param menu - un puntatore a una struttura Menu che rappresenta il menu delle bottiglie del bar.
  @param gradazione - un float che rappresenta la gradazione alcolica della bottiglia da aggiungere al menu.
  @param prezzo - un float che rappresenta il prezzo della  bottiglia da aggiungere al menu.
  @param nome - una stringa che rappresenta il nome della bottiglia da aggiungere al menu.
  La funzione aggiungi_bottiglia_menu prende in input un puntatore a una struttura Menu, la gradazione alcolica,
  il prezzo e il nome di una bottiglia,
*/
void aggiungi_bottiglia_menu(Menu* menu, float gradazione, float prezzo, char* nome);



/*
@param menu - un puntatore a una struttura Menu che rappresenta il menu delle bottiglie del bar.
@param nome - una stringa che rappresenta il nome della bottiglia da rimuovere dal menu.
La funzione rimuovi_bottiglia_menu prende in input un puntatore a una struttura Menu e il nome di una bottiglia, 
e rimuove la bottiglia corrispondente
*/
void rimuovi_bottiglia_menu(Menu* menu, char* nome);



/*
@param menu - un puntatore a una struttura Menu che rappresenta il menu delle bottiglie del bar.
@param nome - una stringa che rappresenta il nome della bottiglia da cercare nel menu.
La funzione get_bottiglia prende in input un puntatore a una struttura Menu e il nome di una bottiglia, 
e restituisce un puntatore alla bottiglia corrispondente se presente
*/
Bottiglia* get_bottiglia(Menu* menu, char* nome);

/* Carica il menu delle bottiglie dal file bar.csv nella lista in memoria. */
void carica_menu_bottiglie(Menu* menu);

#endif
