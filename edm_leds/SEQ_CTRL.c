/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : SEQ_CTRL.c                                                   *
 *                                                                          *
 * Purpose  : SEQ_CTRL C file for robotic arm project                      *
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
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include "altera_avalon_lcd_16207_regs.h"
#include "altera_avalon_lcd_16207.h" 
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/

#include "SEQ_CTRL.h"
#include "RAP.h"
#include "KEYP.h"
#include "LCD.h"
#include "PWM.h"

//#include "FATAL_ERR.h"
  
/*--------------------------------------------------------------------------*
 * Private Data Types and Constants :-                                      *
 *--------------------------------------------------------------------------*/
  
/* None */ 
 
/*--------------------------------------------------------------------------*
 * Private Function Prototypes :-                                           *
 *--------------------------------------------------------------------------*/

/* None */
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void SEQ_CTRL__Schedule( void )
{
    usleep(10000);
    ModeContinue = 0;
    HorizontalCurrent =   0x1250; //PWM1 - LEFT/RIGHT
    ShoulderCurrent   =   0x1250; //PWM2 - TOP ARM
    ElbowCurrent      =   0x1250; //PWM3 - BOTTOM ARM
    GripperCurrent    =   0x1250; //PWM4 - GRIPPER
    PWM__Reset();
      
    LCD__Write("Store Sequence");
    usleep(50000);
    while(ModeContinue == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case 0xFFFFFF99:        /*Left Key (4 Key)*/
            case 0xFFFFFF82:        /*Right Key (6 Key)*/
                SEQ_CTRL__HorizontalMove();
                break;
            case 0xFFFFFF80:        /*Shoulder Up Key (8 Key)*/
            case 0xFFFFFFA4:        /*Shoulder Down Key (2 Key)*/
                SEQ_CTRL__ShoulderMove();
                break;
            case 0xFFFFFFF8:        /*Elbow Up Key (7 Key)*/
            case 0xFFFFFFCF:        /*Elbow Down Key (1 Key)*/
                //SEQ_CTRL__ElbowMove();
                break;
            case 0xFFFFFF90:        /*Open Key (9 Key)*/
            case 0xFFFFFFB0:        /*Close Key (3 Key)*/
                //SEQ_CTRL__GripperMove();
                break;
            case 0xFFFFFF88:        /*Recall Sequence Key (A Key)*/
                //SEQ_CTRL__RecallSequence();
                break;  
            case 0xFFFFFF83:        /*Clear Sequence Key (B Key)*/
                //SEQ_CTRL__ClearSequence();
                break; 
            case 0xFFFFFFC0:        /*Exit Key (0 Key)*/
                ModeContinue = 1;
                break;  
            default:
                //Do nothing
                usleep(10000);
        };
    };
    return;
};

