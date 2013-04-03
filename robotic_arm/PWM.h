/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : PWM.h                                                         *
 *                                                                          *
 * Purpose  : PWM Header file for robotic arm project                       *
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

#ifndef __PWM_H
#define __PWM_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
  
/* Define for Default PWM VALUE */

#define     DEFAULT_PWM_VAL     0x1250

/* Defines for PWM Index Values */

#define     BASE_PWM        PWM1_0_BASE
#define     SHOULDER_PWM    PWM2_0_BASE
#define     ELBOW_PWM       PWM3_0_BASE
#define     GRIP_PWM        PWM4_0_BASE

/* Constants for Base PWM */
#define     BASE_INC        0x0001
#define     BASE_MAX        0x1800
#define     BASE_MIN        0xd2b

/* Constants for Shoulder PWM */
#define     SHOULDER_INC    0x0002
#define     SHOULDER_MIN    0xc31
#define     SHOULDER_MAX    0x1700

/* Constants for Elbow PWM */
#define     ELBOW_INC       0x0005
#define     ELBOW_MIN       0xc31
#define     ELBOW_MAX       0x189c

/* Constants for Grip PWM */
#define     GRIP_INC        0x0010
#define     GRIP_MIN        0xc31
#define     GRIP_MAX        0x1990

/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/
  
void PWM__Send ( const int PWMIndex, const int PWMValue );

void PWM__Reset ( void );

int PWM__Increment ( const int PWMIndex, const int InputValue );

int PWM__Decrement ( const int PWMIndex, const int InputValue );

#endif
