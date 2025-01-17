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
#include "ADC_Config.h"    /* ADC Channel selects and read function */
#include "interrupts.h"
#include "config.h"
#include "can.h"
#include "movements.h"
#include "uart.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */
typedef int bool;
#define true 1
#define false 0


bool FORW = false;
bool BACK = false;
bool EXTEND = false;
bool RETRACT = false;
bool CUSTOM = false;

int margin0 = 0;
int margin1 = 0;
int margin2 = 0;
int margin3 = 0;
int margin4 = 0;
int margin5 = 0;
int margin6 = 0;
int margin7 = 0;
    
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    ecan_init();
    uart_init(9600);
    //enable_interrupts();
        
    setAnalogIn();
    setActuatorCntrl();
    unsigned int actuator0 = 0;
    unsigned int actuator1 = 0;
    unsigned int actuator2 = 0;
    unsigned int actuator3 = 0;
    unsigned int actuator4 = 0;
    unsigned int actuator5 = 0;
    unsigned int actuator6 = 0;
    unsigned int actuator7 = 0;
    
    LATAbits.LATA7 = 1; 
    
    unsigned int retractPos = 0;
    unsigned int extendPos = 400;
    
    unsigned int newPos = 0;
    //char positions[10] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450};
    

    while(1)
    {

        /*
        //CAN MESSAGE SET UP
        if(RXB0CONbits.RXB0FUL)
        {
            Message newMessage;
            ecan_receive_rxb0(&newMessage);

            margin0 = 0;
            margin1 = 0;
            margin2 = 0;
            margin3 = 0;
            margin4 = 0;
            margin5 = 0;
            margin6 = 0;
            margin7 = 0;

            LATAbits.LATA7 ^= 1; 

        
            //Message parsing:
            //EXTEND = 0, FORW = 1, BACK = 2, RETRACT = 3
            //Extend
            if (newMessage.data[0] == 0x00)
            {
                FORW = false;
                BACK = false;
                EXTEND = true;
                RETRACT = false;
            }
            //Forward
            if (newMessage.data[0] == 0x01)
            {
                FORW = true;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
            }
            //Backward
            if (newMessage.data[0] == 0x02)
            {
                FORW = false;
                BACK = true;
                EXTEND = false;
                RETRACT = false;
            }
            // Retract
            if (newMessage.data[0] == 0x03)
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = true;
            }
            

            ecan_rxb0_clear();          // Clear flag
        }
        */
        
        
        if(uart_data_ready())
        {
            char message = uart_read();
            
            margin0 = 0;
            margin1 = 0;
            margin2 = 0;
            margin3 = 0;
            margin4 = 0;
            margin5 = 0;
            margin6 = 0;
            margin7 = 0;
            
            LATAbits.LATA7 ^= 1; 
            
            if (message == 'e')
            {
                FORW = false;
                BACK = false;
                EXTEND = true;
                RETRACT = false;
                CUSTOM = false;
                uart_write_text("Command Sent (Array Extended)\r\n");
            }
            else if (message == 'r')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = true;
                CUSTOM = false;
                uart_write_text("Command Sent (Array Retracted)\r\n");
            }
            else if (message == 'f')
            {
                FORW = true;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = false;
                uart_write_text("Command Sent (Array Forward)\r\n");
            }
            else if (message == 'b')
            {
                FORW = false;
                BACK = true;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = false;
                uart_write_text("Command Sent (Array Backward)\r\n");
            }
            else if (message == '0')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[0];
                newPos = 0;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '1')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[1];
                newPos = 50;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '2')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[2];
                newPos = 100;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '3')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[3];
                newPos = 150;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '4')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[4];
                newPos = 200;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '5')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[5];
                newPos = 250;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '6')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[6];
                newPos = 300;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '7')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[7];
                newPos = 350;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '8')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[8];
                newPos = 400;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
            else if (message == '9')
            {
                FORW = false;
                BACK = false;
                EXTEND = false;
                RETRACT = false;
                CUSTOM = true;
                //newPos = positions[9];
                newPos = 450;
                uart_write_text("Command Sent (Array Custom)\r\n");
            }
        }
        
        
        //READ ADCs---------------------------------------------------
        //CHANNEL 0 - Actuator 0/7
        if(margin0 == 0){
            //Start ADC reading Channel 0
            selectAN0();
            actuator0 = readADC();
        }
        if(margin1 == 0){
            //CHANNEL 1 - Actuator 1/7
            //Start ADC reading Channel 1
            selectAN1();
            actuator1 = readADC();
        }
        if(margin2 == 0){
            //CHANNEL 2 - Actuator 2/7
            //Start ADC reading Channel 2
            selectAN2();
            actuator2 = readADC();
        }
        if(margin3 == 0){
            //CHANNEL 3 - Actuator 3/7
            //Start ADC reading Channel 3
            selectAN3();
            actuator3 = readADC();
        }
        
        if(margin4 == 0){
            //CHANNEL 4 - Actuator 4/7
            //Start ADC reading Channel 4
            selectAN4();
            actuator4 = readADC();
        }
        if(margin5 == 0){
            //CHANNEL 5 - Actuator 5/7
            //Start ADC reading Channel 5
            selectAN5();
            actuator5 = readADC();
        }
        
        if(margin6 == 0){
            //CHANNEL 6 - Actuator 6/7
            //Start ADC reading Channel 6
            selectAN6();
            actuator6 = readADC();
        }
        if(margin7 == 0){
            //CHANNEL 7 - Actuator 7/7
            //Start ADC reading Channel 7
            selectAN7();
            actuator7 = readADC();
        }
        
        //CHANGE ACTUATOR POSITION BASED ON MAIN MC COMMAND------------
        if(FORW == true && BACK == false && EXTEND == false && RETRACT == false)
        {
            //0,2,5,7 retract
            //1,3,4,6 extend/stay long
            
            //testALLON();
            
            // Speed Check Example (actuatorSlow, actuatorFast, set point, &marginSlow, &marginFast);
            //speedCheck(actuator3, actuator1, extendPos, &margin3, &margin1);
            //speedCheck(actuator4, actuator6, extendPos, &margin4, &margin6);
            //speedCheck(actuator4, actuator1, extendPos, &margin4, &margin1);
            //speedCheck(actuator0, actuator2, retractPos, &margin0, &margin2);
            //speedCheck(actuator3, actuator6, extendPos, &margin3, &margin6);
            
            movement(actuator0, retractPos, 0, &margin0);
            movement(actuator1, extendPos, 1, &margin1);
            movement(actuator2, retractPos, 2, &margin2);
            movement(actuator3, extendPos, 3, &margin3);
            movement(actuator4, extendPos, 4, &margin4);
            movement(actuator5, retractPos, 5, &margin5);
            movement(actuator6, extendPos, 6, &margin6);
            movement(actuator7, retractPos, 7, &margin7); 
            
 
        } else if(BACK == true && FORW == false && EXTEND == false && RETRACT == false) {
            //0,2,5,7 extend/stay long
            //1,3,4,6 retract
            //testALLOFF();
                        
            //speedCheck(actuator3, actuator1, extendPos, &margin3, &margin1);
            //speedCheck(actuator4, actuator6, extendPos, &margin4, &margin6);
            
            movement(actuator0, extendPos, 0, &margin0);
            movement(actuator1, retractPos, 1, &margin1);
            movement(actuator2, extendPos, 2, &margin2);
            movement(actuator3, retractPos, 3, &margin3);
            movement(actuator4, retractPos, 4, &margin4);
            movement(actuator5, extendPos, 5, &margin5);
            movement(actuator6, retractPos, 6, &margin6);
            movement(actuator7, extendPos, 7, &margin7);
            
            
        } else if (FORW == false && BACK == false && EXTEND == true && RETRACT == false){
            
            //speedCheck4and6(actuator4, actuator6, extendPos, &margin4, &margin6);
            //testEveryOther();

            movement(actuator0, extendPos, 0, &margin0);
            movement(actuator1, extendPos, 1, &margin1);
            movement(actuator2, extendPos, 2, &margin2);
            movement(actuator3, extendPos, 3, &margin3);
            movement(actuator4, extendPos, 4, &margin4);
            movement(actuator5, extendPos, 5, &margin5);
            movement(actuator6, extendPos, 6, &margin6);
            movement(actuator7, extendPos, 7, &margin7);
            
        } else if (FORW == false && BACK == false && EXTEND == false && RETRACT == false && CUSTOM == true){
            
            //speedCheck4and6(actuator4, actuator6, extendPos, &margin4, &margin6);
            //testEveryOther();

            movement(actuator0, newPos, 0, &margin0);
            movement(actuator1, newPos, 1, &margin1);
            movement(actuator2, newPos, 2, &margin2);
            movement(actuator3, newPos, 3, &margin3);
            movement(actuator4, newPos, 4, &margin4);
            movement(actuator5, newPos, 5, &margin5);
            movement(actuator6, newPos, 6, &margin6);
            movement(actuator7, newPos, 7, &margin7);
            
              
        } else {
            //testEveryOther();
            
            movement(actuator0, retractPos, 0, &margin0);
            movement(actuator1, retractPos, 1, &margin1);
            movement(actuator2, retractPos, 2, &margin2);
            movement(actuator3, retractPos, 3, &margin3);
            movement(actuator4, retractPos, 4, &margin4);
            movement(actuator5, retractPos, 5, &margin5);
            movement(actuator6, retractPos, 6, &margin6);
            movement(actuator7, retractPos, 7, &margin7);
            
        }
    }
}


/*
// Main Interrupt Service Routine (ISR)
void interrupt ISR(void)
{
    if(PIR3bits.RXB0IF)
    {
        resetMargins();
        LATAbits.LATA7 ^= 1; 
        Message newMessage;
        ecan_receive_rxb0(&newMessage);
        
        
        
        //Message parsing:
        //IDLE = 0, FORW = 1, BACK = 2
        
        if (newMessage.data[0] == 0x00)
        {
            FORW = false;
            BACK = false;
        }
        if (newMessage.data[0] == 0x01)
        {
            FORW = true;
            BACK = false;
        }
        if (newMessage.data[0] == 0x02)
        {
            FORW = false;
            BACK = true;
        }
        
        ecan_rxb0_clear();          // Clear flag
        PIR3bits.RXB0IF = 0;
    }
    
}*/