void SEQ_CTRL__HorizontalMove( void )
{
    MoveComplete = 0;
    LCD__Write("Horizontal Move\nPress 4 or 6");
    usleep(10000);
    LCD__Write("A-To Accept Move\nB-To Reject Move")
    usleep(4000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        switch (KeySelected)
        {
            case 0xFFFFFF99:                                                    /*Left Key (4 Key)*/
                if (HorizontalCurrent <= HORIZONTAL_MIN)                        /*Assess value of horizontal value against the minimum*/
                {
                    HorizontalCurrent = HORIZONTAL_MIN;                         /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    HorizontalCurrent = (HorizontalCurrent - HORIZONTAL_INC);   /*Decrement value of horizontal value by set increment*/
                }
                break;
            case 0xFFFFFF82:                                                    /*Right Key (6 Key)*/
                if (HorizontalCurrent >= HORIZONTAL_MAX)                        /*Assess value of horizontal value against the maximum*/
                {
                    HorizontalCurrent = HORIZONTAL_MAX;                         /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    HorizontalCurrent = (HorizontalCurrent + HORIZONTAL_INC);   /*Increment value of horizontal value by set increment*/
                }
                break;
            case 0xFFFFFF88:                                                    /*Accept Move Key (A Key)*/
                MoveCount++;
                PMWIndexStore[MoveCount] = PWM1_0_BASE;
                PMWValueStore[MoveCount] = HorizontalCurrent;
                MoveComplete = 1;
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (A Key)*/
                HorizontalCurrent = HorizontalPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
    }
    HorizontalPrevious = HorizontalCurrent;
    return;
};

void SEQ_CTRL__ ShoulderMove( void )
{
    MoveComplete = 0;
    LCD__Write("Shoulder Move\nPress 8 or 2");
    usleep(10000);
    LCD__Write("A-To Accept Move\nB-To Reject Move")
    usleep(4000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case 0xFFFFFF80:                                                    /*Shoulder Up Key (8 Key)*/
                if (ShoulderCurrent <= SHOULDER_MAX)                            /*Assess value of horizontal value against the maximum*/
                {
                    ShoulderCurrent = SHOULDER_MAX;                             /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    ShoulderCurrent = (ShoulderCurrent - SHOULDER_INC);         /*Decrement value of shoulder value by set increment*/
                }
                break;   
            case 0xFFFFFFA4:                                                    /*Shoulder Down Key (2 Key)*/
                if (ShoulderCurrent >= SHOULDER_MIN)                            /*Assess value of shoulder value against the minimum*/
                {
                    ShoulderCurrent = SHOULDER_MIN;                             /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    ShoulderCurrent = (ShoulderCurrent + SHOULDER_INC);         /*Increment value of shoulder value by set increment*/
                }
                break;
            case 0xFFFFFF88:                                                    /*Accept Move Key (A Key)*/
                MoveCount++;
                PMWIndexStore[MoveCount] = PWM2_0_BASE;
                PMWValueStore[MoveCount] = ShoulderCurrent;
                MoveComplete = 1;
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                ShoulderCurrent = ShoulderPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
    }
    ShoulderPrevious = ShoulderCurrent;
    return;
};

void SEQ_CTRL__ ElbowMove( void )
{
    MoveComplete = 0;
    LCD__Write("Elbow Move\nPress 7 or 1");
    usleep(10000);
    LCD__Write("A-To Accept Move\nB-To Reject Move")
    usleep(4000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case 0xFFFFFFF8:                                                    /*Elbow Up Key (7 Key)*/
                if (ElbowCurrent <= ELBOW_MAX)                                  /*Assess value of elbow value against the maximum*/
                {
                    ElbowCurrent = ELBOW_MAX;                                   /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    ElbowCurrent = (ElbowCurrent - ELBOW_INC);                  /*Decrement value of elbow value by set increment*/
                }
                break;   
            case 0xFFFFFFCF:                                                    /*Elbow Down Key (1 Key)*/
                if (ElbowCurrent >= ELBOW_MIN)                                  /*Assess value of elbow value against the minimum*/
                {
                    ElbowCurrent = ELBOW_MIN;                                   /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    ElbowCurrent = (ElbowCurrent + ELBOW_INC);                  /*Increment value of elbow value by set increment*/
                }
                break;
            case 0xFFFFFF88:                                                    /*Accept Move Key (A Key)*/
                MoveCount++;
                PMWIndexStore[MoveCount] = PWM3_0_BASE;
                PMWValueStore[MoveCount] = ElbowCurrent;
                MoveComplete = 1;
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                ElbowCurrent = ElbowPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
    }
    ShoulderPrevious = ShoulderCurrent;
    return;
};

void SEQ_CTRL__ GripperMove( void )
{
    MoveComplete = 0;
    LCD__Write("Gripper Move\nPress 9 or 3");
    usleep(10000);
    LCD__Write("A-To Accept Move\nB-To Reject Move")
    usleep(4000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case 0xFFFFFF90:                                                    /*Open Key (9 Key)*/
                if (GripperCurrent <= GRIP_MAX)                                   /*Assess value of gripper value against the maximum*/
                {
                    GripperCurrent = GRIP_MAX;                                    /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    GripperCurrent = (GripperCurrent - GRIP_INC);                   /*Decrement value of gripper value by set increment*/
                }
                break;   
            case 0xFFFFFFB0:                                                    /*Close Key (3 Key)*/
                if (GripperCurrent >= GRIP_MIN)                                   /*Assess value of gripper value against the minimum*/
                {
                    GripperCurrent = GRIP_MIN;                                    /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    GripperCurrent = (GripperCurrent + GRIP_INC);                   /*Increment value of gripper value by set increment*/
                }
                break;
            case 0xFFFFFF88:                                                    /*Accept Move Key (A Key)*/
                MoveCount++;
                PMWIndexStore[MoveCount] = PWM4_0_BASE;
                PMWValueStore[MoveCount] = GripperCurrent;
                MoveComplete = 1;
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                GripperCurrent = GripperPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
    }
    GripperPrevious = GripperCurrent;
    return;
};