/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : SEQ_CTRL.h                                                   *
 *                                                                          *
 * Purpose  : SEQ_CTRL Header file for robotic arm project                 *
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

#ifndef __SEQ_CTRL_H
#define __SEQ_CTRL_H

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

/* Variable to hold the move status parameter */

static unsigned int MoveComplete;

/* Variable to hold the store status parameter */

static unsigned int StoreContinue;

/* Variable to hold the move counter */

static unsigned int MoveCount;
 
/* Variables to hold PWM Values */

static unsigned int BaseCurrent;
static unsigned int ShoulderCurrent;
static unsigned int ElbowCurrent;
static unsigned int GripCurrent;

/* Variables to hold Saved Values for Rejection */

static unsigned int BasePrevious;
static unsigned int ShoulderPrevious;
static unsigned int ElbowPrevious;
static unsigned int GripPrevious;

/* Array to hold PWM Storage */

static unsigned int PMWIndexStore[40];
static unsigned int PMWValueStore[40];
#define ARRAY_SIZE  40


/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/

void SEQ_CTRL__Schedule(void);

void SEQ_CTRL__SetSequence(void);

void SEQ_CTRL__BaseMove(void);

void SEQ_CTRL__ShoulderMove(void);

void SEQ_CTRL__ElbowMove(void);

void SEQ_CTRL__GripMove(void);

void SEQ_CTRL__Recall(void);

void SEQ_CTRL__Clear(void);

#endif
