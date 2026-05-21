#ifndef STORICO_H
#define STORICO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* 
La funzione visualizzaStorico stampa a schermo lo storico delle prenotazioni, mostrando le informazioni di ogni prenotazione presente nel file storico.csv 
*/   
void visualizzaStorico();
              
/*       
La funzione stampaStoricoData prende in input una data e stampa a schermo lo storico delle prenotazioni per quella data, mostrando le informazioni di ogni prenotazione presente nel file storico.csv per quella data           
*/                
void stampaStoricoData();

#endif
        



