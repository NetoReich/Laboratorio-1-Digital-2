// File:   PshButton.h
// Author: Johann Haeussler 21223
// 17.01.23


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PshButton_H
#define	PshButton_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void IOC_INT(uint8_t a);

#endif	/* PshButton_H */
