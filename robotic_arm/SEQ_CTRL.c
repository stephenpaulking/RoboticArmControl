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
 * Status   : WRITTEN                                                    *
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
 
 /*-------------------------------------------------------------------------*
  * Object Header Files :-                                                  *
  *-------------------------------------------------------------------------*/

#include "SEQ_CTRL.h"
#include "RAP.h"
#include "KEYP.h"
#include "LCD.h"
#include "PWM.h"
#include "SEV_SEG.h"
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void SEQ_CTRL__Schedule( void )
{
    ModeContinue = 1;
      
    LCD__Write("Sequence Mode\nMain Menu");
    SEV_SEG__Write("RCST");
    usleep(5000000);
    LCD__Write("CLR to Start New\nRE to Recall");
    SEV_SEG__Clear();
    while(ModeContinue == 1)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_D:                                             /*Recall Key (D Key)*/
                SEQ_CTRL__Recall();
                usleep(2000);
                break;  
            case KEY_C:                                             /*New Sequence Key (C Key)*/
                SEQ_CTRL__Clear();
                SEQ_CTRL__SetSequence();
                usleep(2000);
                LCD__Write("C to Start New\nD to Recall Last");
                usleep(2000);
                break; 
            case KEY_0:                                             /*Exit Key (0 Key)*/
                usleep(2000);
                ModeContinue = 0;
                break;  
            default:
                //Do nothing
                usleep(2000);
                break;
        }
    }
    return;
};

void SEQ_CTRL__SetSequence( void )
{
    StoreContinue = 1;
    
    MoveCount = 0;
    
    LCD__Write("Sequence Mode\nResetting Arm");
    usleep(2000);
    
    PWM__Reset();
    
    LCD__Write("Sequence Mode\nStarted");
    
    usleep(400000);
    
    LCD__Write("Make A Move\nPress Bk to Exit");
    usleep(2000);
    
    while(StoreContinue == 1)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_4:                                             /* Left Key */
            case KEY_6:                                             /* Right Key */
                SEQ_CTRL__BaseMove();
                usleep(2000);
                break;  
            case KEY_2:                                             /* Shoulder Up Key */
            case KEY_8:                                             /* Shoulder Down Key */
                SEQ_CTRL__ShoulderMove();
                usleep(2000);
                break; 
            case KEY_1:                                             /* Elbow Up Key */
            case KEY_7:                                             /* Elbow Down Key */
                SEQ_CTRL__ElbowMove();
                usleep(2000);
                break;  
            case KEY_3:                                             /* Grip Close Key */
            case KEY_9:                                             /* Grip Open Key */
                SEQ_CTRL__GripMove();
                usleep(2000);
                break; 
            case KEY_5:                                             /* Exit Key */
                StoreContinue = 0;
                usleep(2000);
                break; 
            default:
                //Do nothing
                usleep(2000);
                break;
        }
    }
    return;
};

void SEQ_CTRL__Clear(void)
{
    LCD__Write("Sequence Clear\nIn Progress");
    
    PWM__Reset();
    
    BaseCurrent         =   DEFAULT_PWM_VAL;                //PWM1 - LEFT/RIGHT
    ShoulderCurrent     =   DEFAULT_PWM_VAL;                //PWM2 - TOP ARM
    ElbowCurrent        =   DEFAULT_PWM_VAL;                //PWM3 - BOTTOM ARM
    GripCurrent         =   DEFAULT_PWM_VAL;                //PWM4 - GRIPPER
    BasePrevious        =   DEFAULT_PWM_VAL;                //PWM1 - LEFT/RIGHT
    ShoulderPrevious    =   DEFAULT_PWM_VAL;                //PWM2 - TOP ARM
    ElbowPrevious       =   DEFAULT_PWM_VAL;                //PWM3 - BOTTOM ARM
    GripPrevious        =   DEFAULT_PWM_VAL;                //PWM4 - GRIPPER
    
    usleep(2000);
    
    int Counter;
    
    for(Counter = 0; Counter < ARRAY_SIZE; Counter++)
    {    
        usleep(2000);
        PMWIndexStore[Counter] = 0;
        usleep(2000);
        PMWValueStore[Counter] = DEFAULT_PWM_VAL;
        usleep(2000);
    }
    
    return;
}

void SEQ_CTRL__Recall(void)
{
    LCD__Write("Sequence Recall\nIn Progress");
    
    PWM__Reset();
    
    usleep(300000);
    
    int Counter;
    
    for(Counter = 0; Counter <= MoveCount; Counter++)
    {    
        usleep(400000);
        PWM__Send(PMWIndexStore[Counter],PMWValueStore[Counter]);
        usleep(2000);
    }
    return;
}

