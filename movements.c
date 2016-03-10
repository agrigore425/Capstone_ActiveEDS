


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
    /*
    if ((current_pos < set_point) && (*margin == 0))
    {
        move0 = 0; //needs to extend
        move1 = 1;
    } else if ((current_pos > set_point) && (*margin == 0))
    {
        move0 = 1; //needs to retract
        move1 = 0;
    } else if (current_pos == set_point && (*margin == 0)) {
        
        move0 = 0; //no motion
        move1 = 0;
        *margin = 1;
    }
    
    if (*margin) {
        move0 = 0;
        move1 = 0;
    }
    */
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
    } else if (actuator == 5)
    {
            LATCbits.LATC6 = move0;
            LATCbits.LATC7 = move1;
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
/*
void retract(unsigned int current_pos, unsigned int set_point, int actuator, bool *go)
{
    int test;
    bool move = false;
    if((test = current_pos - set_point > 30) || *go) //was sp - cp
    {
        move = true;
        if(current_pos <= set_point) *go = 0; //was >=
        else if(test) *go = 1;
    }
    
    if(actuator == 0)
    {
            LATCbits.LATC0 = move;
            LATCbits.LATC1 = 0;
    } else if (actuator == 1)
    {
            LATCbits.LATC2 = move;
            LATCbits.LATC3 = 0;
    } else if (actuator == 2)
    {   
            LATDbits.LATD0 = move;
            LATDbits.LATD1 = 0;
    } else if (actuator == 3)
    {
            LATDbits.LATD2 = move;
            LATDbits.LATD3 = 0;
    } else if (actuator == 4)
    {
            LATCbits.LATC4 = move;
            LATCbits.LATC5 = 0;
    } else if (actuator == 5)
    {
            LATCbits.LATC6 = move;
            LATCbits.LATC7 = 0;
    } else if (actuator == 6)
    {
            LATDbits.LATD4 = move;
            LATDbits.LATD5 = 0;
    } else if (actuator == 7)
    {
            LATDbits.LATD6 = move;
            LATDbits.LATD7 = 0;
    }
}
*/
void forward_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7)
{
    //Retract movements:
    //Actuator 0 = C0,C1 needs to retract
    if (actuator0 < retractPos)
    {
        LATCbits.LATC0 = 0; //needs to extend
        LATCbits.LATC1 = 1;
    } else if (actuator0 > retractPos)
    {
        LATCbits.LATC0 = 1; //needs to retract
        LATCbits.LATC1 = 0;
    } else {
        LATCbits.LATC0 = 0; //no motion
        LATCbits.LATC1 = 0;
    }

    //Actuator 1 = C2,C3 needs to extend
    if (actuator1 < extendPos)
    {
        LATCbits.LATC2 = 0; //needs to extend
        LATCbits.LATC3 = 1;
    } else if (actuator1 > extendPos)
    {
        LATCbits.LATC2 = 1; //needs to retract
        LATCbits.LATC3 = 0;
    } else {
        LATCbits.LATC2 = 0; //no motion
        LATCbits.LATC3 = 0;
    }

    //Actuator 2 = D0,D1 needs to retract
    if (actuator2 < retractPos)
    {
        LATDbits.LATD0 = 0; //needs to extend
        LATDbits.LATD1 = 1;
    } else if (actuator2 > retractPos)
    {
        LATDbits.LATD0 = 1; //needs to retract
        LATDbits.LATD1 = 0;
    } else {
        LATDbits.LATD0 = 0; //no motion
        LATDbits.LATD1 = 0;
    }

    //Actuator 3 = D2,D3 needs to extend
    if (actuator3 < extendPos)
    {
        LATDbits.LATD2 = 0; //needs to extend
        LATDbits.LATD3 = 1;
    } else if (actuator3 > extendPos)
    {
        LATDbits.LATD2 = 1; //needs to retract
        LATDbits.LATD3 = 0;
    } else {
        LATDbits.LATD2 = 0; //no motion
        LATDbits.LATD3 = 0;
    }

    //Actuator 4 = C4,C5 needs to extend
    if (actuator4 < extendPos)
    {
        LATCbits.LATC4 = 0; //needs to extend
        LATCbits.LATC5 = 1;
    } else if (actuator4 > extendPos)
    {
        LATCbits.LATC4 = 1; //needs to retract
        LATCbits.LATC5 = 0;
    } else {
        LATCbits.LATC4 = 0; //no motion
        LATCbits.LATC5 = 0;
    }

    //Actuator 5 = C6,C7 needs to retract
    if (actuator5 < retractPos)
    {
        LATCbits.LATC6 = 0; //needs to extend
        LATCbits.LATC7 = 1;
    } else if (actuator5 > retractPos)
    {
        LATCbits.LATC6 = 1; //needs to retract
        LATCbits.LATC7 = 0;
    } else {
        LATCbits.LATC6 = 0; //no motion
        LATCbits.LATC7 = 0;
    }

    //Actuator 6 = D4,D5 needs to extend
    if (actuator6 < extendPos)
    {
        LATDbits.LATD4 = 0; //needs to extend
        LATDbits.LATD5 = 1;
        
    } else if (actuator6 > extendPos)
    {
        LATDbits.LATD4 = 1; //needs to retract
        LATDbits.LATD5 = 0;
    } else {
        LATDbits.LATD4 = 0; //no motion
        LATDbits.LATD5 = 0;
    }

    //Actuator 7 = D6,D7 needs to retract
    if (actuator7 < retractPos)
    {
        LATDbits.LATD6 = 0; //needs to extend
        LATDbits.LATD7 = 1;
    } else if (actuator7 > retractPos)
    {
        LATDbits.LATD6 = 1; //needs to retract
        LATDbits.LATD7 = 0;
    } else {
        LATDbits.LATD6 = 0; //no motion
        LATDbits.LATD7 = 0;
    }
}

