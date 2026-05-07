#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_CLIENTI "data/clienti.csv"
#define FILE_TEMP "data/clienti_temp.csv"
#define FILE_ID "data/id.csv"

typedef struct {
    char nome[40];
    char cognome[40];
    int eta;
    int id;
} Cliente;

// Rimuove i caratteri di invio a fine riga
void pulisci_stringa(char *s) {
    size_t lunghezza = strlen(s);
    while (lunghezza > 0 && (s[lunghezza - 1] == '\n' || s[lunghezza - 1] == '\r')) {
        s[lunghezza - 1] = '\0';
        lunghezza--;
    }
}

// Ritorna l'ultimo ID salvato
int prendi_ultimo_id() {
    FILE *f = fopen(FILE_ID, "r");
    int id = 0;
    if (f != NULL) {
        fscanf(f, "%d", &id);
        fclose(f);
    }
    return id;
}

// Salva il nuovo ID nel file dedicato
void salva_ultimo_id(int id) {
    FILE *f = fopen(FILE_ID, "w");
    if (f != NULL) {
        fprintf(f, "%d\n", id);
        fclose(f);
    }
}

// Converte una stringa in una struttura Cliente. Ritorna 1 se ok, 0 se errore.
int riga_a_cliente(const char *riga, Cliente *c) {
    char copia[256];
    strncpy(copia, riga, sizeof(copia) - 1);
    pulisci_stringa(copia);

    char *pezzo = strtok(copia, ",");
    if (pezzo == NULL) return 0;
    c->id = atoi(pezzo);

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

// aggiunge un nuovo cliente al file, con ID automatico incrementale
void aggiungi() {
    Cliente c;
    c.id = prendi_ultimo_id() + 1;

    printf("\n--- NUOVO CLIENTE ---\n");
    printf("Nome: ");    
    scanf("%s", c.nome);
    printf("Cognome: "); 
    scanf("%s", c.cognome);
    printf("Età: ");     
    scanf("%d", &c.eta);

    FILE *f = fopen(FILE_CLIENTI, "a");
    if (f != NULL) {
        fprintf(f, "%d,%s,%s,%d\n", c.id, c.nome, c.cognome, c.eta);
        fclose(f);
        salva_ultimo_id(c.id);
        printf("Salvato con ID: %d\n", c.id);
    }
}

//stampa tutti i clienti presenti nel file, con ID, nome, cognome ed età
void elenco() {
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
            printf("[%d] %s %s, %d anni\n", c.id, c.nome, c.cognome, c.eta);
        }
    }
    fclose(f);
}

// elimina un cliente cercandolo per ID. Se trovato, viene rimosso dal file.
void elimina() {
    int id_cerca;
    printf("\nID da eliminare: ");
    scanf("%d", &id_cerca);

    FILE *f = fopen(FILE_CLIENTI, "r");
    FILE *t = fopen(FILE_TEMP, "w");
    if (f == NULL || t == NULL) return;

    char riga[256];
    int trovato = 0;
    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1 && c.id == id_cerca) {
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
    if (trovato == 0) printf("ID non trovato.\n");
}

// modifica un cliente cercandolo per ID. Se trovato, viene chiesto di inserire i nuovi dati e il file viene aggiornato.
void modifica() {
    int id_cerca;
    printf("\nID da modificare: ");
    scanf("%d", &id_cerca);

    FILE *f = fopen(FILE_CLIENTI, "r");
    FILE *t = fopen(FILE_TEMP, "w");
    if (f == NULL || t == NULL) return;

    char riga[256];
    int trovato = 0;
    while (fgets(riga, sizeof(riga), f)) {
        Cliente c;
        if (riga_a_cliente(riga, &c) == 1 && c.id == id_cerca) {
            trovato = 1;
            printf("Nuovo Nome: ");    
            scanf("%s", c.nome);
            printf("Nuovo Cognome: "); 
            scanf("%s", c.cognome);
            printf("Nuova Età: ");     
            scanf("%d", &c.eta);
            fprintf(t, "%d,%s,%s,%d\n", c.id, c.nome, c.cognome, c.eta);
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