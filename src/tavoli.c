#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tavoli.h>
#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/tavoli_temp.csv"
#define FILE_ID "data/id.csv"
#define FILE_TAVOLI "data/tavoli.csv"
#define FILE_BAR "data/bar.csv"
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"

typedef enum{
   BASE,
   VIP
}TipoTavolo;

typedef struct{
    TipoTavolo tipo;
    int max_persone;    //numero massimo di persone che puo esserci il tavolo
    float prezzo; 
    int num_tavolo;        
}Tavolo;

void aggiungiTavoli(){
    FILE *fp = fopen(FILE_TAVOLI, "a");  
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    Tavolo T;
    int tipo_int;
    
    printf("\nInserisci il numero del tavolo: ");
    scanf("%d", &T.num_tavolo);
    printf("\nInserisci il numero massimo di persone che può ospitare il tavolo: ");
    scanf("%d", &T.max_persone);
    getchar();
    printf("\nInserisci il prezzo minimo del tavolo: ");
    scanf("%f", &T.prezzo);
    getchar();

    do{
        printf("\nChe tipo di tavolo è? ");
        printf("\n0) BASE ");
        printf("\n1) VIP ");
        scanf("%d", &tipo_int);
        getchar();
        T.tipo = tipo_int;
        if(T.tipo!=0 && T.tipo!=1) {
            printf("\nScelta non valida! Inserisci 0 o 1\n");
        }
    }while(T.tipo!=0 && T.tipo!=1);
    
    fprintf(fp, "%d,%d,%.2f,%d\n", T.tipo, T.max_persone, T.prezzo, T.num_tavolo);
    printf("\n✓ Tavolo aggiunto con successo!\n");
    fclose(fp);
}

void eliminaTavoli(){
    FILE *fp = fopen(FILE_TAVOLI, "r"); 
    FILE *fpTmp = fopen(FILE_TEMP, "w");
    int cerca;
    Tavolo T;
    int tipo_int;

    if (fp == NULL) {
        printf("Nessun tavolo presente!\n");
        return;
    }
    if (fpTmp == NULL) {
        printf("Errore sul file temporaneo!\n");
        fclose(fp);
        return;
    }

    printf("Inserisci il numero del tavolo: ");
    scanf("%d", &cerca);
    getchar();

    while (fscanf(fp, "%d,%d,%f,%d", &tipo_int, &T.max_persone, &T.prezzo, &T.num_tavolo) == 4) {
        T.tipo = tipo_int;
        if (T.num_tavolo == cerca)
            printf("\nil tavolo numero %d verrà eliminato!!", T.num_tavolo);
        else
            fprintf(fpTmp, "%d,%d,%.2f,%d\n", T.tipo, T.max_persone, T.prezzo, T.num_tavolo);
    }

    fclose(fp);
    fclose(fpTmp);

    if (rename(FILE_TEMP, FILE_TAVOLI) != 0) {
        printf("\nErrore durante l'aggiornamento del file tavoli!\n");
    }
}

void stampaTavoli() {
    FILE *fp = fopen(FILE_TAVOLI, "r");  
    if (fp == NULL) {
        printf("\nNessun tavolo presente!\n");
        return;
    }
    char tipo_str[10];
    Tavolo T;
    int tipo_int;
    printf("\n--- Tavoli ---\n");
    while (fscanf(fp, "%d,%d,%f,%d", &tipo_int, &T.max_persone, &T.prezzo, &T.num_tavolo) == 4) {
        T.tipo = tipo_int;

          if (T.tipo == BASE)
            strcpy(tipo_str, "BASE");
        else
            strcpy(tipo_str, "VIP");

        printf("\nTipo: %s\nNumero massimo persone: %d\nPrezzo: %.2f\nNumero del tavolo: %d\n", tipo_str, T.max_persone, T.prezzo, T.num_tavolo);
    }
    fclose(fp);
}

void trovaTavoli(){
    FILE *fp= fopen(FILE_TAVOLI,"r");
    Tavolo T;
    int cerca;
    int flag = 0;
    int tipo_int;
    char tipo_str[10];
    
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    printf("Inserisci il numero del tavolo: ");
    scanf("%d", &cerca);
    getchar();

    while (fscanf(fp, "%d,%d,%f,%d", &tipo_int, &T.max_persone, &T.prezzo, &T.num_tavolo) == 4 && !flag) {
        T.tipo = tipo_int;
        if (T.num_tavolo == cerca) {
            if (T.tipo == BASE)
                strcpy(tipo_str, "BASE");
            else
                strcpy(tipo_str, "VIP");

            printf("\nTrovato\nTipo: %s\nNumero massimo persone: %d\nPrezzo: %.2f\nNumero del tavolo: %d\n", tipo_str, T.max_persone, T.prezzo, T.num_tavolo);
            flag = 1;
        }
    }
    if (!flag)
        printf("\nTavolo non trovato!!!!! ");

    fclose(fp);
}
void modificaTavoli(){
    FILE *fp = fopen(FILE_TAVOLI, "r"); 
    FILE *fpTmp = fopen(FILE_TEMP, "w");
    int cerca;
    Tavolo T;
    char tipo_str[10];
    int tipo_int;

    if (fp == NULL) {
        printf("Nessun tavolo presente!\n");
        return;
    }
    if (fpTmp == NULL) {
        printf("Errore sul file temporaneo!\n");
        fclose(fp);
        return;
    }
    printf("Inserisci il numero del tavolo che vuoi modificare: ");
    scanf("%d", &cerca);
    getchar();
    while (fscanf(fp, "%d,%d,%f,%d", &tipo_int, &T.max_persone, &T.prezzo, &T.num_tavolo) == 4) {
        T.tipo = tipo_int;
        if (T.num_tavolo == cerca) {
            if (T.tipo == BASE)
                strcpy(tipo_str, "BASE");
            else
                strcpy(tipo_str, "VIP");

            printf("\nTrovato\nTipo: %s\nNumero massimo persone: %d\nPrezzo: %.2f\nNumero del tavolo: %d\n", tipo_str, T.max_persone, T.prezzo, T.num_tavolo);

            printf("\nInserisci il nuovo numero del tavolo: ");
            scanf("%d", &T.num_tavolo);
            printf("\nInserisci il nuovo numero massimo di persone che può ospitare il tavolo: ");
            scanf("%d", &T.max_persone);
            getchar();
            printf("\nInserisci il nuovo prezzo minimo del tavolo: ");
            scanf("%f", &T.prezzo);
            getchar();
            do{
                printf("\nChe tipo di tavolo è? ");
                printf("\n0) BASE ");
                printf("\n1) VIP ");
                scanf("%d", &tipo_int);
                getchar();
                T.tipo = tipo_int;
                if(T.tipo!=0 && T.tipo!=1) {
                    printf("\nScelta non valida! Inserisci 0 o 1\n");
                }
            }while(T.tipo!=0 && T.tipo!=1);
        }
        fprintf(fpTmp, "%d,%d,%.2f,%d\n", T.tipo, T.max_persone, T.prezzo, T.num_tavolo);
    }
    fclose(fp);
    fclose(fpTmp);

    if (rename(FILE_TEMP, FILE_TAVOLI) != 0) {
        printf("\nErrore durante l'aggiornamento del file tavoli!\n");
        return;
    }
    printf("\n✓ Tavolo modificato con successo!\n");
}