void backward_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7)
{
    //Retract movements:
    //Actuator 0 = C0,C1 needs to extend
    if (actuator0 < extendPos)
    {
        LATCbits.LATC0 = 0; //needs to extend
        LATCbits.LATC1 = 1;
    } else if (actuator0 > extendPos)
    {
        LATCbits.LATC0 = 1; //needs to retract
        LATCbits.LATC1 = 0;
    } else {
        LATCbits.LATC0 = 0; //no motion
        LATCbits.LATC1 = 0;
    }

    //Actuator 1 = C2,C3 needs to retract
    if (actuator1 < retractPos)
    {
        LATCbits.LATC2 = 0; //needs to extend
        LATCbits.LATC3 = 1;
    } else if (actuator1 > retractPos)
    {
        LATCbits.LATC2 = 1; //needs to retract
        LATCbits.LATC3 = 0;
    } else {
        LATCbits.LATC2 = 0; //no motion
        LATCbits.LATC3 = 0;
    }

    //Actuator 2 = D0,D1 needs to extend
    if (actuator2 < extendPos)
    {
        LATDbits.LATD0 = 0; //needs to extend
        LATDbits.LATD1 = 1;
    } else if (actuator2 > extendPos)
    {
        LATDbits.LATD0 = 1; //needs to retract
        LATDbits.LATD1 = 0;
    } else {
        LATDbits.LATD0 = 0; //no motion
        LATDbits.LATD1 = 0;
    }

    //Actuator 3 = D2,D3 needs to retract
    if (actuator3 < retractPos)
    {
        LATDbits.LATD2 = 0; //needs to extend
        LATDbits.LATD3 = 1;
    } else if (actuator3 > retractPos)
    {
        LATDbits.LATD2 = 1; //needs to retract
        LATDbits.LATD3 = 0;
    } else {
        LATDbits.LATD2 = 0; //no motion
        LATDbits.LATD3 = 0;
    }

    //Actuator 4 = C4,C5 needs to retract
    if (actuator4 < retractPos)
    {
        LATCbits.LATC4 = 0; //needs to extend
        LATCbits.LATC5 = 1;
    } else if (actuator4 > retractPos)
    {
        LATCbits.LATC4 = 1; //needs to retract
        LATCbits.LATC5 = 0;
    } else {
        LATCbits.LATC4 = 0; //no motion
        LATCbits.LATC5 = 0;
    }

    //Actuator 5 = C6,C7 needs to extend
    if (actuator5 < extendPos)
    {
        LATCbits.LATC6 = 0; //needs to extend
        LATCbits.LATC7 = 1;
    } else if (actuator5 > extendPos)
    {
        LATCbits.LATC6 = 1; //needs to retract
        LATCbits.LATC7 = 0;
    } else {
        LATCbits.LATC6 = 0; //no motion
        LATCbits.LATC7 = 0;
    }

    //Actuator 6 = D4,D5 needs to retract
    if (actuator6 < retractPos)
    {
        LATDbits.LATD4 = 0; //needs to extend
        LATDbits.LATD5 = 1;
    } else if (actuator6 > retractPos)
    {
        LATDbits.LATD4 = 1; //needs to retract
        LATDbits.LATD5 = 0;
    } else {
        LATDbits.LATD4 = 0; //no motion
        LATDbits.LATD5 = 0;
    }

    //Actuator 7 = D6,D7 needs to extend
    if (actuator7 < extendPos)
    {
        LATDbits.LATD6 = 0; //needs to extend
        LATDbits.LATD7 = 1;
    } else if (actuator7 > extendPos)
    {
        LATDbits.LATD6 = 1; //needs to retract
        LATDbits.LATD7 = 0;
    } else {
        LATDbits.LATD6 = 0; //no motion
        LATDbits.LATD7 = 0;
    }
}

