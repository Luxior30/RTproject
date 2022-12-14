/* 
 * File:   semaphore.h
 * Author: Franck
 *
 * Created on 9 f?vrier 2015, 16:58
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "main.h"

// Liste des semaphores
    #define     SEM_CAN     1
    #define     SEM_RXTX    2

// Variables globales semaphores
    unsigned char Val_sem_cna;
    unsigned char Val_sem_rxtx;

    // Prototypes
    void Init(unsigned char sem);
    void P(unsigned char sem);
    void V(unsigned char sem);


#ifdef	__cplusplus
}
#endif

#endif	/* SEMAPHORE_H */

