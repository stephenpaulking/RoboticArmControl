/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : KEYP.h                                                        *
 *                                                                          *
 * Purpose  : KEYP Header file for robotic arm project                      *
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

#ifndef __KEYP_H
#define __KEYP_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
  
/* Defines for each key on the keypad */

#define     KEY_0       0xFFFFFFC0
#define     KEY_1       0xFFFFFFCF
#define     KEY_2       0xFFFFFFA4
#define     KEY_3       0xFFFFFFB0
#define     KEY_4       0xFFFFFF99
#define     KEY_5       0xFFFFFF92
#define     KEY_6       0xFFFFFF82
#define     KEY_7       0xFFFFFFF8
#define     KEY_8       0xFFFFFF80
#define     KEY_9       0xFFFFFF90
#define     KEY_A       0xFFFFFF88
#define     KEY_B       0xFFFFFF83
#define     KEY_C       0xFFFFFFF0
#define     KEY_D       0xFFFFFFA1
#define     KEY_LEFT    0xFFFFFF86
#define     KEY_RIGHT   0xFFFFFF8E
  
/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/
  
int KEYP__GetState ( void );

#endif
