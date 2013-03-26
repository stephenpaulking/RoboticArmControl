/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : FREECTRL.c                                                    *
 *                                                                          *
 * Purpose  : Free Control Mode C file for robotic arm project to enable    *
 *            manual control of all functions of the robotic arm            *
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

#include "FREECTRL.h"
#include "RAP.h"
#include "KEYP.h"
#include "LCD.h"
#include "PWM.h"

/*#include "FATAL_ERR.h"*/                      /*Not currently implemented*/
 
/*---------------------------------------------------------------------------------------------------------------------------------------*
 * Operation Code :-                                                                                                                     *
 *---------------------------------------------------------------------------------------------------------------------------------------*/
  
void FREECTRL__Schedule( void )
{
    usleep(10000);
    ModeContinue = 0;                                                           /*Set internal exit flag*/
    HorizontalValue =   0x1250;                                                 /*PWM1 - LEFT/RIGHT - Initialise Values*/
    ShoulderValue   =   0x1250;                                                 /*PWM2 - TOP ARM - Initialise Values*/
    ElbowValue      =   0x1250;                                                 /*PWM3 - BOTTOM ARM - Initialise Values*/
    GripperValue    =   0x1250;                                                 /*PWM4 - GRIPPER - Initialise Values*/
      
    LCD__Write("Free Roam");                                                    /*Write string to the LCD*/
    
    while(ModeContinue == 0)                                                    /*While internal exit flag is not set*/
    {
        KeySelected = KEYP__GetState();                                         /*Get the state of the keypad and return key press if any*/
        
        switch (KeySelected)                                                    /*Initialise a case when a certain key is pressed*/
        {
            case 0xFFFFFF99:                                                    /*Left Key (4 Key)*/
                if (HorizontalValue <= HORIZONTAL_MIN)                          /*Assess value of horizontal value against the minimum*/
                {
                    LCD__Write("Reached Min Value\nFor Horizontal Move");       /*Write warning to LCD*/
                    HorizontalValue = HORIZONTAL_MIN;                           /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    HorizontalValue = (HorizontalValue - HORIZONTAL_INC);       /*Decrement value of horizontal value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Right");                  /*Display movement message on LCD*/
                }
                break;   
            case 0xFFFFFF82:                                                    /*Right Key (6 Key)*/
                if (HorizontalValue >= HORIZONTAL_MAX)                          /*Assess value of horizontal value against the maximum*/
                {
                    LCD__Write("Reached Max Value\nFor Horizontal Move");       /*Write warning to LCD*/
                    HorizontalValue = HORIZONTAL_MAX;                           /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    HorizontalValue = (HorizontalValue + HORIZONTAL_INC);       /*Increment value of horizontal value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Left");                   /*Display movement message on LCD*/
                }
                break;
            case 0xFFFFFF80:                                                    /*Shoulder Up Key (8 Key)*/
                if (ShoulderValue <= SHOULDER_MAX)                              /*Assess value of horizontal value against the maximum*/
                {
                    LCD__Write("Reached Max Value\nFor Shoulder Move");         /*Write warning to LCD*/
                    ShoulderValue = SHOULDER_MAX;                               /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    ShoulderValue = (ShoulderValue - SHOULDER_INC);             /*Decrement value of shoulder value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Up");                     /*Display movement message on LCD*/
                }
                break;   
            case 0xFFFFFFA4:                                                    /*Shoulder Down Key (2 Key)*/
                if (ShoulderValue >= SHOULDER_MIN)                              /*Assess value of shoulder value against the minimum*/
                {
                    LCD__Write("Reached Min Value\nFor Shoulder Move");         /*Write warning to LCD*/
                    ShoulderValue = SHOULDER_MIN;                               /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    ShoulderValue = (ShoulderValue + SHOULDER_INC);             /*Increment value of shoulder value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Down");                   /*Display movement message on LCD*/
                }
                break; 
            case 0xFFFFFFF8:                                                    /*Elbow Up Key (7 Key)*/
                if (ElbowValue <= ELBOW_MAX)                                    /*Assess value of elbow value against the maximum*/
                {
                    LCD__Write("Reached Max Value\nFor Elbow Move");            /*Write warning to LCD*/
                    ElbowValue = ELBOW_MAX;                                     /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    ElbowValue = (ElbowValue - ELBOW_INC);                      /*Decrement value of elbow value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Up");                     /*Display movement message on LCD*/
                }
                break;   
            case 0xFFFFFFCF:                                                    /*Elbow Down Key (1 Key)*/
                if (ElbowValue >= ELBOW_MIN)                                    /*Assess value of elbow value against the minimum*/
                {
                    LCD__Write("Reached Min Value\nFor Elbow Move");            /*Write warning to LCD*/
                    ElbowValue = ELBOW_MIN;                                     /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    ElbowValue = (ElbowValue + ELBOW_INC);                      /*Increment value of elbow value by set increment*/
                    LCD__Write("We Are Moving!\nGoing Down");                   /*Display movement message on LCD*/
                }
                break;
            case 0xFFFFFF90:                                                    /*Open Key (9 Key)*/
                if (GripperValue <= GRIP_MAX)                                   /*Assess value of gripper value against the maximum*/
                {
                    LCD__Write("Reached Max Value\nFor Gripper");               /*Write warning to LCD*/
                    GripperValue = GRIP_MAX;                                    /*Make value equal to maximum to ensure no move is made*/
                }
                else
                {
                    GripperValue = (GripperValue - GRIP_INC);                   /*Decrement value of gripper value by set increment*/
                    LCD__Write("We Are Moving!\nOpening Grip");                 /*Display movement message on LCD*/
                }
                break;   
            case 0xFFFFFFB0:                                                    /*Close Key (3 Key)*/
                if (GripperValue >= GRIP_MIN)                                   /*Assess value of gripper value against the minimum*/
                {
                    LCD__Write("Reached Min Value\nFor Gripper");               /*Write warning to LCD*/
                    GripperValue = GRIP_MIN;                                    /*Make value equal to minimum to ensure no move is made*/
                }
                else
                {
                    GripperValue = (GripperValue + GRIP_INC);                   /*Increment value of gripper value by set increment*/
                    LCD__Write("We Are Moving!\nClosing Grip");                 /*Display movement message on LCD*/
                }
                break;
            case 0xFFFFFFC0:                                                    /*Exit Key (0 Key)*/
                ModeContinue = 1;                                               /*Set mode exit flag*/
                break;   
            default:
                usleep(2000);                                                   /*Do nothing*/
        };
        
        usleep(14000);
        PWM__Send(PWM1_0_BASE,HorizontalValue);                                 /*Write horizontal value to the horizontal PWM*/
        PWM__Send(PWM2_0_BASE,ShoulderValue);                                   /*Write shoulder value to the shoulder PWM*/
        PWM__Send(PWM3_0_BASE,ElbowValue);                                      /*Write elbow value to the elbow PWM*/
        PWM__Send(PWM4_0_BASE,GripperValue);                                    /*Write gripper value to the gripper PWM*/
        
    };
    
return;

};
