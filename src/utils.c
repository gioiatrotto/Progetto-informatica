#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <utils.h>
#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/clienti_temp.csv"
#define FILE_ID "data/id.csv"
#define FILE_TAVOLI "data/tavoli.csv"
#define FILE_BAR "data/bar.csv"
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"

int id_cliente = 0;

void leggiID(){
    FILE* file = fopen("id_cliente.txt", "r");
    if(file == NULL){
        printf("Errore nell'apertura del file id_cliente.txt\n");
        return;
    }
    fscanf(file, "%d", &id_cliente);
    fclose(file);
}