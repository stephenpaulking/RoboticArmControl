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
    MoveCount = 0;
    HorizontalCurrent =     PWM_DEF;                  //PWM1 - LEFT/RIGHT
    ShoulderCurrent   =     PWM_DEF;                  //PWM2 - TOP ARM
    ElbowCurrent      =     PWM_DEF;                  //PWM3 - BOTTOM ARM
    GripperCurrent    =     PWM_DEF;                  //PWM4 - GRIPPER
    HorizontalPrevious =    PWM_DEF;                 //PWM1 - LEFT/RIGHT
    ShoulderPrevious   =    PWM_DEF;                 //PWM2 - TOP ARM
    ElbowPrevious      =    PWM_DEF;                 //PWM3 - BOTTOM ARM
    GripperPrevious    =    PWM_DEF;                 //PWM4 - GRIPPER
    PWM__Reset();
      
    LCD__Write("Store Sequence");
    usleep(50000);
    while(ModeContinue == 0)
    {
        usleep(6000);
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case 0xFFFFFF99:        /*Left Key (4 Key)*/
            case 0xFFFFFF82:        /*Right Key (6 Key)*/
                SEQ_CTRL__HorizontalMove();
                usleep(9000);
                break;
            case 0xFFFFFF80:        /*Shoulder Up Key (8 Key)*/
            case 0xFFFFFFA4:        /*Shoulder Down Key (2 Key)*/
                SEQ_CTRL__ShoulderMove();
                usleep(9000);
                break;
            case 0xFFFFFFF8:        /*Elbow Up Key (7 Key)*/
            case 0xFFFFFFCF:        /*Elbow Down Key (1 Key)*/
                SEQ_CTRL__ElbowMove();
                usleep(9000);
                break;
            case 0xFFFFFF90:        /*Open Key (9 Key)*/
            case 0xFFFFFFB0:        /*Close Key (3 Key)*/
                SEQ_CTRL__GripperMove();
                usleep(9000);
                break;
            case 0xFFFFFFA1:        /*Recall Sequence Key (D Key)*/
                SEQ_CTRL__RecallSequence();
                LCD__Write("Sequence Recall\nComplete");
                break;  
            case 0xFFFFFFF0:        /*Clear Sequence Key (C Key)*/
                SEQ_CTRL__ClearSequence();
                LCD__Write("Sequence Clear\nComplete");
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

void SEQ_CTRL__HorizontalMove(void)
{
    MoveComplete = 0;
    LCD__Write("Horizontal Move\nPress 4 or 6");
    usleep(1000000);
    LCD__Write("A-To Accept Move\nB-To Reject Move");
    usleep(4000);
    while(MoveComplete == 0)
    {
        usleep(6000);
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
                LCD__Write("Make Next Move\nD-Recall Seqnc");
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (A Key)*/
                HorizontalCurrent = HorizontalPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
        
        PWM__Send(PWM1_0_BASE,HorizontalCurrent);
    }
    HorizontalPrevious = HorizontalCurrent;
    return;
};

void SEQ_CTRL__ShoulderMove(void)
{
    MoveComplete = 0;
    LCD__Write("Shoulder Move\nPress 8 or 2");
    usleep(1000000);
    LCD__Write("A-To Accept Move\nB-To Reject Move");
    usleep(4000);
    while(MoveComplete == 0)
    {
        usleep(6000);
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
                LCD__Write("Make Next Move\nD-Recall Seqnc");
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                ShoulderCurrent = ShoulderPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
        PWM__Send(PWM2_0_BASE,ShoulderCurrent);
    }
    ShoulderPrevious = ShoulderCurrent;
    return;
};

void SEQ_CTRL__ElbowMove(void)
{
    MoveComplete = 0;
    LCD__Write("Elbow Move\nPress 7 or 1");
    usleep(1000000);
    LCD__Write("A-To Accept Move\nB-To Reject Move");
    usleep(4000);
    while(MoveComplete == 0)
    {
        usleep(6000);
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
                LCD__Write("Make Next Move\nD-Recall Seqnc");
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                ElbowCurrent = ElbowPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
        PWM__Send(PWM3_0_BASE,ElbowCurrent);
    }
    ElbowPrevious = ElbowCurrent;
    return;
};

void SEQ_CTRL__GripperMove(void)
{
    MoveComplete = 0;
    LCD__Write("Gripper Move\nPress 9 or 3");
    usleep(1000000);
    LCD__Write("A-To Accept Move\nB-To Reject Move");
    usleep(4000);
    while(MoveComplete == 0)
    {
        usleep(6000);
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
                LCD__Write("Make Next Move\nD-Recall Seqnc");
                break;
            case 0xFFFFFF83:                                                    /*Reject Move Key (B Key)*/
                GripperCurrent = GripperPrevious;
                usleep(4000);
                break;
            default:
                usleep(1000);
        }
        PWM__Send(PWM4_0_BASE,GripperCurrent);
    }
    GripperPrevious = GripperCurrent;
    return;
}

void SEQ_CTRL__RecallSequence(void)
{
    PWM__Reset();
    usleep(10000);
    int x;
    for(x = 0; x<MoveCount; x++)
    {    
        usleep(500000);
        PWM__Send(PMWIndexStore[x],PMWValueStore[x]);
        usleep(500000);
    }
    return;
}

void SEQ_CTRL__ClearSequence(void)
{
    PWM__Reset();
    usleep(10000);
    int x;
    for(x = 0; x<MoveCount; x++)
    {    
        usleep(50000);
        PMWIndexStore[x] = 0;
        PMWValueStore[x] = 0;
        HorizontalCurrent =     PWM_DEF;
        ShoulderCurrent   =     PWM_DEF;
        ElbowCurrent      =     PWM_DEF;
        GripperCurrent    =     PWM_DEF;
        HorizontalPrevious =    PWM_DEF;
        ShoulderPrevious   =    PWM_DEF;
        ElbowPrevious      =    PWM_DEF;
        GripperPrevious    =    PWM_DEF;
        usleep(50000);
    }
    return;
}
