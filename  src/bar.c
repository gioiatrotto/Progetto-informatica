#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    char nome[50];
    float gradazione;
}Bottiglia;

void aggiungi_bottiglia(){
    Bottiglia b;
    printf("nome del drink: ");
    scanf("%s", b.nome);
    printf("gradazione: ");
    scanf("%f", &b.gradazione);

    FILE *f = fopen("bar.csv", "a");
    if(f != NULL){
        fprintf(f, "%s,%.2f\n", b.nome, b.gradazione);
        fclose(f);
        printf("Bottiglia aggiunta con successo!\n");
    } else {
        printf("Errore nell'apertura del file!\n");
    }
}
