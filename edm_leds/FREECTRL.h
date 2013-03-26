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
 * Status   : UNDER WORK                                                    *
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

static unsigned int HorizontalValue;
static unsigned int ShoulderValue;
static unsigned int ElbowValue;
static unsigned int GripperValue;

/* Constants for Horizontal PWM */
#define HORIZONTAL_INC  0x000A
#define HORIZONTAL_MAX  0x1800
#define HORIZONTAL_MIN  0xd2b

/* Constants for Shoulder PWM */
#define SHOULDER_INC    0x000A
#define SHOULDER_MAX    0xc31
#define SHOULDER_MIN    0x1700

/* Constants for Elbow PWM */
#define ELBOW_INC       0x000D
#define ELBOW_MAX       0xc31
#define ELBOW_MIN       0x189c

/* Constants for Gripper PWM */
#define GRIP_INC        0x0050
#define GRIP_MAX        0xc31
#define GRIP_MIN        0x1990

/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/

void FREECTRL__Schedule(void);

#endif
