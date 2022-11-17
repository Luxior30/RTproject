#include "T1.h"

void tache1()
{
    while(1)
    {
        vitesse = 0;
        if (VAR_TACHE1 == 0)
        {
          clear_text(); 
          LED_R=0;LED_G=1;LED_B=1;
          VAR_TACHE1 = 1;
        }
        LED_R=0;LED_G=1;LED_B=1;
        goto_lico(6,0);
        draw_string("Warning choc !!");
        goto_lico(7,0);
        draw_string("speed off");
        goto_lico(8,0);
        draw_string("for unlock push on 'choc'");
        if (CHOC == 1)
        {
            clear_text();
            LED_R=0;LED_G=0;LED_B=0;
            VAR_TACHE1 = 0;
        }  
    }
}