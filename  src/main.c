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

int id_cliente = 0;

int main(){ 
    leggiID();
    int scelta=0;
    int sceltaClienti=0;
    int sceltaTavoli=0;
    int sceltaBottiglia=0;
    int sceltaStorico=0;

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
                printf("1) Cerca cliente\n");
                printf("2) Aggiunmgi cliente \n");
                printf("4) Stampa clienti\n");
                printf("3) Eliminazione cliente \n");
                printf("4) Modifica cliente\n");
                printf("0) Vai alla home\n");

                //cerca cliente
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
                printf("4) Stampa tavoli\n");
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
                printf("1) Visualizzza tutto lo storico\n");
                printf("2) Stampa storico di un determinato giorno\n");
                printf("3) Stampa storico in ordine alfabetico \n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaStorico);

                switch(sceltaStorico){
                    case 1:
                        visualizzaStorico();
                        break;

                    case 2:
                        stampaStoricoData();
                        break;

                    case 3:
                        stampaStoricoAlfa();
                        break;

                    case 0:
                        printf("\nSei tornato al menù principale.\n");
                        break;
                        
                    default:
                        printf("\n!!!ERRORE!!!\n");
                        break;
                }
            }while(sceltaStorico!=0);
            break;

        case 0:
            printf("\n---Uscita dal programma---\n");
            break;

        default:
            printf("\n!!!ERRORE!!!\n");
            break;
        }
        
    }while(scelta!=0);

    return 0;
}


