// File:   PostLab1D2.c
// Author: Johann Haeussler 21223
// 17.01.23


#pragma config  FOSC    = INTRC_NOCLKOUT
#pragma config  WDTE    = OFF
#pragma config  PWRTE   = OFF
#pragma config  MCLRE   = OFF
#pragma config  CP      = OFF
#pragma config  CPD     = OFF
#pragma config  BOREN   = OFF
#pragma config  IESO    = OFF
#pragma config  FCMEN   = OFF
#pragma config  LVP     = OFF

#pragma config  BOR4V   = BOR40V
#pragma config  WRT     = OFF

#include <stdint.h>
#include <xc.h>
#include "ADC.h"
#include "PshButton.h"
#include "Temporizador.h"
#define _XTAL_FREQ  4000000
#define tmr0_value 244      //3ms

uint8_t unidad, decena;
uint8_t display, POT;

const char tabla[] =
{
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b01110111, // A
    0b01111100, // B
    0b00111001, // C
    0b01011110, // D
    0b01111001, // E
    0b01110001  // F

};
void setup(void);

void __interrupt() isr (void){
    
    if (RBIF==1){                       // Interrupción por cambio en el puerto B
        __delay_ms(10);
        if (RB0==0){                    // Si el botón en RB0 está presionado
            if (RB0==0){                // Verificar que el botón sigue presionado (anti-rebote)
                PORTA++;                // Incrementar el valor del puerto A
            }
        } else if (RB1==0){             // Si el botón en RB1 está presionado
            if (RB1==0){                // Verificar que el botón sigue presionado (anti-rebote)
                PORTA--;                // Decrementar el valor del puerto A
            }  
        }
        INTCONbits.RBIF=0;              // Limpiar la bandera de interrupción por cambio en el puerto B
    }
    else if(T0IF == 1){                 // Interrupción por desbordamiento del TMR0 (temporizador)   
        PORTD = 0x00;                   // Apagar todos los segmentos del display    
        
        if(display == 1){               // Mostrar la unidad
            RD0 = 1;                    // Encender el dígito correspondiente a la unidad
            PORTC = tabla[unidad];      // Mostrar el valor de la unidad en el display
                                    
        }else if(display == 2){         // Mostrar la decena
            RD1 = 1;                    // Encender el dígito correspondiente a la decena
            PORTC = tabla[decena];      // Mostrar el valor de la decena en el display
            
        }else if(display == 3){         // Cambiar de dígito
            display = 0;                // Reiniciar la variable para volver a mostrar la unidad en el siguiente ciclo
        }
        
        ++display;                      // Incrementar el contador de dígitos a mostrar
        INTCONbits.T0IF = 0;            // Limpiar la bandera de interrupción del TMR0
        TMR0 = tmr0_value;              // Reiniciar el contador del TMR0
    }
    return;
}

void main(void) {
    setup();                        // Llamar a la función de configuración
    while(1){
           
        POT = ADC_READ();           // Leer el valor analógico del potenciómetro
        
        decena = DECENA(POT);       // Obtener el valor de la decena del potenciómetro
        unidad = UNIDAD(POT);       // Obtener el valor de la unidad del potenciómetro
        
        RB7 = (POT > PORTA) ? 1:0;  // Si el valor del potenciómetro es mayor que el valor en el puerto A, establecer RB7 en 1, de lo contrario, establecerlo en 0
    }
}

void setup(void){
  // Configuración de los pines del microcontrolador   
    ANSEL = 0b00000010;     
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0b00000011;     
    TRISC = 0x00;
    TRISD = 0x00;

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    //oscilador a 4M Hz
    OSCILLATOR(2);
    
    //Configuración del oscilador a 4MHz
    PRESCALER_TMR0(7);              // Establecer el preescalador del TMR0 a 1:256
    TMR0 = tmr0_value;              // Inicializar el valor del TMR0
    
    //Config. PULL UP
    IOC_INT(0b00000011);            // Habilitar las interrupciones por cambio en RB0 y RB1
    
    //Config. ADC
    ADC_INIT(6);                    // Inicializar el módulo ADC con AN6 como entrada   
    
    ADCON1bits.VCFG0 = 0;           // Configurar la referencia de voltaje Vref- a Vss
    ADCON1bits.VCFG1 = 0;           // Configurar la referencia de voltaje Vref+ a Vdd
    
    ADCON0bits.ADCS0 = 0;           // Configurar el clock del ADC a Fosc/32
    ADCON0bits.ADCS1 = 1;

    ADCON1bits.ADFM =0;             // Justificar a la izquierda los bits del resultado del ADC
    
    ADCON0bits.ADON = 1;            // Encender el módulo ADC
    __delay_us(50);                 // Esperar un corto tiempo para que el módulo ADC se estabilice
    ADCON0bits.GO_nDONE = 1;        // Iniciar la conversión ADC
    
    //Config. interrupciones
    
    INTCONbits.GIE  = 1;        // Habilitar las interrupciones globales
    INTCONbits.RBIE = 1;        // Habilitar las interrupciones por cambio en RB0 y RB1
    INTCONbits.RBIF = 0;        // Limpiar la bandera de interrupción por cambio en RB0 y RB1
    INTCONbits.T0IF = 0;        // Limpiar la bandera de interrupción del TMR0
    INTCONbits.T0IE = 1;        // Habilitar las interrupciones del T

    unidad = 0;             
    decena = 0;
    display = 0;
    POT = 0;
    
    return;
}
