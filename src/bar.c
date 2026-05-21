#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <bar.h>
#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/clienti_temp.csv"
#define FILE_ID "data/id.csv"
#define FILE_TAVOLI "data/tavoli.csv"
#define FILE_BAR "data/bar.csv"
#define FILE_BAR_TEMP "data/bar_temp.csv"
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"


Menu* creaMenu() {
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    menu->testa = NULL;
    menu->lunghezza = 0;
    return menu;
}

void stampa_menu_bottiglie(Menu* menu) {
    FILE *f = fopen(FILE_BAR, "r");
    if (f == NULL) {
        printf("Errore apertura file bar.csv!\n");
        return;
    }
    char riga[256];
    printf("\n--- Menu Bar ---\n");
    while (fgets(riga, sizeof(riga), f)) {
        char nome[50];
        float gradazione, prezzo;
        sscanf(riga, "%49[^,],%f,%f", nome, &gradazione, &prezzo);
        printf("Nome: %s | Gradazione: %.2f | Prezzo: %.2f\n", nome, gradazione, prezzo);
    }
    fclose(f);
    
}

void aggiungi_bottiglia_menu(Menu* menu, float gradazione, float prezzo, char* nome) {
    FILE *f = fopen(FILE_BAR, "a");
    if (f == NULL) {
        printf("Errore apertura file bar.csv!\n");
        return;
    }
    Bottiglia* nuovaBottiglia = (Bottiglia*)malloc(sizeof(Bottiglia));
    nuovaBottiglia->gradazione = gradazione;
    nuovaBottiglia->prezzo = prezzo;
    strcpy(nuovaBottiglia->nome, nome);
    nuovaBottiglia->next = menu->testa;
    menu->testa = nuovaBottiglia;
    menu->lunghezza++;
    fprintf(f, "%s,%.2f,%.2f\n", nome, gradazione, prezzo);
    fclose(f);
}

void rimuovi_bottiglia_menu(Menu* menu, char* nome ){
    if (menu == NULL || menu->testa == NULL) {
        printf("Menu vuoto o non inizializzato.\n");
        return;
    }

    bool trovato = false;                                   //variabile per tenere traccia se la bottiglia è stata trovata e rimossa
    Bottiglia* current = menu->testa;                       //prende il 1 elemento della lista  

    if (strcmp(current->nome, nome) == 0) {                 //confronta il nome della bottiglia con il nome cercato
        Bottiglia* temp = current;                          //temp la utilizzo per salvarci la bottiglia da eliminare
        menu->testa = current->next;                        //aggiorno la testa della lista
        free(temp);                                         // libera la memoria della bottiglia da eliminare
        menu->lunghezza--;                                  //dato che tolgo un nodo diminuisce la lunghezza
        trovato = true;                                     //bottiglia trovata e rimossa  
    } else {
        while (current->next != NULL) {                     //scorre la lista fino a trovare la bottiglia da eliminare o arrivare alla fine della lista
            if (strcmp(current->next->nome, nome) == 0) {   //confronta il nome della bottiglia successiva con quella da cercare
                Bottiglia* temp = current->next;            
                current->next = current->next->next;
                free(temp);
                menu->lunghezza--;
                trovato = true;
                break;
            }
            current = current->next;                        //passa al nodo successivo
        }
    }

    FILE *f = fopen(FILE_BAR, "r");
    FILE *fTemp = fopen(FILE_BAR_TEMP, "w");

    if (f == NULL || fTemp == NULL) {
        if (f != NULL) fclose(f);
        if (fTemp != NULL) fclose(fTemp);
        printf("Errore apertura file!\n");
        return;
    }

    char riga[256];                                        //salvo riga corrente
    while (fgets(riga, sizeof(riga), f)) {                  //legge file bar.csv riga per riga
        char copia[256];                                    //variabile copia della variabile riga
        strncpy(copia, riga, sizeof(copia) - 1);
        copia[sizeof(copia) - 1] = '\0';

        char *nome_corrente = strtok(copia, ",");           //legge il primo valore della riga fino alla ,
        if (nome_corrente != NULL) {
            if (strcmp(nome_corrente, nome) != 0) {         //ciò che non devo eliminare salvo su file bar temporaneo
                fputs(riga, fTemp);
            }
        }
    }

    fclose(f);
    fclose(fTemp);

    remove(FILE_BAR);                                       //elimino il file bar.csv
    rename(FILE_BAR_TEMP, FILE_BAR);                        //rinomino il file temporaneo con il nome del file originale    

    if (trovato) {
        printf("Bottiglia rimossa con successo.\n");
    } else {
        printf("Bottiglia non trovata.\n");
    }
}

Bottiglia* get_bottiglia(Menu* menu, char* nome) {
    Bottiglia* current = menu->testa;
    
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            return current;
        }
        current = current->next;
    }
    printf("Bottiglia non trovata\n");
    return NULL;
}



