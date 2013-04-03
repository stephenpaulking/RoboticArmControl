/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : FREECTRL.h                                                   *
 *                                                                          *
 * Purpose  : FREECTRL Header file for robotic arm project                 *
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

#ifndef FREECTRL_H
#define FREECTRL_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
  
/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/
  
/* Variable to hold the selected key on the keypad */

static unsigned int KeySelected;

/* Variable to hold the entry parameter */

static unsigned int ModeContinue;
 
/* Variables to hold PWM Values */

static unsigned int BaseCurrent;
static unsigned int ShoulderCurrent;
static unsigned int ElbowCurrent;
static unsigned int GripCurrent;

/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/

void FREECTRL__Schedule(void);

#endif
