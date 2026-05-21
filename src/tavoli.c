#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <tavoli.h>

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
    FILE *fp = fopen("tavoli.csv", "a");  
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    Tavolo T;
    
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
        scanf("%d", &T.tipo);
        getchar();
        if(T.tipo!=0 && T.tipo!=1) {
            printf("\nScelta non valida! Inserisci 0 o 1\n");
        }
    }while(T.tipo!=0 && T.tipo!=1);
    
    fprintf(fp, "%d,%d,%.2f,%d\n", T.tipo, T.max_persone, T.prezzo, T.num_tavolo);
    printf("\n✓ Tavolo aggiunto con successo!\n");
    fclose(fp);
}

void eliminaTavoli(){
    FILE *fp = fopen("tavoli.csv", "r"); 
    FILE *fpTmp = fopen("temp.csv", "w");
    int cerca;
    Tavolo T;

    if (fp == NULL) {
        printf("Nessun tavolo presente!\n");
        return;
    }
    if (fpTmp == NULL) {
        printf("Errore sul file temporaneo!\n");
        return;
    }

    printf("Inserisci il numero del tavolo: ");
    scanf("%d", &cerca);
    getchar();

    while(fread(&T, sizeof(Tavolo),1, fp)){
        if(T.num_tavolo==cerca)
            printf("\nil tavolo numero %d verrà eliminato!!", T.num_tavolo);
        else 
            fprintf(fpTmp, "%d,%d,%.2f,%d\n", T.tipo, T.max_persone, T.prezzo, T.num_tavolo);
    }
    fclose(fp);
    fclose(fpTmp);
    fpTmp= fopen("temp.csv", "r"); 
    fp = fopen("tavoli.csv", "w");
    while(fread(&T, sizeof(Tavolo), 1, fpTmp))
        fwrite(&T, sizeof(Tavolo), 1, fp);

    fclose(fp);
    fclose(fpTmp);
}

void stampaTavoli() {
    FILE *fp = fopen("tavoli.csv", "r");  
    if (fp == NULL) {
        printf("\nNessun tavolo presente!\n");
        return;
    }
    char tipo_str[10];
    Tavolo T;
    printf("\n--- Tavoli ---\n");
    while (fread(&T, sizeof(Tavolo), 1, fp) == 1) {

        if (T.tipo == BASE)
            strcpy(tipo_str, "BASE");
        else
            strcpy(tipo_str, "VIP");

        printf("\nTipo: %s\nNumero massimo persone: %d\nPrezzo: %.2f\nNumero del tavolo: %d\n", tipo_str, T.max_persone, T.prezzo, T.num_tavolo);
    }
    fclose(fp);
}

void trovaTavoli(){
    FILE *fp= fopen("tavoli.csv","r");
    Tavolo T;
    int cerca;
    int flag;
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    printf("Inserisci il numero del tavolo: ");
    scanf("%d", &cerca);
    getchar();

    while(fread(&T ,sizeof(Tavolo),1,fp)==1 && !flag){
        if(T.num_tavolo == cerca){
            char tipo_str[10];
            strcpy(tipo_str, T.tipo == BASE ? "BASE" : "VIP");
            printf("\nTrovato\nTipo: %s\nNumero massimo persone: %d\nPrezzo: %.2f\nNumero del tavolo: %d\n", tipo_str, T.max_persone, T.prezzo, T.num_tavolo);
            flag=1;

        }
    }
    if(!flag)
        printf("\nTavolo non trovato!!!!! ");

    fclose(fp);
}
void modificaTavoli(){
    FILE *fp = fopen("tavoli.csv", "r"); 
    FILE *fpTmp = fopen("temp.csv", "w");
    int cerca;
    Tavolo T;

    if (fp == NULL) {
        printf("Nessun tavolo presente!\n");
        return;
    }
    if (fpTmp == NULL) {
        printf("Errore sul file temporaneo!\n");
        return;
    }
    printf("Inserisci il numero del tavolo che vuoi modificare: ");
    scanf("%d", &cerca);
    getchar();
    while(fread(&T, sizeof(Tavolo),1, fp)){
        if(T.num_tavolo == cerca){
            char tipo_str[10];
            strcpy(tipo_str, T.tipo == BASE ? "BASE" : "VIP");
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
                scanf("%d", &T.tipo);
                getchar();
                if(T.tipo!=0 && T.tipo!=1) {
                    printf("\nScelta non valida! Inserisci 0 o 1\n");
                }
            }while(T.tipo!=0 && T.tipo!=1);
        }
        fwrite(&T, sizeof(Tavolo), 1, fpTmp);
    }
    fclose(fp);
    fclose(fpTmp);
    fp = fopen("temp.csv", "r"); 
    fpTmp = fopen("tavoli.csv", "w");
    while(fread(&T, sizeof(Tavolo), 1, fp))
        fwrite(&T, sizeof(Tavolo), 1, fpTmp);

    fclose(fp);
    fclose(fpTmp);
    printf("\n✓ Tavolo modificato con successo!\n");
}

