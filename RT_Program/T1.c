#include "T1.h"

void tache1()
{

    while(1)
    {
    unsigned char i;

    di();
    initialisation_des_ports();
    initialisation_afficheur();
    clear_text();
    clear_graphics();
    init_rxtx();
    Init(SEM_RXTX);
    RXTX_libre=1;
    TXREG1='R';
    ei();

    LED_R=0;LED_G=1;LED_B=1;

    vitesse=0;

    while(1)
    {
        goto_lico(6,0);
        draw_string("Warning choc !!");
        goto_lico(7,0);
        draw_string("speed off");
        goto_lico(8,0);
        draw_string("for unlock push on 'choc'");
    }
    
    }
}