/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : LCD.c                                                         *
 *                                                                          *
 * Purpose  : LCD C file for robotic arm project                            *
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
  
#include "RAP.h"
#include "LCD.h"
#include "FREECTRL.h"
#include "SEQ_CTRL.h"
  
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
  
void LCD__Clear ( void )
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01); /*Display Clear*/
    usleep(10000);
    return;
};

void LCD__Initialise ( void )
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits,  */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits, */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits,  */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x38); /* 8-bits, 2 lines, 5x8 font */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x02); /* Set the Cursor to the home position */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x08); /* Turn Off LCD */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01); /* Display Clear */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x06); /* Set Entry Mode -- Cursor increment, display doesn't shift */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x0C); /* Display on */
    usleep(41000);
    return;
};

void LCD__Write( const char * str )
{
    char * s_ptr = (char *) str;

    LCD__Clear();
    
    if ((str != NULL) && (*str != '\0'))
    {
        while (*s_ptr != '\0')
        {
            if (*s_ptr == '\n')
            {
                IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0xC0);
            }
            else
            {
                IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_BASE, *s_ptr);
            }

            usleep(1000);
            s_ptr++;
        }
    }
    
    return;
};
