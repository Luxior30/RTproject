#include "T4.h"

void tache4()
{
    
}

void write_EEPROM (char data, char adressH, char adressL)
{
    EEADRH=adressH;
    EEADRH=adressL;
    EEDATA=data;
    EECON1bits.WREN=1;
    INTCONbits.GIE=0;
    
    EECON2=0x55;
    EECON2=0xAA;
    EECON1bits.WR=1;
    while (EECON1bits.WR==1);
    
    INTCONbits.GIE=1;
    EECON1bits.WREN=0;
}

char read_EEPROM (char adressH, char adressL)
{
    EEADRH=adressH;
    EEADRH=adressL;
    EECON1bits.RD=1;
    while(EECON1bits.RD==1);
    unsigned char data = EEDATA;
    return data;
}


void add_timer (char data_J, char adressH, char adressL)
{
    unsigned char data_t=data_J+read_EEPROM(adressH, adressL);
    write_EEPROM(data_t,adressH, adressL);
}
        // Variable récupération variable timer
        // temps utilisation normale
        // temps utilisation anormale
        // temps de non utilisation
        // temps maintenance
        //temps utilisation conducteur N
        // temps utilisation anormale conducteur N
// envoie des informations sur demande avec condition d'accés
