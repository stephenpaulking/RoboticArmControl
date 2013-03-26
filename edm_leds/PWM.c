/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : PWM.c                                                         *
 *                                                                          *
 * Purpose  : PWM C file for robotic arm project                            *
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
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/
  
#include "PWM.h"
#include "RAP.h"
#include "FREECTRL.h"
//#include "SEQ_CTRL.h"
  
/*--------------------------------------------------------------------------*
 * Private Data Types and Constants :-                                      *
 *--------------------------------------------------------------------------*/
  
/* None */ 
 
/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/
  
/* None */ 
 
/*--------------------------------------------------------------------------*
 * Private Function Prototypes :-                                           *
 *--------------------------------------------------------------------------*/
  
/* None */
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void PWM__Send ( const int PWMIndex , const int PWMValue )
{
    IOWR_ALTERA_AVALON_PIO_DATA(PWMIndex,PWMValue); //- Write to PWM
    usleep(5000);
    return;
};

void PWM__Reset ( void )
{
    IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,PWM_MID_DEFAULT);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,PWM_MID_DEFAULT);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,PWM_MID_DEFAULT);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,PWM_MID_DEFAULT);
    return;
};
