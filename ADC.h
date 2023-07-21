// File:   ADC.h
// Author: Johann Haeussler 21223
// 17.01.23


#ifndef ADC_H
#define	ADC_H

#include <xc.h>  
#include <stdint.h>
#include <proc/pic16f887.h>

void ADC_INIT(int c);   //canal inicial
int ADC_READ(); //leer ADRESH del canal 
void ADC_CHANGE_CHANNEL(int c,int b);//cambiar de canal
int ADC_GET_CHANNEL();//en que canal estamos

uint8_t DECENA(char c);
uint8_t UNIDAD(char c);

#endif	/* ADC_H */

