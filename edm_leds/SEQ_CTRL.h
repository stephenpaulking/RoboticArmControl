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
 * Status   : UNDER WORK                                                    *
 *                                                                          *
 * Author   : Stephen King                                                  *
 *                                                                          *
 * Team:    : Stephen King, Jack Bennett, Steven Mann & Diyana Shakur       *
 *                                                                          *
 *==========================================================================*/

#ifndef SEQ_CTRL_H
#define SEQ_CTRL_H

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

static unsigned int HorizontalCurrent;
static unsigned int ShoulderCurrent;
static unsigned int ElbowCurrent;
static unsigned int GripperCurrent;

/* Variables to hold Saved Values for Rejection */

static unsigned int HorizontalPrevious;
static unsigned int ShoulderPrevious;
static unsigned int ElbowPrevious;
static unsigned int GripperPrevious;

/* Array to hold PWM Storage */

static unsigned int PMWIndexStore[25];
static unsigned int PMWValueStore[25];

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

void SEQ_CTRL__Schedule(void);

#endif
