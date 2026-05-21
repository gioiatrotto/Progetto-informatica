#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <clienti.h>

#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/clienti_temp.csv"
#define FILE_ID "data/id.csv"
#define FILE_TAVOLI "data/tavoli.csv"
#define FILE_BAR "data/bar.csv"
#define FILE_PRENOTAZIONI "data/prenotazioni.csv"
#define FILE_STORICO "data/storico.csv"


// Rimuove i caratteri di invio a fine riga
void pulisci_stringa(char *s) {
    size_t lunghezza = strlen(s);                                                       //calcola la lunghezza della stringa
    while (lunghezza > 0 && (s[lunghezza - 1] == '\n' || s[lunghezza - 1] == '\r')) {   //rimuove i caratteri di invio a fine riga
        s[lunghezza - 1] = '\0';                                                        //sostituisce il carattere di invio con il carattere \0
        lunghezza--;                                                                    //decrementa la lunghezza della stringa
    }
}

// Ritorna l'ultimo ID salvato
int prendi_ultimo_id() {
    FILE *f = fopen(FILE_ID, "r");
    int id = 0;                            
    if (f != NULL) {                       //se il file esiste, leggo l'ultimo id salvato dentro id.csv
        fscanf(f, "%d", &id);
        fclose(f);
    }
    return id;
}

// Salva il nuovo ID nel file dedicato
void salva_ultimo_id(int id) {
    FILE *f = fopen(FILE_ID, "w");
    if (f != NULL) {                    //se il file esiste, salvo l'ultimo id dentro id.csv
        fprintf(f, "%d\n", id);
        fclose(f);
    }
}

// Converte una stringa in una struct Cliente. Ritorna 1 se la conversione è avvenuta con successo, 0 altrimenti.
int riga_a_cliente(const char *riga, Cliente *c) {
    char copia[256];                            // crea un buffer di 256 caratteri
    strncpy(copia, riga, sizeof(copia) - 1);    // copio la stringa riga dentro copia lasciando spazio per il \0
    copia[sizeof(copia) - 1] = '\0';
    pulisci_stringa(copia);

    char *pezzo = strtok(copia, ",");         // leggo la riga fino alla prima virgola
    if (pezzo == NULL) return 0;
    c->ID = atoi(pezzo);                        // converto il primo pezzo in intero e lo salvo in c->ID

    pezzo = strtok(NULL, ",");
    if (pezzo == NULL) return 0;
    strcpy(c->nome, pezzo);

    pezzo = strtok(NULL, ",");
    if (pezzo == NULL) return 0;
    strcpy(c->cognome, pezzo);

    pezzo = strtok(NULL, ",");
    if (pezzo == NULL) return 0;
    c->eta = atoi(pezzo);

    return 1;
}
void cercaCliente() {
    int ID_cerca;
    char riga[256];
    int trovato = 0;
    
    printf("\nID da cercare: ");
    scanf("%d", &ID_cerca);
    getchar();

    FILE *f = fopen(FILE_CLIENTI, "r");
    if (f == NULL) {
        printf("\nArchivio vuoto.\n");
        return;
    }

    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1 && c.ID == ID_cerca) {
            printf("Cliente trovato: [%d] %s %s, %d anni\n", c.ID, c.nome, c.cognome, c.eta);
            trovato = 1;
            break;
        }
    }
    fclose(f);
    if (!trovato) printf("ID non trovato.\n");
}
// aggiunge un nuovo cliente al file, con ID automatico incrementale
void aggiungiClienti() {
    Cliente c;
    c.ID = prendi_ultimo_id() + 1;

    printf("\n--- NUOVO CLIENTE ---\n");
    printf("Nome: ");    
    scanf("%s", c.nome);
    getchar();
    printf("Cognome: "); 
    scanf("%s", c.cognome);
    getchar();
    printf("Età: ");     
    scanf("%d", &c.eta);
    getchar();

    FILE *f = fopen(FILE_CLIENTI, "a");
    if (f != NULL) {
        fprintf(f, "%d,%s,%s,%d\n", c.ID, c.nome, c.cognome, c.eta);
        fclose(f);
        salva_ultimo_id(c.ID);
        printf("Salvato con ID: %d\n", c.ID);
    }
}

//stampa tutti i clienti presenti nel file, con ID, nome, cognome ed età
void stampaClienti() {
    FILE *f = fopen(FILE_CLIENTI, "r");
    if (f == NULL) {
        printf("\nArchivio vuoto.\n");
        return;
    }

    char riga[256];
    printf("\n--- LISTA CLIENTI ---\n");
    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1) {
            printf("[%d] %s %s, %d anni\n", c.ID, c.nome, c.cognome, c.eta);
        }
    }
    fclose(f);
}

// elimina un cliente cercandolo per ID. Se trovato, viene rimosso dal file.
void eliminaClienti() {
    int ID_cerca;
    char riga[256];
    int trovato = 0;

    printf("\nID da eliminare: ");
    scanf("%d", &ID_cerca);
    getchar();

    FILE *f = fopen(FILE_CLIENTI, "r");
    FILE *t = fopen(FILE_TEMP, "w");
    if (f == NULL || t == NULL) return;

    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1 && c.ID == ID_cerca) {
            trovato = 1;
            printf("Cliente eliminato con successo.\n");
            continue;
        }
        fputs(riga, t);
    }
    fclose(f);
    fclose(t);

    remove(FILE_CLIENTI);
    rename(FILE_TEMP, FILE_CLIENTI);
    if (trovato == 0)
    printf("ID non trovato.\n");
}

// modifica un cliente cercandolo per ID. Se trovato, viene chiesto di inserire i nuovi dati e il file viene aggiornato.
void modificaCliente() {
    int ID_cerca;
    printf("\nID da modificare: ");
    scanf("%d", &ID_cerca);

    FILE *f = fopen(FILE_CLIENTI, "r");
    FILE *t = fopen(FILE_TEMP, "w");
    if (f == NULL || t == NULL) return;

    char riga[256];
    int trovato = 0;
    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1 && c.ID == ID_cerca) {
            trovato = 1;
            printf("Nuovo Nome: ");    
            scanf("%s", c.nome);
            getchar();
            printf("Nuovo Cognome: "); 
            scanf("%s", c.cognome);
            getchar();
            printf("Nuova Età: ");     
            scanf("%d", &c.eta);
            getchar();
            fprintf(t, "%d,%s,%s,%d\n", c.ID, c.nome, c.cognome, c.eta);
        } else {
            fputs(riga, t);
        }
    }
    fclose(f);
    fclose(t);

    remove(FILE_CLIENTI);
    rename(FILE_TEMP, FILE_CLIENTI);
    if (trovato == 1) printf("Modifica completata.\n");
    else printf("ID non trovato.\n");
}