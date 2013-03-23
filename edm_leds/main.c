#include <stdbool.h>
#include <unistd.h>
#include <stdio.h> 
#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include "altera_avalon_lcd_16207_regs.h"
#include "altera_avalon_lcd_16207.h"
#include "lcd.h"

void InitialiseLCD();
void WriteToLCD(const char * str);

int key;
int HorizontalValue;
int ShoulderValue;
int ElbowValue;
int GripperValue;

static int HORIZONTAL_INC = 0x0015;
static int HORIZONTAL_MAX = 0x1800;
static int HORIZONTAL_MIN = 0xd2b;
static int SHOULDER_INC = 0x0015;
static int SHOULDER_MAX = 0xc31;
static int SHOULDER_MIN = 0x1700;
static int ELBOW_INC = 0x0015;
static int ELBOW_MAX = 0xc31;
static int ELBOW_MIN = 0x189c;
static int GRIP_INC = 0x0015;
static int GRIP_MAX = 0xc31;
static int GRIP_MIN = 0x1990;

int main(void)
{
    usleep(15000);
    InitialiseLCD();
    WriteToLCD("Robot Arm\nProject");

    HorizontalValue = 0x1250; //PWM1 - LEFT/RIGHT
    ShoulderValue = 0x1250; //PWM2 - TOP ARM
    ElbowValue = 0x1250; //PWM3 - BOTTOM ARM
    GripperValue = 0x1250; //PWM4 - GRIPPER
    
    /*IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,0xd2b); //- Max Right
    IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,0xc31); //- Max Up
    IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,0xc31); //- Max Up
    IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,0xc31); //- Max Open
    usleep(1000000);
    IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,0x1800); //- Min Right
    IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,0x1700); //- Min Up
    IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,0x189c); //- Min Up
    IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,0x189c); //- Min Open
    usleep(1000000);*/
    //IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,0x1250); //- Mid Right
    //IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,0x1250); //- Mid Up
    //IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,0x1250); //- Mid Up
    //IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,0x1250); //- Mid Open
    
    WriteToLCD("Ready for Input\nPress a key");
    
    while(1)
    {
        key = IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_0_BASE); //read keypad
        
        switch (key)
        {
            case 0xFFFFFF86:        //Left Key
                usleep(2000);
                if (HorizontalValue <= HORIZONTAL_MIN)
                {
                    WriteToLCD("Reached Min Value\nFor Horizontal Move");
                    HorizontalValue = HORIZONTAL_MIN;
                }
                else
                {
                    HorizontalValue = (HorizontalValue - HORIZONTAL_INC);
                    WriteToLCD("We Are Moving!\nGoing Left");
                }
                usleep(10000);
                break;   
            case 0xFFFFFF8E:        //Right Key
                usleep(4100);
                if (HorizontalValue >= HORIZONTAL_MAX)
                {
                    WriteToLCD("Reached Max Value\nFor Horizontal Move");
                    HorizontalValue = HORIZONTAL_MAX;
                }
                else
                {
                    HorizontalValue = (HorizontalValue + HORIZONTAL_INC);
                    WriteToLCD("We Are Moving!\nGoing Right");
                }
                usleep(10000);
                break;
            case 0xFFFFFF80:        //8 Key
                usleep(2000);
                if (ShoulderValue <= SHOULDER_MAX)
                {
                    WriteToLCD("Reached Max Value\nFor Shoulder Move");
                    ShoulderValue = SHOULDER_MAX;
                }
                else
                {
                    ShoulderValue = (ShoulderValue - SHOULDER_INC);
                    WriteToLCD("We Are Moving!\nGoing Up");
                }
                usleep(10000);
                break;   
            case 0xFFFFFFA4:        //2 Key
                usleep(4100);
                if (ShoulderValue >= SHOULDER_MIN)
                {
                    WriteToLCD("Reached Min Value\nFor Shoulder Move");
                    ShoulderValue = SHOULDER_MIN;
                }
                else
                {
                    ShoulderValue = (ShoulderValue + SHOULDER_INC);
                    WriteToLCD("We Are Moving!\nGoing Down");
                }
                usleep(10000);
                break; 
            case 0xFFFFFF90:        //9 Key
                usleep(2000);
                if (ElbowValue <= ELBOW_MAX)
                {
                    WriteToLCD("Reached Max Value\nFor Elbow Move");
                    ElbowValue = ELBOW_MAX;
                }
                else
                {
                    ElbowValue = (ElbowValue - ELBOW_INC);
                    WriteToLCD("We Are Moving!\nGoing Up");
                }
                usleep(10000);
                break;   
            case 0xFFFFFFB0:        //3 Key
                usleep(4100);
                if (ElbowValue >= ELBOW_MIN)
                {
                    WriteToLCD("Reached Min Value\nFor Elbow Move");
                    ElbowValue = ELBOW_MIN;
                }
                else
                {
                    ElbowValue = (ElbowValue + ELBOW_INC);
                    WriteToLCD("We Are Moving!\nGoing Down");
                }
                usleep(10000);
                break;
            case 0xFFFFFFF8:        //7 Key
                usleep(2000);
                if (GripperValue <= GRIP_MAX)
                {
                    WriteToLCD("Reached Max Value\nFor Gripper");
                    GripperValue = GRIP_MAX;
                }
                else
                {
                    GripperValue = (GripperValue - GRIP_INC);
                    WriteToLCD("We Are Moving!\nOpening Grip");
                }
                usleep(10000);
                break;   
            case 0xFFFFFFCF:        //1 Key
                usleep(4100);
                if (GripperValue >= GRIP_MIN)
                {
                    WriteToLCD("Reached Min Value\nFor Gripper");
                    GripperValue = GRIP_MIN;
                }
                else
                {
                    GripperValue = (GripperValue + GRIP_INC);
                    WriteToLCD("We Are Moving!\nClosing Grip");
                }
                usleep(10000);
                break;  
            default:
                //Do nothing
                usleep(10000);
        };
        
        IOWR_ALTERA_AVALON_PIO_DATA(PWM1_0_BASE,HorizontalValue); //- Write to Base
        IOWR_ALTERA_AVALON_PIO_DATA(PWM2_0_BASE,ShoulderValue); //- Write to Shoulder
        IOWR_ALTERA_AVALON_PIO_DATA(PWM3_0_BASE,ElbowValue); //- Write to Elbow
        IOWR_ALTERA_AVALON_PIO_DATA(PWM4_0_BASE,GripperValue); //- Write to Gripper
        
        //IOWR_ALTERA_AVALON_PIO_DATA(SEG7_BASE, key);
    }
return(0);
}
