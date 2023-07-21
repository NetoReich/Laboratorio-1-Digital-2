// File:   Temporizador.c
// Author: Johann Haeussler 21223
// 17.01.23


#include <stdint.h>
#include <xc.h>
#include "Temporizador.h"
#define _XTAL_FREQ  4000000

void OSCILLATOR(uint8_t c){         //Escogo que frecuencia quiero para el oscilador
    OSCCONbits.SCS   =1;
    
    switch(c){
        case(1):
            OSCCONbits.IRCF2 =1;        //8M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =1;
            break;
            
        case(2):
            OSCCONbits.IRCF2 =1;        //4M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
            
        case(3):
            OSCCONbits.IRCF2 =1;        //2M Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =1;
            break;
            
        case(4):
            OSCCONbits.IRCF2 =1;        //1M Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =0;
            break;
            
        case(5):
            OSCCONbits.IRCF2 =0;        //500k Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =1;
            break;
        
        case(6):
            OSCCONbits.IRCF2 =0;        //250k Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
        
        case(7):
            OSCCONbits.IRCF2 =0;        //125k Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =1;
            break;
        
        case(8):
            OSCCONbits.IRCF2 =0;        //31k Hz    
            OSCCONbits.IRCF1 =0;
            OSCCONbits.IRCF0 =0;
            break;
        
        default:
            OSCCONbits.IRCF2 =1;        //4M Hz    
            OSCCONbits.IRCF1 =1;
            OSCCONbits.IRCF0 =0;
            break;
    }
    
    
}

void PRESCALER_TMR0(int c){         //prescaler del TMR0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    
    switch(c){
        case(0):
            OPTION_REGbits.PS2 = 0;     //1:2
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 0;
            break;
            
        case(1):
            OPTION_REGbits.PS2 = 0;     //1:4
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 1;
            break;
            
        case(2):
            OPTION_REGbits.PS2 = 0;     //1:8
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 0;
            break;
        
        case(3):
            OPTION_REGbits.PS2 = 0;     //1:16
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
            break;
            
            
        case(4):
            OPTION_REGbits.PS2 = 1;     //1:32
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 0;
            break;
            
        case(5):
            OPTION_REGbits.PS2 = 1;     //1:64
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS0 = 1;
            break;
            
        case(6):
            OPTION_REGbits.PS2 = 1;     //1:128
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 0;
            break;
            
        case(7):
            OPTION_REGbits.PS2 = 1;     //1:256
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
            break;
            
        default:
            OPTION_REGbits.PS2 = 1;     //1:256
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS0 = 1;
            break;
    }
}
