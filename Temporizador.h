// File: Temporizador.h
// Author: Johann Haeussler 21223
// 17.01.23


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef Temporizador_H
#define	Temporizador_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void OSCILLATOR(uint8_t c);
void PRESCALER_TMR0(int c);

#endif	/* Temporizador_H */

