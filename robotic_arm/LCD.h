/*==========================================================================*
 * C OBJECT HEADER                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : LCD.h                                                         *
 *                                                                          *
 * Purpose  : LCD Header file for robotic arm project                       *
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

#ifndef __LCD_H
#define __LCD_H

/*--------------------------------------------------------------------------*
 * Public Types :-                                                          *
 *--------------------------------------------------------------------------*/
 
/* None */
 
/*--------------------------------------------------------------------------*
 * Public Data :-                                                           *
 *--------------------------------------------------------------------------*/
  
/* None */
  
/*--------------------------------------------------------------------------*
 * Public Operations :-                                                     *
 *--------------------------------------------------------------------------*/
  
void LCD__Initialise ( void );

void LCD__Write ( const char * str );

void LCD__Clear ( void );

#endif
