#include "T4.h"

void tache4()
{
    if ((STID_CODE==1)&&(tempon_presence_cle==0))
    {
        temps_initial=Timer_G;
        tempon_presence_cle=1;
    }
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


void add_data_time (char data_J, char adress_H, char adress_L)
{
    unsigned char data_t=read_EEPROM(adress_H, adress_L);
    data_t=data_t+data_J;
    write_EEPROM(data_t,adress_H, adress_L);
}

void follow_driver_timer (char temps_end, char temps_ini)
{
    unsigned char adresslow=conv_badge_8bitsl();
    unsigned char adresshigh=conv_badge_8bitsh();
    unsigned char temps_act_normal = temps_end - temps_ini ;
    add_data_time(temps_act_normal,adresslow,adresshigh);
}

char conv_badge_8bitsl (void)
{
    unsigned badge_t=0;
    for (unsigned char i=0; i<8; i++)
    {
        badge_t=badge_t+badge[i]<<i;
    }
    return badge_t;
}

char conv_badge_8bitsh (void)
{
    unsigned badge_t=0;
    for (unsigned char i=0; i<2; i++)
    {
        badge_t=badge_t+badge[i+8]<<i;
    }
    return badge_t;
}


        // Variable récupération variable timer
        // temps utilisation normale
        // temps utilisation anormale
        // temps de non utilisation
        // temps maintenance
        //temps utilisation conducteur N
        // temps utilisation anormale conducteur N
// envoie des informations sur demande avec condition d'accés
