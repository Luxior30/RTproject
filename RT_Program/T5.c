#include "T5.h"

void tache5()
{
    unsigned int a;
    while(1)
    {
        if (download==1)
        {
        for (int i=0; i<1024 ; i++)
        {
            unsigned char ADRESSH= i>>8 & 0xFF;
            unsigned char ADRESSL = i & 0xFF;
            while(PIR1bits.TX1IF==0); TXREG1=read_EEPROM(ADRESSH,ADRESSL); while (TXSTA1bits.TRMT==0);
            write_EEPROM(0x00,ADRESSH,ADRESSL);
            if (i==1023) download==0;
        }
        }
    }
    
        
        
       /* //P(SEM_RXTX);
        //while(RXTX_libre==0);
        //RXTX_libre=0;
        while (PIR1bits.TX1IF==0);   TXREG1='t';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='a';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='c';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='h';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='e';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='5';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='_';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='e';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='n';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='_';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='c';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='o';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='u';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='r';while (TXSTA1bits.TRMT==0);
        while (PIR1bits.TX1IF==0);   TXREG1='s';while (TXSTA1bits.TRMT==0);
        //RXTX_libre=1;
        //V(SEM_RXTX);*/
        for (a=0;a<65000;a++)
            ;
        for (a=0;a<65000;a++)
            ;
    }
