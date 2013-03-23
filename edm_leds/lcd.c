#include <stdbool.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_lcd_16207_regs.h"
#include "alt_types.h"
#include "globals.h"
#include "lcd.h"

static bool lcd_init1 = false;

void InitialiseLCD(void)
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits,  */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits, */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x30); /* 8-bits,  */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x38); /* 8-bits, 2 lines, 5x8 font */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x02); /* Set the Cursor to the home position */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x08); /* Turn Off LCD */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01); /* Display Clear */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x06); /* Set Entry Mode -- Cursor increment, display doesn't shift */
    usleep(41000);
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x0C); /* Display on */
    usleep(41000);
    
    lcd_init1 = true;     /*End of initialisation*/ 
    return;
}

void ClearLCD(void)
{
    IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0x01); /*Display Clear*/
    usleep(10000);
}

void WriteToLCD(const char * str)
{
    char * s_ptr = (char *) str;

    ClearLCD();
    if ((str != NULL) && (*str != '\0'))
    {
        while (*s_ptr != '\0')
        {
            if (*s_ptr == '\n')
            {
                IOWR_ALTERA_AVALON_LCD_16207_COMMAND(LCD_BASE, 0xC0);
            }
            else
            {
                IOWR_ALTERA_AVALON_LCD_16207_DATA(LCD_BASE, *s_ptr);
            }

            usleep(1000);
            s_ptr++;
        }
    }

    return;
}
