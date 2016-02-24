/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    setAnalogIn();
    setActuatorCntrl();
    unsigned int actuatorOnePos = 0;
    unsigned int desiredOnePos = 500;
    
    while(1)
    {
        //Start ADC reading
        ADCON0bits.GO_NOT_DONE = 1;
        
        //Wait for conversion to finish
        while (ADCON0bits.GO_NOT_DONE == 1);
        
        //Read ADC value from High/Low registers
        actuatorOnePos = ADRESL;
        actuatorOnePos += ADRESH << 8;
        
        if(actuatorOnePos < desiredOnePos)
        {
            //Extend
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 1;
        } else if(actuatorOnePos > desiredOnePos) {
            //Retract
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 0;
        } else {
            //No Motion
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
            
            //Reverse desired motion
            if(desiredOnePos == 500)
            {
                desiredOnePos = 400;
            } else {
                desiredOnePos = 500;
            }
        }
    }

}

