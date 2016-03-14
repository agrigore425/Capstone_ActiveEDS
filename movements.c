


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
#include <math.h>

#endif

typedef int bool;
#define true 1
#define false 0

unsigned int retractPos = 200;
unsigned int extendPos = 800;

void movement(unsigned int current_pos, unsigned int set_point, int actuator, int *margin)
{
    int move0;
    int move1;
    
    if(*margin == 0)
    {
       if (current_pos < set_point)
        {
            move0 = 0; //needs to extend
            move1 = 1;
        } else if (current_pos > set_point)
        {
            move0 = 1; //needs to retract
            move1 = 0;
        } else 
        {
            move0 = 0; //no motion
            move1 = 0;
            *margin = 1;
        } 
    } else 
    {
        move0 = 0;
        move1 = 0;
    }
    
    if(actuator == 0)
    {
            LATCbits.LATC0 = move0;
            LATCbits.LATC1 = move1;
    } else if (actuator == 1)
    {
            LATCbits.LATC2 = move0;
            LATCbits.LATC3 = move1;
    } else if (actuator == 2)
    {   
            LATDbits.LATD0 = move0;
            LATDbits.LATD1 = move1;
    } else if (actuator == 3)
    {
            LATDbits.LATD2 = move0;
            LATDbits.LATD3 = move1;
    } else if (actuator == 4)
    {
            LATCbits.LATC4 = move0;
            LATCbits.LATC5 = move1;
    } else if (actuator == 5)           // Actuator 5 digital pins reconfigured for UART
    {
            LATBbits.LATB0 = move0;
            LATBbits.LATB1 = move1;
    } else if (actuator == 6)
    {
            LATDbits.LATD4 = move0;
            LATDbits.LATD5 = move1;
    } else if (actuator == 7)
    {
            LATDbits.LATD6 = move0;
            LATDbits.LATD7 = move1;
    }
    
}


void testEveryOther()
{
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 1;
    LATCbits.LATC3 = 0;
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 1;
    LATDbits.LATD3 = 0;
    LATCbits.LATC4 = 1;
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 1;
    LATCbits.LATC7 = 0;
    LATDbits.LATD4 = 1;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;
    LATDbits.LATD7 = 0;
}
void testALLON()
{
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 1;
    LATCbits.LATC2 = 1;
    LATCbits.LATC3 = 1;
    LATDbits.LATD0 = 1;
    LATDbits.LATD1 = 1;
    LATDbits.LATD2 = 1;
    LATDbits.LATD3 = 1;
    LATCbits.LATC4 = 1;
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 1;
    LATCbits.LATC7 = 1;
    LATDbits.LATD4 = 1;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;
    LATDbits.LATD7 = 1;
}
void testALLOFF()
{
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;
    LATCbits.LATC3 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
    LATDbits.LATD3 = 0;
    LATCbits.LATC4 = 0;
    LATCbits.LATC5 = 0;
    LATCbits.LATC6 = 0;
    LATCbits.LATC7 = 0;
    LATDbits.LATD4 = 0;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;
    LATDbits.LATD7 = 0;
}


void speedCheck(unsigned int actuatorSlow, unsigned int actuatorFast,
                     unsigned int set_point, int *marginSlow, int *marginFast)
{
    if(set_point == extendPos)
    {
        if((actuatorFast - actuatorSlow) == 10)
        {
           *marginFast = 1;
           *marginSlow = 0;
        }
        if ((actuatorSlow - actuatorFast) == 10)
        {
           *marginFast = 0;
           *marginSlow = 1;
        }
    } else if(set_point == retractPos)
    {
        if((actuatorFast - actuatorSlow) == -10)
        {
           *marginFast = 1;
           *marginSlow = 0;
        }
        if ((actuatorSlow - actuatorFast) == -10)
        {
           *marginFast = 0;
           *marginSlow = 1;
        }
    }

}