void SEQ_CTRL__BaseMove(void)
{
    MoveComplete = 0;
    
    LCD__Write("Base Move\nPress L or R");
    usleep(300000);
    LCD__Write("A - Accept Move\nRJ - Reject Move");
    usleep(2000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_4:                                                    /* Left Key */
                BaseCurrent = PWM__Decrement(BASE_PWM,BaseCurrent);
                break;
            case KEY_6:                                                    /* Right Key */
                BaseCurrent = PWM__Increment(BASE_PWM,BaseCurrent);
                break;
            case KEY_A:                                                    /*Accept Move Key */
                PMWIndexStore[MoveCount] = BASE_PWM;
                PMWValueStore[MoveCount] = BaseCurrent;
                BasePrevious = BaseCurrent;
                MoveCount++;
                MoveComplete = 1;
                LCD__Write("Make Next Move\nor 0 to Finish");
                break;
            case KEY_B:                                                    /*Reject Move Key */
                BaseCurrent = BasePrevious;
                PWM__Send(BASE_PWM,BasePrevious);
                usleep(2000);
                break;
            case KEY_0:                                                   /* Exit Key */
                MoveComplete = 1;
                break;
            default:
                usleep(2000);
                //Do Nothing
        }
    }
    return;
};

void SEQ_CTRL__ShoulderMove(void)
{
    MoveComplete = 0;
    
    LCD__Write("Shoulder Move\nPress Us or Ds");
    usleep(300000);
    LCD__Write("A - Accept Move\nRJ - Reject Move");
    usleep(2000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_2:                                                    /* Shoulder Up Key */
                ShoulderCurrent = PWM__Increment(SHOULDER_PWM,ShoulderCurrent);
                break;
            case KEY_8:                                                    /* Shoulder Down Key */
                ShoulderCurrent = PWM__Decrement(SHOULDER_PWM,ShoulderCurrent);
                break;
            case KEY_A:                                                    /*Accept Move Key */
                PMWIndexStore[MoveCount] = SHOULDER_PWM;
                PMWValueStore[MoveCount] = ShoulderCurrent;
                ShoulderPrevious = ShoulderCurrent;
                MoveCount++;
                MoveComplete = 1;
                LCD__Write("Make Next Move\nor 0 to Finish");
                break;
            case KEY_B:                                                    /*Reject Move Key */
                ShoulderCurrent = ShoulderPrevious;
                PWM__Send(SHOULDER_PWM,ShoulderPrevious);
                usleep(2000);
                break;
            case KEY_0:                                                   /* Exit Key */
                MoveComplete = 1;
                break;
            default:
                usleep(2000);
                //Do Nothing
        }
    }
    return;
};

void SEQ_CTRL__ElbowMove(void)
{
    MoveComplete = 0;
    
    LCD__Write("Elbow Move\nPress Ue or De");
    usleep(300000);
    LCD__Write("A - Accept Move\nRJ - Reject Move");
    usleep(2000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_1:                                                     /* Elbow Up Key */
                ElbowCurrent = PWM__Increment(ELBOW_PWM,ElbowCurrent);
                break;
            case KEY_7:                                                     /* Elbow Down Key */
                ElbowCurrent = PWM__Decrement(ELBOW_PWM,ElbowCurrent);
                break;
            case KEY_A:                                                     /*Accept Move Key */
                PMWIndexStore[MoveCount] = ELBOW_PWM;
                PMWValueStore[MoveCount] = ElbowCurrent;
                ElbowPrevious = ElbowCurrent;
                MoveCount++;
                MoveComplete = 1;
                LCD__Write("Make Next Move\nor 0 to Finish");
                break;
            case KEY_B:                                                     /*Reject Move Key */
                ElbowCurrent = ElbowPrevious;
                PWM__Send(ELBOW_PWM,ElbowPrevious);
                usleep(2000);
                break;
            case KEY_0:                                                     /* Exit Key */
                MoveComplete = 1;
                break;
            default:
                usleep(2000);
                //Do Nothing
        }
    }
    return;
};

void SEQ_CTRL__GripMove(void)
{
    MoveComplete = 0;
    
    LCD__Write("Grip Move\nPress Oj or Cj");
    usleep(300000);
    LCD__Write("A - Accept Move\nRJ - Reject Move");
    usleep(2000);
    while(MoveComplete == 0)
    {
        KeySelected = KEYP__GetState();
        
        switch (KeySelected)
        {
            case KEY_3:                                                     /* Grip Close Key */
                GripCurrent = PWM__Increment(GRIP_PWM,GripCurrent);
                break;
            case KEY_9:                                                     /* Grip Open Key */
                GripCurrent = PWM__Decrement(GRIP_PWM,GripCurrent);
                break;
            case KEY_A:                                                     /*Accept Move Key */
                PMWIndexStore[MoveCount] = GRIP_PWM;
                PMWValueStore[MoveCount] = GripCurrent;
                GripPrevious = GripCurrent;
                MoveCount++;
                MoveComplete = 1;
                LCD__Write("Make Next Move\nor 0 to Finish");
                break;
            case KEY_B:                                                     /*Reject Move Key */
                GripCurrent = GripPrevious;
                PWM__Send(GRIP_PWM,GripPrevious);
                usleep(2000);
                break;
            case KEY_0:                                                     /* Exit Key */
                MoveComplete = 1;
                break;
            default:
                usleep(2000);
                //Do Nothing
        }
    }
    return;
}
