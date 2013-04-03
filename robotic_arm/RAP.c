/*==========================================================================*
 * C OBJECT OPERATION                                                       *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : RAP.c                                                         *
 *                                                                          *
 * Purpose  : RAP file for robotic arm project                              *
 *                                                                          *
 *--------------------------------------------------------------------------*
 * Copyright 2013 University of the West of England                         *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Status   : WRITTEN                                                    *
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
#include "altera_avalon_lcd_16207_regs.h"
#include "altera_avalon_lcd_16207.h" 

/*--------------------------------------------------------------------------*
 * Object Header Files :-                                                   *
 *--------------------------------------------------------------------------*/
  
#include "RAP.h"
#include "KEYP.h"
#include "LCD.h"
#include "PWM.h"
#include "FREECTRL.h"
#include "SEQ_CTRL.h"
#include "SEV_SEG.h"

#include "FATAL_ERR.h"
  
  
/*--------------------------------------------------------------------------*
 * Private Data Types and Constants :-                                      *
 *--------------------------------------------------------------------------*/
  
/* None */ 
 
/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/
  
 /* None */ 
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void RAP__main ( void )
{
    RAP__Initialise();              /* Intialise the Program */
    
    RAP__Schedule();                /* Enter main program */
    
    fatal_error();                  /* Execution will only reach here in error */
};

void RAP__Initialise (void)
{
    LCD__Initialise();                                              /* Initialise LCD Screen */
    LCD__Write("Robotic Arm\nProject");                             /* Write to LCD */
    SEV_SEG__Initialise();                                          /* Initialise Seven Segment Display */
    usleep(5000000);                                                /* Delay for 5 seconds */
    PWM__Reset();
    return;
};

void RAP__Schedule ( void )
{
    while(1)
    {
        if (MenuInit == 0)                                  /* Perform only on entry */
        {
            LCD__Write("Select a Mode\nFREE or SEQ");       /* Write to LCD */
            ModeSelect = 0;                                 /* Reset the mode select flag  */
            MenuInit = 1;
        }
        
        RAP__DetermineMode();                               /* Determine the selected mode */
        
        switch(ModeSelect)
        {
            case 1:
                FREECTRL__Schedule();                       /* Call Free Control Mode */
                MenuInit = 0;
                break;
            case 2:
                SEQ_CTRL__Schedule();                       /* Call Sequence Control Mode */
                MenuInit = 0;
                break;
            default:
                /* Do Nothing */
                break;
        }
    }
return;                                     /* Should not reach here */
};

void RAP__DetermineMode (void)
{
    
    SelectedKey = KEYP__GetState ();
        
    switch(SelectedKey)
    {
        case KEY_RIGHT:
            ModeSelect = 1;                 /*Free Control Mode*/
            break;
        case KEY_LEFT:
            ModeSelect = 2;                 /*Record Sequence Mode*/
            break;
        default:
            ModeSelect = 0;
    }
    
    return;
    
};
