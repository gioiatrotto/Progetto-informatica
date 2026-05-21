#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <storico.h>

visualizzaStorico() {
    int num_tavolo, num_presenti, giorno, mese, anno, id;
    char riga[100];


    FILE *f = fopen("storico.csv", "r");
    if (f == NULL) {
        printf("Errore apertura file storico!\n");
        return;
    }
    
    printf("\n----Storico prenotazioni----\n");
    printf("Tavolo | Presenti | Data | ID\n");
    while (fgets(riga, sizeof(riga), f)) {
        
        sscanf(riga, "%d,%d,%d,%d,%d,%d", &num_tavolo, &num_presenti, &giorno, &mese, &anno, &id);
        printf("%d | %d | %02d/%02d/%04d | %d\n", num_tavolo, num_presenti, giorno, mese, anno, id);
    }
    
    fclose(f);
}
stampaStoricoData() {
    int giorno, mese, anno;
    int num_tavolo, num_presenti, g, m, a, id;
    int cnt=0;
    char riga[100];

    printf("\nInserisci la data da cercare (gg mm aaaa): ");
    scanf("%d %d %d", &giorno, &mese, &anno);
    getchar();

    FILE *f = fopen("storico.csv", "r");
    if (f == NULL) {
        printf("Errore apertura file storico!\n");
        return;
    }
    
    
    printf("\n----Prenotazioni del %02d/%02d/%04d----\n", giorno, mese, anno);

    while (fgets(riga, sizeof(riga), f)) {
        
        sscanf(riga, "%d,%d,%d,%d,%d,%d", &num_tavolo, &num_presenti, &g, &m, &a, &id);
        if (g == giorno && m == mese && a == anno) {
            printf("%d | %d | %d\n", num_tavolo, num_presenti, id);
            cnt++;
        }
    }
    
    if (cnt == 0) {
        printf("Nessuna prenotazione trovata per la data specificata.\n");
    }else 
        printf("Totale prenotazioni trovate: %d\n", cnt);
    
    fclose(f);
}

