#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bar.c"
#include "clienti.c"
#include "file_io.c"
#include "prenotazioni.c"
#include "tavoli.c"
#include "utils.c"

int main(){ 
    int scelta=0, sceltaClienti=0,sceltaTavoli=0,sceltaBottiglia=0, scelta_statistiche;

    do{
        printf("\nBENVENUTI AD ABYSSIA\n");
        printf("cosa vuoi gestire?\n");
        printf("1) Clienti\n");
        printf("2) Tavoli\n");
        printf("3) Bar\n");
        printf("4) Visualizza storico\n");
        printf("0) Esci\n");
        scanf("%d", &scelta);


        switch(scelta){

        case 1:
            do{
                printf("\n---Clienti---\n");
                printf("1) Aggiungi clienti\n");
                printf("2) Stampa lista clienti\n");
                printf("3) Eliminazione clienti\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaClienti);

                switch(sceltaClienti){
                    case 1:
                        aggiungiClienti();
                        break;

                    case 2:
                        stampaClienti();
                        break;

                    case 3:
                        eliminaClienti();
                        break;

                    case 0:
                        printf("\nVai alla home.\n");
                        break;
                    
                    default:
                        printf("\n!!!ERRORE!!!\n");
                    break;
                }
            }while(sceltaClienti!=0);
            break;

        case 2:
            do{
                printf("\n---Tavoli---\n");
                printf("1) Aggiungi tavolo\n");
                printf("2) Elimina tavolo\n");
                printf("3) Modifica tavolo\n");
                printf("4) Stampa tavolo\n");
                printf("5) Trova tavolo\n");
                printf("6) Prenota Tavolo\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaTavoli);

                switch(sceltaTavoli){
                    case 1:
                        aggiungiTavoli();
                        break;

                    case 2:
                        eliminaTavoli();
                        break;

                    case 3:
                        modificaTavoli();
                        break;

                    case 4:
                        stampaTavoli();
                        break;

                    case 5:
                        trovaTavoli();
                        break;
                    case 6:
                        prenotaTavolo();
                        break;
                    case 0:
                        printf("\nSei tornato al menù principale.\n");
                        break;
                        
                    default:
                        printf("\n!!!ERRORE!!!\n");
                    break;
                }
            }while(sceltaTavoli!=0);
            break;

        case 3:
            do{
                printf("\n----Bar----\n");
                printf("1) Scegli la bottiglia in omaggio\n");
                printf("2) Elimina la bottiglia dal tavolo\n");
                printf("3) Modifica la bottiglia dal tavolo\n");
                printf("4) Aggiungi una bottiglia dal menù\n");
                printf("5) Elimina una bottiglia dal menù\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaBottiglia);

                switch(sceltaBottiglia){
                    case 1:
                        scegliBottigliaTavolo();
                        break;

                    case 2:
                        eliminaBottigliaTavolo();
                        break;

                    case 3:
                        modificaBottigliaTavolo();
                        break;
                    case 4:
                        aggiungiBottigliaMenu();
                        break;
                    case 5:
                        eliminaBottigliaMenu();
                        break;

                    case 0:
                        printf("\nVai alla home.\n");
                        break;
                    
                    default:
                        printf("\n!!!ERRORE!!!\n");
                    break;
                }
            }while(sceltaBottiglia!=0);
            break;

        case 4:
            do{
                printf("\n----Storico----\n");
                printf("1) \n");
                printf("2. Utente con più prestiti\n");
                printf("3. Visualizza storico prestiti\n");
                printf("4. Visualizza tasso di restituzione\n");
                printf("5. Visualizza generi più richiesti\n");
                printf("0. Esci\n");
                printf("Scelta: ");
                scanf("%d", &scelta_statistiche);

                switch(scelta_statistiche){
                    case 1:
                        libroPiuPrestato();
                        break;

                    case 2:
                        utentePiuPrestiti();
                        break;

                    case 3:
                        storicoPrestiti();
                        break;

                    case 4:
                        tassoRestituzione();
                        break;

                    case 5:
                        generiPiuRichiesti();
                        break;

                    case 0:
                        printf("\nSei tornato al menù principale.\n");
                        break;
                        
                    default:
                        printf("\nScelta non valida.\n");
                    break;
                }
            }while(scelta_statistiche!=0);
            break;

        case 0:
            printf("\nSei uscito dal programma.\n");
            break;

        default:
            printf("\nOpzione non valida.\n");
            break;
        }
        
    }while(scelta!=0);

    return 0;
}


