typedef struct{
    int giorno;
    int mese;
    int anno; 
    
}Data;

typedef struct{
    int num_presenti;       // numero delle persone effettive al tavolo
    char nome_prenotazione; //nome con cui prenota il cliente
    bool booked;            //se il tavolo è libero o no
    Data date;
}prenotazione;

