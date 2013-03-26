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
 * Status   : UNDER WORK                                                    *
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

//#include "FATAL_ERR.h"
  
  
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
    RAP__Initialise();
    
    RAP__Schedule();
    
//    fatal_error();              /* Execution will only reach here in error */
};

void RAP__Initialise (void)
{
    LCD__Write("Robotic Arm/nProject");
    usleep(10000);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,DEFAULT_PWM_VAL);
    usleep(10000);
    return;
};

void RAP__Schedule ( void )
{
    while(1)
    {
        ModeSelect = 0;
        RAP__DetermineMode();
        
        switch(ModeSelect)
        {
            case 1:
                FREECTRL__Schedule();
                break;
            case 2:
                SEQ_CTRL__Schedule();
                break;
            default:
                //Do Nothing
                break;
        }
    }
return;
};

void RAP__DetermineMode (void)
{
    LCD__Write("Select a Mode");
    usleep(5000);
    ModeSelect = 0;
    while(ModeSelect == 0)
    {
        SelectedKey = KEYP__GetState ();
        
        switch(SelectedKey)
        {
            case 0xFFFFFF86:
                usleep(1000);
                ModeSelect = 1;     /*Free Control Mode*/
                FREECTRL__Schedule();
                usleep(1000);
                break;
            case 0xFFFFFFCF:
                usleep(1000);
                ModeSelect = 2;     /*Record Sequence Mode*/
                SEQ_CTRL__Schedule();
                usleep(1000);
                break;
            default:
                usleep(1000);
                ModeSelect = 0;
                usleep(1000);
        }
    }
    usleep(10000);
    return;
};
