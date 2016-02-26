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

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */
typedef int bool;
#define true 1
#define false 0

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();


    
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
    
    bool FORW = false;
    bool BACK = false;
    bool done = true;
    
    unsigned int retract = 200;
    unsigned int extend = 800;
    while(1)
    {
        //READ ADCs---------------------------------------------------
        //CHANNEL 0 - Actuator 0/7
        //Start ADC reading Channel 0
        selectAN0();
        actuator0 = readADC();
        
        //CHANNEL 1 - Actuator 1/7
        //Start ADC reading Channel 1
        selectAN1();
        actuator1 = readADC();
        
        //CHANNEL 2 - Actuator 2/7
        //Start ADC reading Channel 2
        selectAN2();
        actuator2 = readADC();
        
        //CHANNEL 3 - Actuator 3/7
        //Start ADC reading Channel 3
        selectAN3();
        actuator3 = readADC();
        
        //CHANNEL 4 - Actuator 4/7
        //Start ADC reading Channel 4
        selectAN4();
        actuator4 = readADC();
        
        //CHANNEL 5 - Actuator 5/7
        //Start ADC reading Channel 5
        selectAN5();
        actuator5 = readADC();
        
        //CHANNEL 6 - Actuator 6/7
        //Start ADC reading Channel 6
        selectAN6();
        actuator6 = readADC();
        
        //CHANNEL 7 - Actuator 7/7
        //Start ADC reading Channel 7
        selectAN7();
        actuator7 = readADC();
        
        
        //RETRIEVE COMMAND FROM MAIN MC--------------------------------
        if(done == true) {
        /* CAN BUS RESETS the FORW and BACK booleans*/
        }
        
        //CHANGE ACTUATOR POSITION BASED ON MAIN MC COMMAND------------
        if(FORW == true && BACK == false)
        {
            //Check if done changing positions
            if ((actuator0 == actuator2 == actuator5 == actuator7 == retract) && 
                (actuator1 == actuator3 == actuator4 == actuator6 == extend))
            {
                    done = true;
            }
            else
            {
                done = false;
                //0,2,5,7 retract
                //1,3,4,6 extend/stay long

                /*Retract movements:*/
                //Actuator 0 = C0,C1 needs to retract
                if (actuator0 < retract)
                {
                    LATCbits.LATC0 = 0; //needs to extend
                    LATCbits.LATC1 = 1;
                } else if (actuator0 > retract)
                {
                    LATCbits.LATC0 = 1; //needs to retract
                    LATCbits.LATC1 = 0;
                } else {
                    LATCbits.LATC0 = 0; //no motion
                    LATCbits.LATC1 = 0;
                }

                //Actuator 1 = C2,C3 needs to extend
                if (actuator1 < extend)
                {
                    LATCbits.LATC2 = 0; //needs to extend
                    LATCbits.LATC3 = 1;
                } else if (actuator1 > extend)
                {
                    LATCbits.LATC2 = 1; //needs to retract
                    LATCbits.LATC3 = 0;
                } else {
                    LATCbits.LATC2 = 0; //no motion
                    LATCbits.LATC3 = 0;
                }

                //Actuator 2 = D0,D1 needs to retract
                if (actuator2 < retract)
                {
                    LATDbits.LATD0 = 0; //needs to extend
                    LATDbits.LATD1 = 1;
                } else if (actuator2 > retract)
                {
                    LATDbits.LATD0 = 1; //needs to retract
                    LATDbits.LATD1 = 0;
                } else {
                    LATDbits.LATD0 = 0; //no motion
                    LATDbits.LATD1 = 0;
                }

                //Actuator 3 = D2,D3 needs to extend
                if (actuator3 < extend)
                {
                    LATDbits.LATD2 = 0; //needs to extend
                    LATDbits.LATD3 = 1;
                } else if (actuator3 > extend)
                {
                    LATDbits.LATD2 = 1; //needs to retract
                    LATDbits.LATD3 = 0;
                } else {
                    LATDbits.LATD2 = 0; //no motion
                    LATDbits.LATD3 = 0;
                }

                //Actuator 4 = C4,C5 needs to extend
                if (actuator4 < extend)
                {
                    LATCbits.LATC4 = 0; //needs to extend
                    LATCbits.LATC5 = 1;
                } else if (actuator4 > extend)
                {
                    LATCbits.LATC4 = 1; //needs to retract
                    LATCbits.LATC5 = 0;
                } else {
                    LATCbits.LATC4 = 0; //no motion
                    LATCbits.LATC5 = 0;
                }

                //Actuator 5 = C6,C7 needs to retract
                if (actuator5 < retract)
                {
                    LATCbits.LATC6 = 0; //needs to extend
                    LATCbits.LATC7 = 1;
                } else if (actuator5 > retract)
                {
                    LATCbits.LATC6 = 1; //needs to retract
                    LATCbits.LATC7 = 0;
                } else {
                    LATCbits.LATC6 = 0; //no motion
                    LATCbits.LATC7 = 0;
                }

                //Actuator 6 = D4,D5 needs to extend
                if (actuator6 < extend)
                {
                    LATDbits.LATD4 = 0; //needs to extend
                    LATDbits.LATD5 = 1;
                } else if (actuator6 > extend)
                {
                    LATDbits.LATD4 = 1; //needs to retract
                    LATDbits.LATD5 = 0;
                } else {
                    LATDbits.LATD4 = 0; //no motion
                    LATDbits.LATD5 = 0;
                }

                //Actuator 7 = D6,D7 needs to retract
                if (actuator7 < retract)
                {
                    LATDbits.LATD6 = 0; //needs to extend
                    LATDbits.LATD7 = 1;
                } else if (actuator7 > retract)
                {
                    LATDbits.LATD6 = 1; //needs to retract
                    LATDbits.LATD7 = 0;
                } else {
                    LATDbits.LATD6 = 0; //no motion
                    LATDbits.LATD7 = 0;
                }
            }
            
        } else if(BACK == true && FORW == false) {
            //Check if done changing positions
            if ((actuator0 == actuator2 == actuator5 == actuator7 == extend) && 
                (actuator1 == actuator3 == actuator4 == actuator6 == retract))
            {
                done = true;
            }
            else
            {
                done = false;

                //0,2,5,7 extend/stay long
                //1,3,4,6 retract

                /*Retract movements:*/
                //Actuator 0 = C0,C1 needs to extend
                if (actuator0 < extend)
                {
                    LATCbits.LATC0 = 0; //needs to extend
                    LATCbits.LATC1 = 1;
                } else if (actuator0 > extend)
                {
                    LATCbits.LATC0 = 1; //needs to retract
                    LATCbits.LATC1 = 0;
                } else {
                    LATCbits.LATC0 = 0; //no motion
                    LATCbits.LATC1 = 0;
                }

                //Actuator 1 = C2,C3 needs to retract
                if (actuator1 < retract)
                {
                    LATCbits.LATC2 = 0; //needs to extend
                    LATCbits.LATC3 = 1;
                } else if (actuator1 > retract)
                {
                    LATCbits.LATC2 = 1; //needs to retract
                    LATCbits.LATC3 = 0;
                } else {
                    LATCbits.LATC2 = 0; //no motion
                    LATCbits.LATC3 = 0;
                }

                //Actuator 2 = D0,D1 needs to extend
                if (actuator2 < extend)
                {
                    LATDbits.LATD0 = 0; //needs to extend
                    LATDbits.LATD1 = 1;
                } else if (actuator2 > extend)
                {
                    LATDbits.LATD0 = 1; //needs to retract
                    LATDbits.LATD1 = 0;
                } else {
                    LATDbits.LATD0 = 0; //no motion
                    LATDbits.LATD1 = 0;
                }

                //Actuator 3 = D2,D3 needs to retract
                if (actuator3 < retract)
                {
                    LATDbits.LATD2 = 0; //needs to extend
                    LATDbits.LATD3 = 1;
                } else if (actuator3 > retract)
                {
                    LATDbits.LATD2 = 1; //needs to retract
                    LATDbits.LATD3 = 0;
                } else {
                    LATDbits.LATD2 = 0; //no motion
                    LATDbits.LATD3 = 0;
                }

                //Actuator 4 = C4,C5 needs to retract
                if (actuator4 < retract)
                {
                    LATCbits.LATC4 = 0; //needs to extend
                    LATCbits.LATC5 = 1;
                } else if (actuator4 > retract)
                {
                    LATCbits.LATC4 = 1; //needs to retract
                    LATCbits.LATC5 = 0;
                } else {
                    LATCbits.LATC4 = 0; //no motion
                    LATCbits.LATC5 = 0;
                }

                //Actuator 5 = C6,C7 needs to extend
                if (actuator5 < extend)
                {
                    LATCbits.LATC6 = 0; //needs to extend
                    LATCbits.LATC7 = 1;
                } else if (actuator5 > extend)
                {
                    LATCbits.LATC6 = 1; //needs to retract
                    LATCbits.LATC7 = 0;
                } else {
                    LATCbits.LATC6 = 0; //no motion
                    LATCbits.LATC7 = 0;
                }

                //Actuator 6 = D4,D5 needs to retract
                if (actuator6 < retract)
                {
                    LATDbits.LATD4 = 0; //needs to extend
                    LATDbits.LATD5 = 1;
                } else if (actuator6 > retract)
                {
                    LATDbits.LATD4 = 1; //needs to retract
                    LATDbits.LATD5 = 0;
                } else {
                    LATDbits.LATD4 = 0; //no motion
                    LATDbits.LATD5 = 0;
                }

                //Actuator 7 = D6,D7 needs to extend
                if (actuator7 < extend)
                {
                    LATDbits.LATD6 = 0; //needs to extend
                    LATDbits.LATD7 = 1;
                } else if (actuator7 > extend)
                {
                    LATDbits.LATD6 = 1; //needs to retract
                    LATDbits.LATD7 = 0;
                } else {
                    LATDbits.LATD6 = 0; //no motion
                    LATDbits.LATD7 = 0;
                }
            }
            
        } else {
            //ALL EXTENDED
            //Check if done changing positions
            if ((actuator0 == actuator2 == actuator5 == actuator7 == extend) && 
                (actuator1 == actuator3 == actuator4 == actuator6 == extend))
            {
                done = true;
            }
            //if not, correct the positions
            else
            {
                done = false;

                if (actuator0 < extend)
                {
                    LATCbits.LATC0 = 0; //needs to extend
                    LATCbits.LATC1 = 1;
                } else if (actuator0 > extend)
                {
                    LATCbits.LATC0 = 1; //needs to retract
                    LATCbits.LATC1 = 0;
                } else {
                    LATCbits.LATC0 = 0; //no motion
                    LATCbits.LATC1 = 0;
                }

                //Actuator 1 = C2,C3 needs to extend
                if (actuator1 < extend)
                {
                    LATCbits.LATC2 = 0; //needs to extend
                    LATCbits.LATC3 = 1;
                } else if (actuator1 > extend)
                {
                    LATCbits.LATC2 = 1; //needs to retract
                    LATCbits.LATC3 = 0;
                } else {
                    LATCbits.LATC2 = 0; //no motion
                    LATCbits.LATC3 = 0;
                }

                //Actuator 2 = D0,D1 needs to extend
                if (actuator2 < extend)
                {
                    LATDbits.LATD0 = 0; //needs to extend
                    LATDbits.LATD1 = 1;
                } else if (actuator2 > extend)
                {
                    LATDbits.LATD0 = 1; //needs to retract
                    LATDbits.LATD1 = 0;
                } else {
                    LATDbits.LATD0 = 0; //no motion
                    LATDbits.LATD1 = 0;
                }

                //Actuator 3 = D2,D3 needs to extend
                if (actuator3 < extend)
                {
                    LATDbits.LATD2 = 0; //needs to extend
                    LATDbits.LATD3 = 1;
                } else if (actuator3 > extend)
                {
                    LATDbits.LATD2 = 1; //needs to retract
                    LATDbits.LATD3 = 0;
                } else {
                    LATDbits.LATD2 = 0; //no motion
                    LATDbits.LATD3 = 0;
                }

                //Actuator 4 = C4,C5 needs to extend
                if (actuator4 < extend)
                {
                    LATCbits.LATC4 = 0; //needs to extend
                    LATCbits.LATC5 = 1;
                } else if (actuator4 > extend)
                {
                    LATCbits.LATC4 = 1; //needs to retract
                    LATCbits.LATC5 = 0;
                } else {
                    LATCbits.LATC4 = 0; //no motion
                    LATCbits.LATC5 = 0;
                }

                //Actuator 5 = C6,C7 needs to extend
                if (actuator5 < extend)
                {
                    LATCbits.LATC6 = 0; //needs to extend
                    LATCbits.LATC7 = 1;
                } else if (actuator5 > extend)
                {
                    LATCbits.LATC6 = 1; //needs to retract
                    LATCbits.LATC7 = 0;
                } else {
                    LATCbits.LATC6 = 0; //no motion
                    LATCbits.LATC7 = 0;
                }

                //Actuator 6 = D4,D5 needs to extend
                if (actuator6 < extend)
                {
                    LATDbits.LATD4 = 0; //needs to extend
                    LATDbits.LATD5 = 1;
                } else if (actuator6 > extend)
                {
                    LATDbits.LATD4 = 1; //needs to retract
                    LATDbits.LATD5 = 0;
                } else {
                    LATDbits.LATD4 = 0; //no motion
                    LATDbits.LATD5 = 0;
                }

                //Actuator 7 = D6,D7 needs to extend
                if (actuator7 < extend)
                {
                    LATDbits.LATD6 = 0; //needs to extend
                    LATDbits.LATD7 = 1;
                } else if (actuator7 > extend)
                {
                    LATDbits.LATD6 = 1; //needs to retract
                    LATDbits.LATD7 = 0;
                } else {
                    LATDbits.LATD6 = 0; //no motion
                    LATDbits.LATD7 = 0;
                }
            }
            
        }
    }

}

