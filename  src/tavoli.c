typedef enum{
   BASE,
   VIP
}TipoTavolo;

typedef struct{
    TipoTavolo tipo;
    int max_persone;    //numero massimo di persone che puo esserci il tavolo
    float prezzo;       //prezzo base di ogni tavolo
}Tavolo;