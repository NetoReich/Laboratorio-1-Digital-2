// File:   ADC.c
// Author: Johann Haeussler 21223
// 17.01.23


#include <stdint.h>
#include <xc.h>
#include "ADC.h"
#define _XTAL_FREQ  4000000

uint8_t DECENA(char c){         //Bits altos
    c = (uint8_t)(c % 16);
    return c;
}

uint8_t UNIDAD(char c){         //Bits bajos
    c = (uint8_t)((c/16) % 16);
    return c;
}

void ADC_INIT(int c){               //Canales
    switch(c){
        case 0:
            ADCON0bits.CHS3 = 0;    //0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 1:
            ADCON0bits.CHS3 = 0;    //1
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 2:
            ADCON0bits.CHS3 = 0;    //2
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 3:
            ADCON0bits.CHS3 = 0;    //3
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 4:
            ADCON0bits.CHS3 = 0;    //4
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 5:
            ADCON0bits.CHS3 = 0;    //5
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 6:
            ADCON0bits.CHS3 = 0;    //6
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 7:
            ADCON0bits.CHS3 = 0;    //7
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 8:
            ADCON0bits.CHS3 = 1;    //8
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 9:
            ADCON0bits.CHS3 = 1;    //9
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 10:
            ADCON0bits.CHS3 = 1;    //10
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 11:
            ADCON0bits.CHS3 = 1;    //11
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 1;
            ADCON0bits.CHS0 = 1;
            break;
            
        case 12:
            ADCON0bits.CHS3 = 1;    //12
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
            
        case 13:
            ADCON0bits.CHS3 = 1;    //13
            ADCON0bits.CHS2 = 1;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 1;
            break;
            
        default:
            ADCON0bits.CHS3 = 0;    //0
            ADCON0bits.CHS2 = 0;
            ADCON0bits.CHS1 = 0;
            ADCON0bits.CHS0 = 0;
            break;
    }
    return;
}
int ADC_READ() {
    ADCON0bits.GO = 1;              // Inicia la conversión ADC
    while(ADCON0bits.GO == 1) {
        // Espera hasta que el ADC complete la conversión
    }
    // La conversión ha terminado, devuelve el valor del resultado de la conversión
    return ADRESH;
}

void ADC_CHANGE_CHANNEL(int c, int b){      //Cambio de Canales
    ADCON0bits.GO = 1;                      
    while(ADCON0bits.GO == 1){
        if(ADCON0bits.GO == 0){
            if(ADCON0bits.CHS == c){
                ADCON0bits.CHS = b;   
            }else if(ADCON0bits.CHS == b){
                ADCON0bits.CHS = c;
            }
            ADCON0bits.GO = 1;
        }
    }
    return;
}

int ADC_GET_CHANNEL(){          // Canal actual
    return ADCON0bits.CHS;
}
