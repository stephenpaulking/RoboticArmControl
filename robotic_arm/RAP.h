/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : RAP.h                                                         *
 *                                                                          *
 * Purpose  : RAP Header file for robotic arm project                       *
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

#ifndef __RAP_H
#define __RAP_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
  
/* Variable to hold the selected key on the keypad */

static int SelectedKey;

/* Variable to hold the selected mode */

static int ModeSelect;

/* Variable to hold the initialise flag */

static int MenuInit;
  
/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/
  
void RAP__main ( void );

void RAP__Schedule ( void );

void RAP__DetermineMode ( void );

void RAP__Initialise ( void ); 

#endif
