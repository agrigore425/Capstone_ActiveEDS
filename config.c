/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "config.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */
    OSCCONbits.IRCF2 = 1;       // All set -> 8 MHz
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;
    
    OSCCONbits.SCS1 = 0;        // All clear -> select primary oscillator
    OSCCONbits.SCS0 = 0;
    
    OSCTUNEbits.PLLEN = 1;      // Enable PLL x4
}

void enable_interrupts(void)
{
    /* Enable Interrupts */
    RCONbits.IPEN   = 0;    // Enable interrupt priority
    INTCONbits.GIE  = 1;    // Enable interrupts
    INTCONbits.PEIE = 1;    // Enable peripheral interrupts.
    
    //PIE1bits.RCIE   = 1;    // Enable USART receive interrupt
    PIE3bits.RXB0IE = 1;    // Enable CAN receive buffer 0 interrupt
    //PIE3bits.RXB1IE = 1;    // Enable CAN receive buffer 1 interrupt
}