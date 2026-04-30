#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CLIENTI_FILE "data/clienti.csv"
#define CLIENTI_TEMP_FILE "data/clienti_temp.csv"
#define ID_FILE "data/id.csv"

typedef struct {
    char nome[40];
    char cognome[40];
    int eta;
    int ID;
} Cliente;

void trimNewline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

static int leggiUltimoID(void) {
    FILE *fp = fopen(ID_FILE, "r");
    int id = 0;
    if (fp == NULL) {
        return 0;
    }
    if (fscanf(fp, "%d", &id) != 1) {
        id = 0;
    }
    fclose(fp);
    return id;
}

static void scriviUltimoID(int id) {
    FILE *fp = fopen(ID_FILE, "w");
    if (fp == NULL) {
        printf("Impossibile aggiornare %s\n", ID_FILE);
        return;
    }
    fprintf(fp, "%d\n", id);
    fclose(fp);
}

static bool leggiClienteDaLinea(const char *linea, Cliente *c) {
    char buffer[256];
    strncpy(buffer, linea, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    trimNewline(buffer);

    char *token = strtok(buffer, ",");
    if (token == NULL) {
        return false;
    }
    c->ID = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;
    }
    strncpy(c->nome, token, sizeof(c->nome) - 1);
    c->nome[sizeof(c->nome) - 1] = '\0';

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;
    }
    strncpy(c->cognome, token, sizeof(c->cognome) - 1);
    c->cognome[sizeof(c->cognome) - 1] = '\0';

    token = strtok(NULL, ",");
    if (token == NULL) {
        return false;
    }
    c->eta = atoi(token);
    return true;
}

void aggiungiClienti(void) {
    Cliente c;
    int ultimoID = leggiUltimoID();
    c.ID = ultimoID + 1;

    printf("\n--- Aggiungi cliente ---\n");
    printf("Nome: ");
    scanf(" %39[^"]", c.nome);
    printf("Cognome: ");
    scanf(" %39[^"]", c.cognome);
    printf("Età: ");
    scanf("%d", &c.eta);

    FILE *fp = fopen(CLIENTI_FILE, "a");
    if (fp == NULL) {
        printf("Impossibile aprire %s per scrittura.\n", CLIENTI_FILE);
        return;
    }
    fprintf(fp, "%d,%s,%s,%d\n", c.ID, c.nome, c.cognome, c.eta);
    fclose(fp);

    scriviUltimoID(c.ID);
    printf("Cliente aggiunto con ID %d.\n", c.ID);
}

void stampaClienti(void) {
    FILE *fp = fopen(CLIENTI_FILE, "r");
    if (fp == NULL) {
        printf("\nNessun cliente presente.\n");
        return;
    }

    printf("\n--- Elenco clienti ---\n");
    char linea[256];
    int count = 0;
    while (fgets(linea, sizeof(linea), fp)) {
        if (linea[0] == '\n' || linea[0] == '\0') {
            continue;
        }
        Cliente c;
        if (leggiClienteDaLinea(linea, &c)) {
            printf("\nID: %d\nNome: %s\nCognome: %s\nEtà: %d\n", c.ID, c.nome, c.cognome, c.eta);
            count++;
        }
    }
    fclose(fp);
    if (count == 0) {
        printf("Nessun cliente registrato.\n");
    }
}

void eliminaClienti(void) {
    int idCancellare;
    printf("\n--- Eliminazione cliente ---\n");
    printf("Inserisci ID cliente: ");
    scanf("%d", &idCancellare);

    FILE *fp = fopen(CLIENTI_FILE, "r");
    if (fp == NULL) {
        printf("Nessun cliente presente.\n");
        return;
    }

    FILE *tmp = fopen(CLIENTI_TEMP_FILE, "w");
    if (tmp == NULL) {
        printf("Impossibile creare file temporaneo.\n");
        fclose(fp);
        return;
    }

    char linea[256];
    bool trovato = false;
    while (fgets(linea, sizeof(linea), fp)) {
        Cliente c;
        if (!leggiClienteDaLinea(linea, &c)) {
            continue;
        }
        if (c.ID == idCancellare) {
            printf("Cliente eliminato: %s %s (ID %d)\n", c.nome, c.cognome, c.ID);
            trovato = true;
            continue;
        }
        fputs(linea, tmp);
    }
    fclose(fp);
    fclose(tmp);

    if (trovato) {
        remove(CLIENTI_FILE);
        rename(CLIENTI_TEMP_FILE, CLIENTI_FILE);
    } else {
        remove(CLIENTI_TEMP_FILE);
        printf("Nessun cliente trovato con ID %d.\n", idCancellare);
    }
}

