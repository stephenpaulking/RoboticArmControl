/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : FREECTRL.c                                                    *
 *                                                                          *
 * Purpose  : Free Control Mode C file for robotic arm project to enable    *
 *            manual control of all functions of the robotic arm            *
 *                                                                          *
 *--------------------------------------------------------------------------*
 * Copyright 2013 University of the West of England                         *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Status   : WRITTEN                                                       *
 *                                                                          *
 * Author   : Stephen King                                                  *
 *                                                                          *
 * Team:    : Stephen King, Jack Bennett, Steven Mann & Diyana Shakur       *
 *                                                                          *
 *==========================================================================*/

/*--------------------------------------------------------------------------*
 * System Wide Header Files :-                                              *
 *--------------------------------------------------------------------------*/
 
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h> 
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/

#include "RAP.h"
#include "FREECTRL.h"
#include "KEYP.h"
#include "LCD.h"
#include "PWM.h"
#include "SEV_SEG.h"
 
/*---------------------------------------------------------------------------------------------------------------------------------------*
 * Operation Code :-                                                                                                                     *
 *---------------------------------------------------------------------------------------------------------------------------------------*/
  
void FREECTRL__Schedule( void )
{
    BaseCurrent       =   DEFAULT_PWM_VAL;                                      /* PWM1 - LEFT/RIGHT - Initialise Values */
    ShoulderCurrent   =   DEFAULT_PWM_VAL;                                      /* PWM2 - TOP ARM - Initialise Values */
    ElbowCurrent      =   DEFAULT_PWM_VAL;                                      /* PWM3 - BOTTOM ARM - Initialise Values */
    GripCurrent       =   DEFAULT_PWM_VAL;                                      /* PWM4 - GRIPPER - Initialise Values */
    
    ModeContinue = 1;                                                           /* Set internal exit flag*/

    LCD__Write("FreeControl Mode\nPlease Wait");                                /* Write string to the LCD */
    
    SEV_SEG__Write("FREE");                                                     /* Write string to the Seven Segment Display*/
    
    usleep(3000000);                                                            /* Delay for 3 seconds */    
    
    PWM__Reset();
      
    LCD__Write("FreeControl Mode\nPress Any Key");                              /* Write string to the LCD */
    
    while(ModeContinue == 1)                                                    /*While internal continue flag is set*/
    {
        KeySelected = KEYP__GetState();                                         /*Get the state of the keypad and return key press if any*/
        
        switch (KeySelected)                                                    /*Initialise a case when a certain key is pressed*/
        {
            case KEY_4:                                                         /* Left Key */
                BaseCurrent = PWM__Decrement(BASE_PWM,BaseCurrent);
                break;   
            case KEY_6:                                                         /* Right Key */
                BaseCurrent = PWM__Increment(BASE_PWM,BaseCurrent);
                break;
            case KEY_8:                                                         /* Shoulder Up Key */
                ShoulderCurrent = PWM__Decrement(SHOULDER_PWM,ShoulderCurrent);
                break;   
            case KEY_2:                                                         /* Shoulder Down Key */
                ShoulderCurrent = PWM__Increment(SHOULDER_PWM,ShoulderCurrent);
                break; 
            case KEY_7:                                                         /* Elbow Up Key */
                ElbowCurrent = PWM__Decrement(ELBOW_PWM,ElbowCurrent);
                break;   
            case KEY_1:                                                         /* Elbow Down Key */
                ElbowCurrent = PWM__Increment(ELBOW_PWM,ElbowCurrent);
                break;
            case KEY_9:                                                         /* Open Key */
                GripCurrent = PWM__Decrement(GRIP_PWM,GripCurrent);
                break;   
            case KEY_3:                                                         /* Close Key */
                GripCurrent = PWM__Increment(GRIP_PWM,GripCurrent);
                break;
            case KEY_0:                                                         /* Exit Key */
                ModeContinue = 0;                                               /* Reset mode continue flag */
                break;   
            default:
                usleep(1000);                                                   /*Do nothing*/
        }
    }    
return;

};
