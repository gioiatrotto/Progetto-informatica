#ifndef CLIENTI_H
#define CLIENTI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char nome[40];
    char cognome[40];
    int eta;
    int ID;
} Cliente;


/*
@param s - una stringa da pulire.
La funzione pulisci_stringa prende in input una stringa e rimuove eventuali caratteri di nuova linea
o spazi bianchi alla fine della stringa.
*/
void pulisci_stringa(char *s);

/*
La funzione salva_ultimo_id prende in input un intero e lo salva come ultimo ID utilizzato.
*/
int prendi_ultimo_id();


/*
@param id - un intero che rappresenta l'ID da salvare.
La funzione salva_ultimo_id prende in input un intero e lo salva come ultimo ID utilizzato.
*/ 
void salva_ultimo_id(int id);
         
/*
@param riga - una stringa che rappresenta una riga del file clienti.csv.
@param c - un puntatore a una struttura Cliente in cui verranno salvati i dati estratti dalla riga.
La funzione riga_a_cliente prende in input una stringa che rappresenta una riga del file clienti.csv 
e un puntatore a una struttura Cliente, e estrae
*/
int riga_a_cliente(const char *riga, Cliente *c);

/*
La funzione cercaCliente prende in input il nome e il cognome di un cliente, e cerca nel file clienti.csv
un cliente con quel nome e cognome, restituendo le informazioni del cliente
*/
void cercaCliente();

/*
La funzione aggiungiClienti prende in input il nome, il cognome e l'età di un cliente, 
e aggiunge un nuovo cliente al file clienti.csv con un ID automatico incrementale
*/
void aggiungiClienti();

/*
La funzione stampaClienti prende in input il nome, il cognome e l'età di un cliente, 
e stampa a schermo tutti i clienti presenti nel file clienti.csv con le loro informazioni
*/
void stampaClienti();

/*
La funzione eliminaCliente prende in input il nome e il cognome di un cliente,
e elimina il cliente corrispondente dal file clienti.csv
*/
void eliminaCliente();

/*
La funzione eliminaClienti è un alias per eliminaCliente
*/
void eliminaClienti();

/*
La funzione modificaCliente prende in input il nome, il cognome e l'età di un cliente,
e modifica le informazioni del cliente corrispondente nel file clienti.csv
*/
void modificaCliente();

#endif


