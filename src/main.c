#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <bar.h>
#include <clienti.h>
#include <prenotazioni.h>
#include <storico.h>
#include <tavoli.h>
#include <utils.h>

extern int id_cliente;

int main(){ 
    leggiID();
    int scelta=0;
    int sceltaClienti=0;
    int sceltaTavoli=0;
    int sceltaBottiglia=0;
    int sceltaStorico=0;

    Menu* menu = creaMenu();
    carica_menu_bottiglie(menu);

    do{
        printf("\nBENVENUTI AD ABYSSIA\n");
        printf("cosa vuoi gestire?\n");
        printf("1) Clienti\n");
        printf("2) Tavoli\n");
        printf("3) Bar\n");
        printf("4) Visualizza storico\n");
        printf("0) Esci\n");
        scanf("%d", &scelta);
        getchar();


        switch(scelta){

        case 1:
            do{
                printf("\n---Clienti---\n");
                printf("1) Cerca cliente\n");
                printf("2) Aggiungi cliente \n");
                printf("3) Stampa clienti\n");
                printf("4) Eliminazione cliente \n");
                printf("5) Modifica cliente\n");
                printf("0) Vai alla home\n");

                //cerca cliente
                scanf("%d", &sceltaClienti);
                getchar();

                switch(sceltaClienti){
                    case 1:
                        cercaCliente();
                        break;  
                    case 2:
                        aggiungiClienti();
                        break;

                    case 3:
                        stampaClienti();
                        break;

                    case 4:
                        eliminaClienti();
                        break;
                    case 5:
                        modificaCliente();
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
                printf("7) modifica prenotazione\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaTavoli);
                getchar();

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
                        prenotaTavolo(menu);
                        break;
                    case 7:
                        // modificaPrenotazione();  // TODO: Funzione non ancora implementata
                        printf("Funzione non ancora implementata.\n");
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
            char _nome[50];
            float _prezzo;
            float _gradazione;
            do{
                printf("\n----Bar----\n");
                printf("1) Mostra menu bottiglie\n");
                printf("2) Aggiungi bottiglia al menù\n");
                printf("3) Elimina bottiglia dal menù\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaBottiglia);
                getchar();

                switch(sceltaBottiglia){
                    case 1:
                        stampa_menu_bottiglie(menu);
                        break;

                    case 2:
                        
                        printf("Inserisci il nome della bottiglia: ");
                        scanf("%s", _nome);
                        getchar();
                        printf("Inserisci il prezzo: ");
                        scanf("%f", &_prezzo);
                        getchar();
                        printf("Inserisci la gradazione alcolica: ");
                        scanf("%f", &_gradazione);
                        getchar();
                        aggiungi_bottiglia_menu(menu, _gradazione, _prezzo, _nome);
                        break;

                    case 3:
                        printf("Inserisci il nome della bottiglia da eliminare: ");
                        scanf("%s", _nome);
                        getchar();
                        rimuovi_bottiglia_menu(menu, _nome);
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
                printf("2) Stampa storico di una determinaa data\n");
                printf("0) Vai alla home\n");
                scanf("%d", &sceltaStorico);

                switch(sceltaStorico){
                    case 1:
                        visualizzaStorico();
                        break;

                    case 2:
                        stampaStoricoData();
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


