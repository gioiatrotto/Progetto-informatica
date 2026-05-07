#ifndef BOTTIGLIE_H
#define BOTTIGLIE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char nome[50];
    float gradazione;
}Bottiglia;

typedef struct{
    int num_tavolo;
    char nome_bottiglia[50];
}BottigliaTavolo;

// Funzioni per il menu di bottiglie
void aggiungi_bottiglia_menu();
void rimuovi_bottiglia_menu();
void stampa_menu_bottiglie();

// Funzioni per gestire bottiglie nei tavoli
void aggiungi_bottiglia_tavolo();
void elimina_bottiglia_tavolo();
void modifica_bottiglia_tavolo();
void scegli_bottiglia_omaggio();
void stampa_bottiglie_tavolo();

#endif
