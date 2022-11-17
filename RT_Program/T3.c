#include "T3.h"


void tache3()
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

    LED_R=0;LED_G=0;LED_B=0;

    vitesse=0;
    batterie=120;
    n_octet_badge=0;

    init_chRGB();

    TP_appui=0;

    while(1)
    {
        switch (screen)
        {
            case (main_screen):
                if (tempon_anormal_use==1)
                {
                    LED_R = 1;
                    LED_G=0;
                    LED_B=0;
                }
                goto_lico(0,0);
                draw_string("Marche:");
                if (MARCHE_AVANT==0)
                    draw_string("AV");
                else
                    if (MARCHE_ARRIERE==0)
                        draw_string("AR");
                    else
                        draw_string("N ");

                goto_lico(1,0);
                draw_string("Siege:");
                if (SIEGE==0)
                {draw_char('1');}
                else
                {draw_char('0');}

                goto_lico(2,0);
                draw_string("Temp. Eau:");
                draw_hex8(lecture_8bit_analogique(TEMPERATURE_EAU));

                goto_lico(3,0);
                draw_string("Temp. Huile:");
                draw_hex8(lecture_8bit_analogique(TEMPERATURE_HUILE));

                goto_lico(4,0);
                draw_string("Choc:");
                if (CHOC==0)
                    draw_char('1');
                else
                    draw_char('0');

                goto_lico(5,0);
                draw_string("Vitesse:");
                if (VITESSE_PLUS==0)
                    vitesse++;
                if (VITESSE_MOINS==0)
                    vitesse--;
               draw_hex8(vitesse);
               // draw_hex8(test_EEPROM); 

                goto_lico(6,0);
                draw_string("Batterie:");
                if (BATTERIE_PLUS==0)
                    batterie++;
                if (BATTERIE_MOINS==0)
                    batterie--;
                draw_hex8(batterie);

                goto_lico(7,0);
                if (FREIN_A_MAIN==0)
                    draw_string("((!))");
                else
                    draw_string("     ");

                goto_lico(8,0);
                draw_string("Badge:");
                if (n_octet_badge==0)
                    draw_string(" AUCUN              ");
                else
                {
                    for (i=0;i<n_octet_badge;i++)
                    {
                        draw_hex8(badge[i]);
                    }
                }

                goto_lico(9,0);
                draw_string("X-Joystick:");
                draw_hex8(lecture_8bit_analogique(JOYSTICK_X));


                goto_lico(10,0);
                draw_string("Y-Joystick:");
                draw_hex8(lecture_8bit_analogique(JOYSTICK_Y));

                goto_lico(5,20);
                draw_hex8(test_EEPROM);
                goto_lico(6,20);
                draw_hex8(temps_initial);
                goto_lico(7,20);
                draw_hex8(temps_final);
                
          
                
                if (TP_appui==1)
                {
                    goto_lico(0,20);
                    draw_string("x=");
                    draw_hex8(TP_x);
                    draw_string(" y=");
                    draw_hex8(TP_y);
                    plot1(TP_x,TP_y);
                }
                else
                {
                    Nop();
                }

                goto_lico(13,0);
                draw_string("-------------");
                goto_lico(14,0);
                draw_string("social data  |");
                goto_lico(15,13);
                draw_string("|");
                goto_lico(16,13);

                     if (TP_appui==1)
                    { 
                       if ((TP_x<0x50)&&(TP_y>0x60))
                       {
                       clear_text();    
                       screen=social_data_screen;
                       }
                    }  
                if (TP_appui==1)
        {
            if ((TP_x>=203)&&(TP_x<209))
            {
                if ((TP_y>=113)&&(TP_y<121))
                {
                    LED_R=1;
                }
                if ((TP_y>=121)&&(TP_y<127))
                {
                    LED_R=0;
                }
            }
        }
        if (TP_appui==1)
        {
            if ((TP_x>=215)&&(TP_x<221))
            {
                if ((TP_y>=113)&&(TP_y<121))
                {
                    LED_G=1;
                }
                if ((TP_y>=121)&&(TP_y<127))
                {
                    LED_G=0;
                }
            }
        }
        if (TP_appui==1)
        {
            if ((TP_x>=227)&&(TP_x<233))
            {
                if ((TP_y>=113)&&(TP_y<121))
                {
                    LED_B=1;
                }
                if ((TP_y>=121)&&(TP_y<127))
                {
                    LED_B=0;
                }
            }
        }
                
            break;
            case (social_data_screen):
                    goto_lico(0,0);
                    draw_string ("social datas");
                    goto_lico(2,0);
                    draw_string ("time unused ans power on");
                    goto_lico(3,0);
                    draw_hex8(read_EEPROM(0x00,0x01));
                    goto_lico(4,0);
                    draw_string("your time");
                    goto_lico(5,0);
                    draw_hex8(read_EEPROM(conv_badge_8bitsh(),conv_badge_8bitsl ()+1));
                    goto_lico(6,0);
                    draw_string("warning your anormal use");
                    goto_lico(7,0);
                    draw_hex8(read_EEPROM(conv_badge_8bitsh(),conv_badge_8bitsl ()+4));
                    
                    goto_lico(13,0);
                    draw_string("-------------");
                    goto_lico(14,0);
                    draw_string("main screen  |");
                    goto_lico(15,13);
                    draw_string("|");
                    goto_lico(13,14);
                    draw_string("-------------");
                    goto_lico(14,14);
                    draw_string("download     |");
                    goto_lico(15,27);
                    draw_string("|");
                    if (TP_appui==1)
                    { 
                       if ((TP_x<0x50)&&(TP_y>0x60))
                       {
                       clear_text();    
                       screen=0;
                       init_chRGB();
                       }
                       if((TP_y>0x60)&&((TP_x<100)&&(TP_x>50)))
                       {
                           download=1;
                       }
                    } 
                    
                    break; 
                
    }
           
         
           
        
    }
}

void init_chRGB (void)
{
    goto_lico(13,34);draw_char('R');draw_char(' ');draw_char('V');draw_char(' ');draw_char('B');
    goto_lico(14,34);draw_char('0');draw_char(' ');draw_char('0');draw_char(' ');draw_char('0');
    goto_lico(15,34);draw_char('1');draw_char(' ');draw_char('1');draw_char(' ');draw_char('1');
}