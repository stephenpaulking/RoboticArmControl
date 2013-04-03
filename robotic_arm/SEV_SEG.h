/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : SEV_SEG.h                                                     *
 *                                                                          *
 * Purpose  : SEV_SEG Header file for robotic arm project                   *
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

#ifndef __SEV_SEG_H
#define __SEV_SEG_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
 
/* Numeric output values */
#define NUM_ZERO        0xC0
#define NUM_ONE         0xF9
#define NUM_TWO         0xA4
#define NUM_THREE       0xB0
#define NUM_FOUR        0x99
#define NUM_FIVE        0x92
#define NUM_SIX         0x82
#define NUM_SEVEN       0xF8
#define NUM_EIGHT       0x80
#define NUM_NINE        0x90

/* Alphabetical character output values */
#define ALPH_A          0x88
#define ALPH_B          0x83
#define ALPH_C          0xC6
#define ALPH_D          0xA1
#define ALPH_E          0x86
#define ALPH_F          0x8E
#define ALPH_G          0x90
#define ALPH_H          0x8B
#define ALPH_I          0xF9
#define ALPH_J          0xF1
#define ALPH_K          0x89
#define ALPH_L          0xC7
#define ALPH_M          0xAA
#define ALPH_N          0xAB
#define ALPH_O          0xC0
#define ALPH_P          0x8C
#define ALPH_Q          0x98
#define ALPH_R          0xAF
#define ALPH_S          0x92
#define ALPH_T          0x87
#define ALPH_U          0xE3
#define ALPH_V          0xC1
#define ALPH_W          0x95
#define ALPH_X          0xD6
#define ALPH_Y          0x91
#define ALPH_Z          0xA4

/* Seven Segment Size */
#define SEG_LENGTH      4
  
/* Seven Segment Size */
#define CLEAR_VALUE     0xFFFFFFFF
  
/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/

/* Initialise the 7 segment display */

void SEV_SEG__Initialise ( void );

/* Clear the 7 segment display */

void SEV_SEG__Clear ( void );

/* Write to the 7 segment display */

void SEV_SEG__Write ( const char * str );


#endif /*_SEV_SEG_H_*/
