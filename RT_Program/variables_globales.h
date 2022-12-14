/* 
 * File:   variables_globales.h
 * Author: Franck
 *
 * Created on 29 janvier 2015, 09:59
 */

#ifndef VARIABLES_GLOBALES_H
#define	VARIABLES_GLOBALES_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
#include "systeme.h"

            /* Constantes */
#define     NOMBRE_DE_TACHES        6
#define     TACHE1                  1
#define     TACHE2                  2
#define     TACHE3                  3
#define     TACHE4                  4
#define     TACHE5                  5
#define     TACHE6                  6

/* Variables globales */
    // On stock dans la bank0 on laisse la zone access ram (00-5F) pour le compilateur
unsigned char W_TEMPORAIRE         @ 0x60;
unsigned char STATUS_TEMPORAIRE    @ 0x61;
unsigned char BSR_TEMPORAIRE       @ 0x62;
unsigned char FSR0H_TEMPORAIRE     @ 0x63;
unsigned char FSR0L_TEMPORAIRE     @ 0x64;
unsigned char DEMARRAGE            @ 0x65;

//Variables touch pad
unsigned char TP_appui             @ 0x66;
unsigned char TP_x                 @ 0x67;
unsigned char TP_y                 @ 0x68;

unsigned char queue[NOMBRE_DE_TACHES]        @ 0x69;
unsigned char tache_active         @ 0x6F;
unsigned char pointeur_de_tache    @ 0x70;
unsigned int Tick_Count            @ 0x71;
unsigned char vitesse              @ 0x73;
unsigned char batterie             @ 0x74;

unsigned char badge[10]            @ 0x75;
unsigned char n_octet_badge        @ 0x7F;

unsigned char RXTX_libre        @ 0x80;
unsigned char VAR_TACHE1        @ 0x370;

    //pointeur de fonction
        //il va servir a modifier la pile pour executer les taches
void (*fptr)(void);
unsigned short long val_tos;
unsigned char * puc;
unsigned char tc[3];


//Contexte = 18 registres SFR + 48 octet de 00h ? 2Fh = 66 octets
/* R?servation de la zone de 100h ? 142h pour le contexte de la tache 1 */
/* R?servation de la zone de 200h ? 242h pour le contexte de la tache 2 */
/* Ainsi de suite ...*/
/* Chaque contexte va utiliser 66 octets (0x42) au d?but de la banque correspondante */
unsigned char contexte1[66] @ 0x100;
unsigned char contexte2[66] @ 0x200;
unsigned char contexte3[66] @ 0x300;
unsigned char contexte4[66] @ 0x400;
unsigned char contexte5[66] @ 0x500;
unsigned char contexte6[66] @ 0x600;


unsigned char STKPTR_T1             @0x103;
unsigned char STKPTR_T2             @0x203;
unsigned char STKPTR_T3             @0x303;
unsigned char STKPTR_T4             @0x403;
unsigned char STKPTR_T5             @0x503;
unsigned char STKPTR_T6             @0x603;


unsigned long Timer_G @0x81 ;
unsigned char Timer_swap @0x85 ;
unsigned char timer_swap_tempon @0x86 ;

unsigned char tempon_presence_cle @0x87;
unsigned char temps_initial @0x88;
unsigned char temps_initial_warn @0x89;
unsigned char tempon_warnning @0x8A;
unsigned long test_EEPROM  @0x8B;
unsigned char temps_final @0x8F;
unsigned char tempon_anormal_use @0x90;
unsigned char tempon_unused @0x91;
unsigned char download @0x92;


#ifdef	__cplusplus
}
#endif

#endif	/* VARIABLES_GLOBALES_H */

