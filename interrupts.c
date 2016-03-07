/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>
#include <stdio.h>
#include <pic18f4685.h>        /* For true/false definition */
#include <string.h> 

#include "can.h"
#include "interrupts.h"

char num;

// Main Interrupt Service Routine (ISR)
void interrupt ISR(void)
{
    if(PIR3bits.RXB0IF)
    {
        Message newMessage;
        ecan_receive_rxb0(&newMessage);
        ecan_rxb0_clear();          // Clear flag
        PIR3bits.RXB0IF = 0;
    }
    if(PIR3bits.RXB1IF)
    {
        Message newMessage;
        ecan_receive_rxb1(&newMessage);
        ecan_rxb1_clear();
        PIR3bits.RXB1IF = 0;
    }
}

