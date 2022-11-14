#include "T1.h"

void tache1()
{

    unsigned char i;

    di(); // Disable interrupt
    initialisation_des_ports();
    initialisation_afficheur();
    clear_text();
    clear_graphics();
    init_rxtx();
    Init(SEM_RXTX);
    RXTX_libre=1;
    TXREG1='R';
    ei(); // Enable interrupt
    

    LED_R=0;LED_G=0;LED_B=0;

    vitesse=0;
    batterie=120;
    n_octet_badge=0;

    goto_lico(13,34);draw_char('R');draw_char(' ');draw_char('V');draw_char(' ');draw_char('B');
    goto_lico(14,34);draw_char('0');draw_char(' ');draw_char('0');draw_char(' ');draw_char('0');
    goto_lico(15,34);draw_char('1');draw_char(' ');draw_char('1');draw_char(' ');draw_char('1');

    TP_appui=0;

    while(1)
    {
        if (CHOC == 0)
        {
            Timer_G_temp = Timer_G;
            while(CHOC==0);
            if(Timer_G - Timer_G_temp >= 10)
            {
                CHOC_LONG = 1;
            }
            else {
                CHOC_LONG = 0;
            }
        }
        
        /* //Gère le siège
        if((SIEGE == 1) && (CHOC == 0)) //Si user pas sur le siege et a un choc
        {
            LED_R=0; //Allume le rouge
            LED_G=1;
            LED_B=1;
            if (vitesse >= 0) //0% vitesse max
            {
               vitesse = 0; // 0% vitesse max
            }    
        }
        else if((SIEGE == 0) && (CHOC == 0)) //Si user sur le siege et a un choc
        {
                LED_R=0; //Allume le rouge
                LED_G=1;
                LED_B=1;
                if (vitesse >= 10) //4% vitesse max
                {
                   vitesse = 10; // 4% vitesse max
                }  
        }
        else if ((SIEGE == 1) && (CHOC == 1)) //Si user pas sur le siege et pas de choc
            {   
                LED_R=1; 
                LED_G=1;
                LED_B=0; //Allume le bleu
                if (vitesse >= 0) //0% vitesse max
                {
                   vitesse = 0; // 0% vitesse max
                }  
            }
        if ((SIEGE == 0) && (CHOC == 1)) //Si user pas sur le siege et pas de choc
        {
            LED_R=1;
            LED_G=1;
            LED_B=0;
            if (vitesse >= 200) //0% vitesse max
                {
                   vitesse = 200; // 0% vitesse max
                } 
        }  */

    //Gère marche avant / marche arrière
        /*if (MARCHE_AVANT == 0)
        {
            
        }*/
     
        goto_lico(1,0);
        draw_string("Siege:");
        if (SIEGE==0)
        {draw_char('1');}
        else
        {draw_char('0');}

        goto_lico(4,0);
        draw_string("Choc:");
        if (CHOC==0)
            draw_char('1');
        else
            draw_char('0');
        goto_lico(5,0);
        draw_string("Choc long:");
        if (CHOC_LONG==0)
            draw_char('1');
        else
            draw_char('0');

        goto_lico(6,0);
        draw_string("Vitesse:");
        if (VITESSE_PLUS==0)
            vitesse++;
        if (VITESSE_MOINS==0)
            vitesse--;
        draw_hex8(vitesse);
    }
}