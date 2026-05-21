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
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"


Menu* creaMenu() {
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    menu->testa = NULL;
    menu->lunghezza = 0;
    return menu;
}
void stampa_menu_bottiglie(Menu* menu) {
    Bottiglia* current = menu->testa;
    
    printf("Menu delle bottiglie:\n");
    while (current != NULL) {
        printf("%s (Gradazione: %.2f, Prezzo: %.2f) -> ", current->nome, current->gradazione, current->prezzo);
        current = current->next;
    }
    printf("NULL\n");
    printf("Lunghezza: %d\n", menu->lunghezza);
}

void aggiungi_bottiglia_menu(Menu* menu, float gradazione, float prezzo, char* nome) {
    Bottiglia* nuovaBottiglia = (Bottiglia*)malloc(sizeof(Bottiglia));
    nuovaBottiglia->gradazione = gradazione;
    nuovaBottiglia->prezzo = prezzo;
    strcpy(nuovaBottiglia->nome, nome);
    nuovaBottiglia->next = menu->testa;
    menu->testa = nuovaBottiglia;
    menu->lunghezza++;
}

void rimuovi_bottiglia_menu(Menu* menu, char* nome ){
    if (menu->testa == NULL) return;
    
    if (menu->testa->nome == nome) {
        Bottiglia* temp = menu->testa;
        menu->testa = menu->testa->next;
        free(temp);
        menu->lunghezza--;
        return;
    
    }
    Bottiglia* current = menu->testa;
    while (current->next != NULL) {
        if (current->next->nome == nome) {
            Bottiglia* temp = current->next;
            current->next = current->next->next;
            free(temp);
            menu->lunghezza--;
            return;
        }
        current = current->next;
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



