/*
 * File:   interrupt.c
 * Author: Alexandre
 *
 * Created on 15 novembre 2022, 13:11
 */


#include <xc.h>

void high_priority interrupt H_ISR()
{
	if (INTCON3bits.INT1IF == 1) 
	{ 
        debloquer_tache(char TACHE1)
    }
		INTCON3bits.INT1IF = 0; 
	}

