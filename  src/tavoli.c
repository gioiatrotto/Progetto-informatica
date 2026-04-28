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

aggiungiTavoli(){
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
    }while(T.tipo!=0 || T.tipo!=1);
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
        if(strcmp(T.num_tavolo,cerca)==0)
            printf("\nil tavolo numero %d verrà eliminato!!", T.num_tavolo);
        else 
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
}

void stampaTavolo() {
    FILE *fp = fopen("tavoli.csv", "r"); // lettura binaria
    if (fp == NULL) {
        printf("Nessun tavolo presente!\n");
        return;
    }

    Tavolo T;
    printf("\n--- Tavoli ---\n");
    while (fread(&T, sizeof(Tavolo), 1, fp) == 1) {
        printf("Tipo: %d \nnumero massimo persone: %s Sesso: %c\n", c.nome, c.telefono, c.sesso);
    }
    fclose(fp);
    printf("---------------\n");
}

