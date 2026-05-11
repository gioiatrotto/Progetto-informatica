typedef struct{
    int giorno;
    int mese;
    int anno; 
    
}Data;

typedef struct{
    int num_presenti;               // numero delle persone effettive al tavolo
    int id;                         // id del cliente che ha prenotato                    
    int num_tavolo;                 // numero del tavolo prenotato
    Bottiglia* bottiglia_omaggio;   // bottiglia in omaggio per il tavolo
    Data date;                      // data della prenotazione
}prenotazione;

void prenotaTavolo(Menu* menu){
    char nome_bottiglia[50];

    prenotazione P;
    FILE *fp = fopen("prenotazioni.csv", "a");
    if (fp == NULL) {
        printf("Errore apertura file!\n");
        return;
    }
    
    printf("\nInserisci il numero del tavolo da prenotare: ");
    scanf("%d", &P.num_tavolo);
    getchar();
    printf("\nInserisci il numero di persone che saranno presenti al tavolo: ");
    scanf("%d", &P.num_presenti);
    getchar();
    printf("\nInserisci la data della prenotazione (gg mm aaaa): ");
    scanf("%d %d %d", &P.date.giorno, &P.date.mese, &P.date.anno);
    getchar();
    printf("\nInserisci l'id del cliente che ha prenotato: ");
    scanf("%d", &P.id);
    getchar();
    printf("\nChe bottiglia in omaggio vuoi per il tavolo? ");
    stampa_menu_bottiglie(menu);
    printf("Inserisci il nome della bottiglia in omaggio: ");
    scanf("%s", nome_bottiglia);
    getchar();
    P.bottiglia_omaggio = get_bottiglia_menu(menu, nome_bottiglia);
    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d\n", P.num_tavolo, P.num_presenti, P.date.giorno, P.date.mese, P.date.anno, P.id);
    fclose(fp);

}



