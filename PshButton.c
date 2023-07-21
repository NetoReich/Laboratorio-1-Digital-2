// File:   PshButton.c
// Author: Johann Haeussler 21223
// 17.01.23

#include <stdint.h>
#include <xc.h>
#include "PshButton.h"

void IOC_INT(uint8_t a){        
    
    //Config. PULL UP
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB = a;
    IOCBbits.IOCB = a;         
    
}
