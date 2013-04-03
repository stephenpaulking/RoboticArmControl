/*==========================================================================*
 * C OBJECT                                                                 *
 *--------------------------------------------------------------------------*
 *                                                                          *
 * Object   : PWM.c                                                         *
 *                                                                          *
 * Purpose  : PWM C file for robotic arm project                            *
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
 
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
 
/*--------------------------------------------------------------------------*
 * Object Header Files :-                                                   *
 *--------------------------------------------------------------------------*/
  
#include "PWM.h"
#include "RAP.h"
#include "SEV_SEG.h"

/*--------------------------------------------------------------------------*
 * Private Data Items :-                                                    *
 *--------------------------------------------------------------------------*/
 
/* Variable to store output value of increment/decrement */
unsigned int OutputValue;

/* Variables to store index settings */
unsigned int SetMaximum;
unsigned int SetMinimum;
unsigned int SetIncrement;
 
/*--------------------------------------------------------------------------*
 * Operation Code :-                                                        *
 *--------------------------------------------------------------------------*/
  
void PWM__Send ( const int PWMIndex, const int PWMValue )
{
    IOWR_ALTERA_AVALON_PIO_DATA(PWMIndex,PWMValue);         /* Write to PWM */
    return;
};

void PWM__Reset ( void )
{
    SEV_SEG__Write("RSET");
    IOWR_ALTERA_AVALON_PIO_DATA(BASE_PWM,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(SHOULDER_PWM,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(ELBOW_PWM,DEFAULT_PWM_VAL);
    IOWR_ALTERA_AVALON_PIO_DATA(GRIP_PWM,DEFAULT_PWM_VAL);
    usleep(5000000);                                            /* Delay for 5 seconds */
    SEV_SEG__Clear();
    return;
};

int PWM__Increment ( const int PWMIndex, const int InputValue )
{
    
    OutputValue = DEFAULT_PWM_VAL;
    
    switch (PWMIndex)
    {
        case BASE_PWM:
            SetMaximum = BASE_MAX;
            SetIncrement = BASE_INC;
            break;
        case SHOULDER_PWM:
            SetMaximum = SHOULDER_MAX;
            SetIncrement = SHOULDER_INC;
            break;
        case ELBOW_PWM:
            SetMaximum = ELBOW_MAX;
            SetIncrement = ELBOW_INC;
            break;
        case GRIP_PWM:
            SetMaximum = GRIP_MAX;
            SetIncrement = GRIP_INC;
            break;
        default:
            /* Do Nothing */
            break;
    }
    
    if (InputValue >= SetMaximum)
    {
        SEV_SEG__Write("STOP");
        SEV_SEG__Clear();
        OutputValue = InputValue;
    }
    else
    {
        OutputValue = (InputValue + SetIncrement);
        usleep(2000);
        PWM__Send(PWMIndex,OutputValue);
    }
    
    return OutputValue;
}

int PWM__Decrement ( const int PWMIndex, const int InputValue )
{
    
    OutputValue = DEFAULT_PWM_VAL;
    
    switch (PWMIndex)
    {
        case BASE_PWM:
            SetMinimum = BASE_MIN;
            SetIncrement = BASE_INC;
            break;
        case SHOULDER_PWM:
            SetMinimum = SHOULDER_MIN;
            SetIncrement = SHOULDER_INC;
            break;
        case ELBOW_PWM:
            SetMinimum = ELBOW_MIN;
            SetIncrement = ELBOW_INC;
            break;
        case GRIP_PWM:
            SetMinimum = GRIP_MIN;
            SetIncrement = GRIP_INC;
            break;
        default:
            /* Do Nothing */
            break;
    }
    
    if (InputValue <= SetMinimum)
    {
        SEV_SEG__Write("STOP");
        SEV_SEG__Clear();
        OutputValue = InputValue;
    }
    else
    {
        OutputValue = (InputValue - SetIncrement);
        usleep(2000);
        PWM__Send(PWMIndex,InputValue);
    }
    
    return OutputValue;
}