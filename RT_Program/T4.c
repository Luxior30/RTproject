#include "T4.h"

void tache4()
{
    if ((tempon_presence_cle==0)&&(n_octet_badge!=0))
    {
        tempon_unused=0;
        follow_timer_unused;
        tempon_presence_cle==1; // mise a un de la variable indiquant la présence de cle
        temps_initial=Timer_G; // initialisation du compteur de temps
    }
    
    if ((tempon_presence_cle==1)&&(n_octet_badge==0))
    {        
        tempon_presence_cle==0; // mise a zero de la variable indiquant la présence de cle
        follow_driver_timer(); //incrementation des mémoires
        test_EEPROM=read_EEPROM(conv_badge_8bitsh,conv_badge_8bitsl);
        
    }
    
    if ((tempon_presence_cle==1)&&(SIEGE==0)&&(tempon_anormal_use==0))
    {
        temps_initial=Timer_G;
        tempon_anormal_use = 1;
    }
    
    if ((tempon_presence_cle==1)&&(SIEGE==1)&&(tempon_anormal_use==1))
    {
        temps_initial=Timer_G;
        tempon_anormal_use = 0;
        follow_driver_timer_anormal();
    }
    
    if ((tempon_presence_cle==0)&&(n_octet_badge==0)&&(tempon_unused==0))
    {
        temps_initial=Timer_G;
        tempon_unused=1;  
    }
    
}

void write_EEPROM (char data, char adressH, char adressL)
{
    EEADRH=adressH; // récupération de la valeur des huit bit de poids fort de l'adresse EEPROM 
    EEADR=adressL; // récupération de la valeur des huit  bit de poids faible de l'adresse EEPROM 
    EEDATA=data; // donnée à écrire
    EECON1bits.WREN=1; // autorisation de communiquer avec EEPROM
    INTCONbits.GIE=0; // interdiction d'utiliser des interruptions pendant l'écriture
    
    EECON2=0x55; // commande obligatoire
    EECON2=0xAA; //commande obligatoire
    EECON1bits.WR=1; // autorisation d'écriture
    while (EECON1bits.WR==1); // attente de la fin du processus d'écriture ; WR retourne automatiquement a 0 à la fin du processus
    
    INTCONbits.GIE=1; // Autorisation des interruptions
    EECON1bits.WREN=0; // fin de la communication avec EEPROM
}

char read_EEPROM (char adressH, char adressL)
{
    EEADRH=adressH; // récupération de la valeur des huit bit de poids fort de l'adresse EEPROM 
    EEADR=adressL; // récupération de la valeur des huit  bit de poids faible de l'adresse EEPROM 
    EECON1bits.RD=1; // autorisation de lecture
    while(EECON1bits.RD==1); // attente de la fin du processus de lecture
    unsigned char data = EEDATA; // récupération de la donnée lue
    return data; // renvoie de la donnée lue
}


unsigned char add_timer (char data_J, char adressH, char adressL, char type) // incremente la memoire EEPROM avec la donnée temps réel
{
    unsigned char reste = 0;
    unsigned int data_t=0;
    unsigned char mem_val=0;
    switch (type)
    {
        case type_heure :  //heure
            
                mem_val = read_EEPROM(adressH,adressL);
                data_t = (int)mem_val + data_J;
                if (data_t>255)
                {
                    unsigned reste = 1;
                    write_EEPROM(data_t-256,adressH,adressL);
                }
                else
                {
                    write_EEPROM(data_t,adressH,adressL);
                }
                break;
                 
        case type_minute ://min
                mem_val = read_EEPROM(adressH,adressL);
                 data_t = mem_val + data_J;
                if (data_t>59)
                {
                    reste = 1;
                    write_EEPROM(data_t-60,adressH,adressL);
                }
                else
                {
                    write_EEPROM(data_t,adressH,adressL);
                }
                break;
        default : 
            reste =0;
            break;
                
    }
                
     return reste;
    
}

void follow_driver_timer (void) // incrémentation du temps d'utilisation d'un chauffeur
{
    unsigned char adresslow=conv_badge_8bitsl();
    unsigned char adresshigh=conv_badge_8bitsh();
    unsigned int temps_act_driver = Timer_G - temps_initial ;
    unsigned int heure = temps_act_driver/360000;
    unsigned char heureh = heure>>8 & 0xFF;
    unsigned char heurel = heure & 0xFF;
    unsigned char min = (temps_act_driver-heure*360000)/60;
    unsigned char reste = add_timer(min,adresshigh,adresslow+2,1);
    reste=(heurel+reste,adresshigh,adresslow+1,0);
    reste=add_timer(heureh + reste,adresshigh,adresslow,0);
    
    
}

void follow_driver_timer_anormal (void)
{
  unsigned char adresslow=conv_badge_8bitsl();
    unsigned char adresshigh=conv_badge_8bitsh();
    unsigned int temps_act_driver = Timer_G - temps_initial ;
    unsigned int heure = temps_act_driver/360000;
    unsigned char heureh = heure>>8 & 0xFF;
    unsigned char heurel = heure & 0xFF;
    unsigned char min = (temps_act_driver-heure*360000)/60;
    unsigned char reste = add_timer(min,adresshigh,adresslow+6,1);
    reste=(heurel+reste,adresshigh,adresslow+5,0);
    reste=add_timer(heureh + reste,adresshigh,adresslow+4,0);
    }

void follow_timer_unused(void)
{
    unsigned int temps_act_driver = Timer_G - temps_initial ;
    unsigned int heure = temps_act_driver/360000;
    unsigned char heureh = heure>>8 & 0xFF;
    unsigned char heurel = heure & 0xFF;
    unsigned char min = (temps_act_driver-heure*360000)/60;
    unsigned char reste = add_timer(min,0x00,0x02,1);
    reste=(heurel+reste,0x00,0x01,0);
    reste=add_timer(heureh + reste,0x00,0x00,0);
    }

char conv_badge_8bitsl (void) // récupere les huit bits de poids faible du badge conducteur
{
    unsigned badge_t=0;
    for (unsigned char i=0; i<8; i++)
    {
        badge_t=badge_t+badge[i]<<i;
    }
    return badge_t;
}

char conv_badge_8bitsh (void) // récupere les huit bits de poids fort du badge conducteur
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
// envoie des informations sur demande avec0'accés