void cercaClienti(void) {
    int idRicerca;
    printf("\n--- Cerca cliente ---\n");
    printf("Inserisci ID cliente: ");
    scanf("%d", &idRicerca);

    FILE *fp = fopen(CLIENTI_FILE, "r");
    if (fp == NULL) {
        printf("Nessun cliente presente.\n");
        return;
    }

    char linea[256];
    bool trovato = false;
    while (fgets(linea, sizeof(linea), fp)) {
        Cliente c;
        if (leggiClienteDaLinea(linea, &c) && c.ID == idRicerca) {
            printf("\nID: %d\nNome: %s\nCognome: %s\nEtà: %d\n", c.ID, c.nome, c.cognome, c.eta);
            trovato = true;
            break;
        }
    }
    fclose(fp);

    if (!trovato) {
        printf("Cliente con ID %d non trovato.\n", idRicerca);
    }
}

void modificaClienti(void) {
    int idModifica;
    printf("\n--- Modifica cliente ---\n");
    printf("Inserisci ID cliente: ");
    scanf("%d", &idModifica);

    FILE *fp = fopen(CLIENTI_FILE, "r");
    if (fp == NULL) {
        printf("Nessun cliente presente.\n");
        return;
    }

    FILE *tmp = fopen(CLIENTI_TEMP_FILE, "w");
    if (tmp == NULL) {
        printf("Impossibile creare file temporaneo.\n");
        fclose(fp);
        return;
    }

    char linea[256];
    bool trovato = false;
    while (fgets(linea, sizeof(linea), fp)) {
        Cliente c;
        if (!leggiClienteDaLinea(linea, &c)) {
            continue;
        }
        if (c.ID == idModifica) {
            printf("Cliente trovato: %s %s (ID %d)\n", c.nome, c.cognome, c.ID);
            printf("Nuovo nome (premi invio per mantenere lo stesso): ");
            char nuovoNome[40];
            scanf(" %39[^"]", nuovoNome);
            if (strlen(nuovoNome) > 0) {
                strncpy(c.nome, nuovoNome, sizeof(c.nome) - 1);
                c.nome[sizeof(c.nome) - 1] = '\0';
            }
            printf("Nuovo cognome (premi invio per mantenere lo stesso): ");
            char nuovoCognome[40];
            scanf(" %39[^"]", nuovoCognome);
            if (strlen(nuovoCognome) > 0) {
                strncpy(c.cognome, nuovoCognome, sizeof(c.cognome) - 1);
                c.cognome[sizeof(c.cognome) - 1] = '\0';
            }
            printf("Nuova età (0 per mantenere la stessa): ");
            int nuovaEta;
            scanf("%d", &nuovaEta);
            if (nuovaEta > 0) {
                c.eta = nuovaEta;
            }
            fprintf(tmp, "%d,%s,%s,%d\n", c.ID, c.nome, c.cognome, c.eta);
            trovato = true;
        } else {
            fputs(linea, tmp);
        }
    }

    fclose(fp);
    fclose(tmp);

    if (trovato) {
        remove(CLIENTI_FILE);
        rename(CLIENTI_TEMP_FILE, CLIENTI_FILE);
        printf("Cliente aggiornato con successo.\n");
    } else {
        remove(CLIENTI_TEMP_FILE);
        printf("Cliente con ID %d non trovato.\n", idModifica);
    }
}
