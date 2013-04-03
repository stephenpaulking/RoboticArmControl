/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : SEV_SEG.c                                                     *
 *                                                                          *
 * Purpose  : SEV_SEG C file for robotic arm project                        *
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
#include "system.h"
#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/
  
#include "RAP.h"
#include "SEV_SEG.h"
 
/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/

/* Array for Seven Segment lookup table */
  
static alt_u8 val_7seg[36];

/* Variables to hold Current variables for writing to 7 Seg */

unsigned int CurrentChar;
unsigned int CurrentValue;

/* Variable to hold output for writing to 7 Seg */

int SegOutput;

/* Variable to hold length flag */
int LengthFlag;

/* Variable to hold counter to use for statements */
int Counter;
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/

/* Initialise the lookup table for the 7 Segment display */

void SEV_SEG__Initialise(void)
{
    val_7seg[0]  = NUM_ZERO;
    val_7seg[1]  = NUM_ONE;
    val_7seg[2]  = NUM_TWO;
    val_7seg[3]  = NUM_THREE;
    val_7seg[4]  = NUM_FOUR;
    val_7seg[5]  = NUM_FIVE;
    val_7seg[6]  = NUM_SIX;
    val_7seg[7]  = NUM_SEVEN;
    val_7seg[8]  = NUM_EIGHT;
    val_7seg[9]  = NUM_NINE;
        
    val_7seg[10] = ALPH_A;
    val_7seg[11] = ALPH_B;
    val_7seg[12] = ALPH_C;
    val_7seg[13] = ALPH_D;
    val_7seg[14] = ALPH_E;
    val_7seg[15] = ALPH_F;
    val_7seg[16] = ALPH_G;
    val_7seg[17] = ALPH_H;
    val_7seg[18] = ALPH_I;
    val_7seg[19] = ALPH_J;
    val_7seg[20] = ALPH_K;
    val_7seg[21] = ALPH_L;
    val_7seg[22] = ALPH_M;
    val_7seg[23] = ALPH_N;
    val_7seg[24] = ALPH_O;
    val_7seg[25] = ALPH_P;
    val_7seg[26] = ALPH_Q;
    val_7seg[27] = ALPH_R;
    val_7seg[28] = ALPH_S;
    val_7seg[29] = ALPH_T;
    val_7seg[30] = ALPH_U;
    val_7seg[31] = ALPH_V;
    val_7seg[32] = ALPH_W;
    val_7seg[33] = ALPH_X;
    val_7seg[34] = ALPH_Y;
    val_7seg[35] = ALPH_Z;
    
    return;
}
  
void SEV_SEG__Clear ( void )
{
    IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, CLEAR_VALUE); /* Clear Seven Segment Display */
    
    return;
};

void SEV_SEG__Write( const char * str )
{
    SegOutput = 0;
    
    char * OutputText = (char *)str;                            /* Set character pointer to string */
    
    SEV_SEG__Clear();                                           /* Clear Seven Segment Display */
    
    if (str == NULL)                                            /* Check if string is empty */
    {
        return;
    }
    
    for (Counter = 0; Counter < SEG_LENGTH; Counter++)          /* Process each character to assign value */
    {
        CurrentChar = OutputText[Counter];
        
        if (isdigit(CurrentChar))                                   /* Check whether character is numerical */
        {
            CurrentValue = val_7seg[CurrentChar - '0'];
        }
        else
        {
            CurrentChar = toupper(CurrentChar);
            if ((CurrentChar >= 'A') && (CurrentChar < 'Z'))        /* Check whether character is alphanumerical */
            {
                CurrentValue = val_7seg[10 + CurrentChar - 'A'];
            }
            else if (CurrentChar == ' ')                            /* Check whether character is empty */
            {
                CurrentValue = 0xFF;
            }
            else
            {
               return;
            }
        }
        
        SegOutput <<= 8;
        SegOutput |= CurrentValue;
    }

    IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, SegOutput);      /* Send to seven segment display */
    
    return;
};
