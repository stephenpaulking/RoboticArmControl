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

#include "system.h" 
#include "alt_types.h"
#include "altera_avalon_lcd_16207_regs.h"
#include "altera_avalon_lcd_16207.h" 
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/
  
#include "RAP.h"
#include "LCD.h"
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void LCD__Clear ( void )
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01);       /*Display Clear*/
    usleep(2000);                                               /* Short delay to take effect */
    return;
};

void LCD__Initialise ( void )
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30);       /* 8-bits,  */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x38);       /* 8-bits, 2 lines, 5x8 font */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x02);       /* Set the Cursor to the home position */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x08);       /* Turn Off LCD */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01);       /* Display Clear */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x06);       /* Set Entry Mode -- Cursor increment, display doesn't shift */
    usleep(2000);                                               /* Short delay to allow for setup */
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x0C);       /* Display on */
    usleep(2000);                                               /* Short delay to allow for setup */
    return;
};

void LCD__Write( const char * str )
{
    char * s_ptr = (char *) str;                                /* Assign string to char pointer */

    LCD__Clear();                                               /* Clear LCD */
    
    if ((str != NULL) && (*str != '\0'))                        /* Check if string is empty */
    {
        while (*s_ptr != '\0')                                  /* While current character is not empty */
        {
            if (*s_ptr == '\n')                                 /* Check for new line */
            {
                IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0xC0);   /* Go to new line on LCD */
            }
            else
            {
                IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_BASE, *s_ptr);    /* Write character to LCD */
            }

            usleep(2000);                                       /* Short delay to take effect */
            s_ptr++;                                            /* Increment string pointer to select next character */
        }
    }
    
    return;
};
