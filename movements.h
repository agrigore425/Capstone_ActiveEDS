/* 
 * File:   movements.h
 * Author: agrigore
 *
 * Created on March 9, 2016, 11:38 AM
 */
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

void forward_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7);

void backward_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7);

void idle_movements(unsigned int actuator0, unsigned int actuator1, 
                       unsigned int actuator2, unsigned int actuator3,
                       unsigned int actuator4, unsigned int actuator5,
                       unsigned int actuator6, unsigned int actuator7);

//void speedControlForw4_6(unsigned int actuator4, unsigned int actuator6);

void movement(unsigned int current_pos, unsigned int set_point, int actuator, int *margin);
//void retract(unsigned int current_pos, unsigned int set_point, int actuator, bool *go);

void speedCheck(unsigned int actuator4, unsigned int actuator6, unsigned int set_point,
                int *margin4, int *margin6);

void testEveryOther();
void testALLON();
void testALLOFF();


/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */