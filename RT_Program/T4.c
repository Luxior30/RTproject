#include "T4.h"

void tache4()
{
    if ((tempon_presence_cle==0)&&(STID_CODE==1))
    {
        tempon_presence_cle==1; // mise a un de la variable indiquant la pr�sence de cle
        temps_initial=Timer_G; // initialisation du compteur de temps
    }
    
    if ((tempon_presence_cle==1)&&(STID_CODE==0))
    {
        tempon_presence_cle==0; // mise a zero de la variable indiquant la pr�sence de cle
        follow_driver_timer();
    }
    
}

void write_EEPROM (char data, char adressH, char adressL)
{
    EEADRH=adressH; // r�cup�ration de la valeur des huit bit de poids fort de l'adresse EEPROM 
    EEADR=adressL; // r�cup�ration de la valeur des huit  bit de poids faible de l'adresse EEPROM 
    EEDATA=data; // donn�e � �crire
    EECON1bits.WREN=1; // autorisation de communiquer avec EEPROM
    INTCONbits.GIE=0; // interdiction d'utiliser des interruptions pendant l'�criture
    
    EECON2=0x55; // commande obligatoire
    EECON2=0xAA; //commande obligatoire
    EECON1bits.WR=1; // autorisation d'�criture
    while (EECON1bits.WR==1); // attente de la fin du processus d'�criture ; WR retourne automatiquement a 0 � la fin du processus
    
    INTCONbits.GIE=1; // Autorisation des interruptions
    EECON1bits.WREN=0; // fin de la communication avec EEPROM
}

char read_EEPROM (char adressH, char adressL)
{
    EEADRH=adressH; // r�cup�ration de la valeur des huit bit de poids fort de l'adresse EEPROM 
    EEADR=adressL; // r�cup�ration de la valeur des huit  bit de poids faible de l'adresse EEPROM 
    EECON1bits.RD=1; // autorisation de lecture
    while(EECON1bits.RD==1); // attente de la fin du processus de lecture
    unsigned char data = EEDATA; // r�cup�ration de la donn�e lue
    return data; // renvoie de la donn�e lue
}


void add_timer (char data_J, char adressH, char adressL) // incremente la memoire EEPROM avec la donn�e temps r�el
{
    unsigned char data_t=data_J+read_EEPROM(adressH, adressL); // somme de la donn�e a �crire et de la m�moire
    write_EEPROM(data_t,adressH, adressL); // �criture du r�sultat sur la case m�moire correspondante
}

void follow_driver_timer (void) // incr�mentation du temps d'utilisation d'un chauffeur
{
    unsigned char adresslow=conv_badge_8bitsl();
    unsigned char adresshigh=conv_badge_8bitsh();
    unsigned char temps_act_driver = Timer_G - temps_initial ;
    add_timer(temps_act_driver,adresslow,adresshigh);
}

char conv_badge_8bitsl (void) // r�cupere les huit bits de poids faible du badge conducteur
{
    unsigned badge_t=0;
    for (unsigned char i=0; i<8; i++)
    {
        badge_t=badge_t+badge[i]<<i;
    }
    return badge_t;
}

char conv_badge_8bitsh (void) // r�cupere les huit bits de poids fort du badge conducteur
{
    unsigned badge_t=0;
    for (unsigned char i=0; i<2; i++)
    {
        badge_t=badge_t+badge[i+8]<<i;
    }
    return badge_t;
}
        // Variable r�cup�ration variable timer
        // temps utilisation normale
        // temps utilisation anormale
        // temps de non utilisation
        // temps maintenance
        //temps utilisation conducteur N
        // temps utilisation anormale conducteur N
// envoie des informations sur demande avec condition d'acc�s
