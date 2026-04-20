typedef enum{
   BASE,
   VIP
}TipoTavolo;

typedef struct{
    TipoTavolo tipo;
    int max_persone;
    float prezzo;
}