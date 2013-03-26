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
#include <ctype.h>
#include <string.h>
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
#include "SEV_SEG.h"
#include "FREECTRL.h"
#include "SEQ_CTRL.h"
  
/*--------------------------------------------------------------------------*
 * Private Data Types and Constants :-                                      *
 *--------------------------------------------------------------------------*/
  
/* None */ 
 
/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/
  
static alt_u8 val_7seg[36];
 
/*--------------------------------------------------------------------------*
 * Private Function Prototypes :-                                           *
 *--------------------------------------------------------------------------*/
  
/* None */
 
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
    const int ClearValue = 0xFFFFFFFF;
    
    IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, ClearValue);
    
    return;
};

void SEV_SEG__Write( const char * str )
{
    SEV_SEG__Initialise();
    size_t length;
    char * outp_txt = (char *)str;
    int outp_bits = 0;
    int i;
    unsigned int cur_char, cur_val;
    
    if (str == NULL)
    {
        return;
    }
    
    SEV_SEG__Clear();
    
    length = strlen(str);
    if (length > 4)
    {
        length = 4;
    }
    
    for (i = 0; i < length; i++)
    {
        cur_char = (alt_u8)outp_txt[i];
        if (isdigit(cur_char))
        {
            cur_val = val_7seg[cur_char - '0'];
        }
        else
        {
            cur_char = toupper(cur_char);
            if ((cur_char >= 'A') && (cur_char < 'Z'))
            {
                cur_val = val_7seg[10 + cur_char - 'A'];
            }
            else if (cur_char == ' ')
            {
                cur_val = 0xFF;
            }
            else
            {
               return;
            }
        }
        
        outp_bits <<= 8;
        outp_bits |= cur_val;
    }
    
    /* Pad the rest of the display with empty characters */

    if (length < 4)
    {
        for (i = length; i < 4; i++)
        {
            outp_bits <<= 8;
            outp_bits |= 0xFF;
        }
    }

    IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, outp_bits);
    
    return;
};