void idle_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7)
{
    if (actuator0 < extendPos)
    {
        LATCbits.LATC0 = 0; //needs to extend
        LATCbits.LATC1 = 1;
    } else if (actuator0 > extendPos)
    {
        LATCbits.LATC0 = 1; //needs to retract
        LATCbits.LATC1 = 0;
    } else {
        LATCbits.LATC0 = 0; //no motion
        LATCbits.LATC1 = 0;
    }

    //Actuator 1 = C2,C3 needs to extend
    if (actuator1 < extendPos)
    {
        LATCbits.LATC2 = 0; //needs to extend
        LATCbits.LATC3 = 1;
    } else if (actuator1 > extendPos)
    {
        LATCbits.LATC2 = 1; //needs to retract
        LATCbits.LATC3 = 0;
    } else {
        LATCbits.LATC2 = 0; //no motion
        LATCbits.LATC3 = 0;
    }

    //Actuator 2 = D0,D1 needs to extend
    if (actuator2 < extendPos)
    {
        LATDbits.LATD0 = 0; //needs to extend
        LATDbits.LATD1 = 1;
    } else if (actuator2 > extendPos)
    {
        LATDbits.LATD0 = 1; //needs to retract
        LATDbits.LATD1 = 0;
    } else {
        LATDbits.LATD0 = 0; //no motion
        LATDbits.LATD1 = 0;
    }

    //Actuator 3 = D2,D3 needs to extend
    if (actuator3 < extendPos)
    {
        LATDbits.LATD2 = 0; //needs to extend
        LATDbits.LATD3 = 1;
    } else if (actuator3 > extendPos)
    {
        LATDbits.LATD2 = 1; //needs to retract
        LATDbits.LATD3 = 0;
    } else {
        LATDbits.LATD2 = 0; //no motion
        LATDbits.LATD3 = 0;
    }

    //Actuator 4 = C4,C5 needs to extend
    if (actuator4 < extendPos)
    {
        LATCbits.LATC4 = 0; //needs to extend
        LATCbits.LATC5 = 1;
    } else if (actuator4 > extendPos)
    {
        LATCbits.LATC4 = 1; //needs to retract
        LATCbits.LATC5 = 0;
    } else {
        LATCbits.LATC4 = 0; //no motion
        LATCbits.LATC5 = 0;
    }

    //Actuator 5 = C6,C7 needs to extend
    if (actuator5 < extendPos)
    {
        LATCbits.LATC6 = 0; //needs to extend
        LATCbits.LATC7 = 1;
    } else if (actuator5 > extendPos)
    {
        LATCbits.LATC6 = 1; //needs to retract
        LATCbits.LATC7 = 0;
    } else {
        LATCbits.LATC6 = 0; //no motion
        LATCbits.LATC7 = 0;
    }

    //Actuator 6 = D4,D5 needs to extend
    if (actuator6 < extendPos)
    {
        LATDbits.LATD4 = 0; //needs to extend
        LATDbits.LATD5 = 1;
    } else if (actuator6 > extendPos)
    {
        LATDbits.LATD4 = 1; //needs to retract
        LATDbits.LATD5 = 0;
    } else {
        LATDbits.LATD4 = 0; //no motion
        LATDbits.LATD5 = 0;
    }

    //Actuator 7 = D6,D7 needs to extend
    if (actuator7 < extendPos)
    {
        LATDbits.LATD6 = 0; //needs to extend
        LATDbits.LATD7 = 1;
    } else if (actuator7 > extendPos)
    {
        LATDbits.LATD6 = 1; //needs to retract
        LATDbits.LATD7 = 0;
    } else {
        LATDbits.LATD6 = 0; //no motion
        LATDbits.LATD7 = 0;
    }
}
/*
void speedControlForw4_6(unsigned int actuator4, unsigned int actuator6)
{
    // 4 moves slower than 6
    // Moving forward, 4 and 6 would extend
    if(actuator6 - actuator4 > 50)
    {
        
        //Pause actuator6
        LATDbits.LATD4 = 0; //no motion
        LATDbits.LATD5 = 0;

        //Allow actuator4 to catch up
    }
}
 */

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