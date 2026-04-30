#ifndef CLIENTI_H
#define CLIENTI_H

typedef struct {
    char nome[40];
    char cognome[40];
    int eta;
    int ID;
} Cliente;

void aggiungiClienti(void);
void stampaClienti(void);
void eliminaClienti(void);
void cercaClienti(void);
void modificaClienti(void);

#endif // CLIENTI_H
