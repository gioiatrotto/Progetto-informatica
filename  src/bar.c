#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
    char nome[50];
    float gradazione;
}drink;

void aggiungiBottiglia(){
    drink menu[4];
    
    strcpy(menu[0].nome, "Anima Latina");
    menu[0].gradazione = 12.00;

    strcpy(menu[1].nome, "Veleno Dolce");
    menu[1].gradazione = 10.00;

    strcpy(menu[2].nome, "Oro Tropicale");
    menu[2].gradazione = 14.00;

    strcpy(menu[3].nome, "Breeze");
    menu[3].gradazione = 0;
}

