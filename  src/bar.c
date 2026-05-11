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

Bottiglia get_bottiglia(Menu* menu, char* nome) {
    Bottiglia* current = menu->testa;
    
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0) {
            return *current;
        }
        current = current->next;
    }
    printf("Bottiglia non trovata\n");
    return (Bottiglia){ .nome = "", .gradazione = 0, .prezzo = 0 };
}



