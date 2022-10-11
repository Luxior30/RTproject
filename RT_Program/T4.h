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
    void tache4();
    char read_EEPROM(char adressH, char adressL);
    void write_EEPROM(char data, char adressH, char adressL);
    void add_timer (char data_J, char adressH, char adressL);
    void follow_driver_timer (void);
    char conv_badge_8bitsl (void);
    char conv_badge_8bitsh (void);
#ifdef	__cplusplus
}
#endif

#endif	/* T4_H */

