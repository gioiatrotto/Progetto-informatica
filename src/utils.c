#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <utils.h>

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