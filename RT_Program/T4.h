/* 
 * File:   T4.h
 * Author: Franck
 *
 * Created on 29 janvier 2015, 11:46
 */

#ifndef T4_H
#define	T4_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"
    
    
#define type_heure 0
#define type_minute 1
    
    
    
    void tache4();
    char read_EEPROM(char adressH, char adressL);
    void write_EEPROM(char data, char adressH, char adressL);
    unsigned char add_timer (char data_J, char adressH, char adressL,char type);
    void follow_driver_timer (void);
    char conv_badge_8bitsl (void);
    char conv_badge_8bitsh (void);
    void follow_driver_timer_anormal (void);
    void follow_timer_unused(void);
#ifdef	__cplusplus
}
#endif

#endif	/* T4_H */

