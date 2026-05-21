#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <prenotazioni.h>
#include <bar.h>

#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/clienti_temp.csv"
#define FILE_ID "data/id.csv"
#define FILE_TAVOLI "data/tavoli.csv"
#define FILE_BAR "data/bar.csv"
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"

typedef struct{
    int giorno;
    int mese;
    int anno; 
    
}Data;
typedef struct Meta{
    char nome[30];
    char descrizione[300];
    Data data_evento;
} Meta;

Meta eventi[3] = {
    {"Santorini", "Festa sulla Caldera, musica house, un tuffo nel blu, e il sole che scompare nel vulcano ", {6, 6, 2026}},
    {"Albufeira", "Grotte dorate e serata Perreo: party offshore più caliente dell'Algarve", {14, 7, 2026}},
    {"Pag", "Cassa dritta in mare aperto: rotta techno verso il delirio di Zrce", {15, 8, 2026}},
};

typedef struct{
    int num_presenti;               // numero delle persone effettive al tavolo
    int id;                         // id del cliente che ha prenotato                    
    int num_tavolo;                 // numero del tavolo prenotato
    Bottiglia* bottiglia_omaggio;   // bottiglia in omaggio per il tavolo
    Meta meta_scelta;               // meta scelta per la prenotazione
                          
}prenotazione;

void stampa_mete(){
    printf("\n----Mete----\n");
    for(int i=0; i<3; i++){
        printf("%d) %s - %s (Data evento: %02d/%02d/%04d)\n", i+1, eventi[i].nome, eventi[i].descrizione, eventi[i].data_evento.giorno, eventi[i].data_evento.mese, eventi[i].data_evento.anno);
    }
}

void prenotaTavolo(Menu* menu){
    char nome_bottiglia[50];
    int scelta;

    prenotazione P;
    FILE *fp = fopen(FILE_PRENOTAZIONI, "a");
    FILE  *f = fopen(FILE_STORICO, "a");
    
    if (fp == NULL) {
        printf("Errore apertura file prenotazioni!\n");
        return;
    }
    if (f == NULL) {
        printf("Errore apertura file storico!\n");
        return;
    }
    
    printf("\nInserisci il numero del tavolo da prenotare: ");
    scanf("%d", &P.num_tavolo);
    getchar();

    printf("\nInserisci il numero di persone che saranno presenti al tavolo: ");
    scanf("%d", &P.num_presenti);
    getchar();

    printf("\nIn che meta vuoi andare? ");
    stampa_mete();

    printf("Scegli la meta(1-3): ");
    scanf("%d", &scelta);
    getchar();
    
    do{
        printf("\nScegli la meta(1-3): ");
        scanf("%d", &scelta);
        getchar();
        
    }while(scelta < 1 || scelta > 3);
    P.meta_scelta = eventi[scelta-1];            //scelta -1 perche l'utente sceglie da 1 a 3 ma noi nell'array partiamo da 0

    printf("\nInserisci l'id del cliente che ha prenotato: ");
    scanf("%d", &P.id);
    getchar();

    printf("\nChe bottiglia in omaggio vuoi per il tavolo? ");
    stampa_menu_bottiglie(menu);
    printf("Inserisci il nome della bottiglia in omaggio: ");
    scanf("%s", nome_bottiglia);
    getchar();
    P.bottiglia_omaggio = get_bottiglia(menu, nome_bottiglia);

    fprintf(fp, "%d,%d,%d,%d,%d,%d\n", P.num_tavolo, P.num_presenti, P.meta_scelta.data_evento.giorno, P.meta_scelta.data_evento.mese, P.meta_scelta.data_evento.anno, P.id);
    fprintf(f, "%d,%d,%d,%d,%d,%d\n", P.num_tavolo, P.num_presenti, P.meta_scelta.data_evento.giorno, P.meta_scelta.data_evento.mese, P.meta_scelta.data_evento.anno, P.id);
    fclose(fp);
    fclose(f);

}





