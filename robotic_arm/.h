#ifndef LCD_H_
#define LCD_H_

#define LCD_DISPLAY_CLEAR           0x0001
#define LCD_RETURN_HOME             0x0002
#define LCD_NEWLINE                 0x00D0

#define LCD_DISPLAY_OFF             0x0008
#define LCD_ENTRY_MODE              0x0006       /* Increment cursor, no shift */

#define LCD_INSTRUCTION_1           0x0038       /* Display uses 8-bit data */
#define LCD_INSTRUCTION_2           0x000F       /* Display on */
#define LCD_INSTRUCTION_3           0x0007       /* Read up */

#define LCD_CONFIG_INSTRUCTION      0x0038       /* 8-bits, 2 lines, 5x7 font */

#define LCD_WAIT_INIT               40000
#define LCD_WAIT_1                  200
#define LCD_WAIT_2                  200
#define LCD_WAIT_3                  2000

#define LCD_DELAY                   200
#define LCD_SMALL_DELAY             100

#define LCD_E_HIGH                  0x0400
#define LCD_E_LOW                   0xFBFF

void InitialiseLCD(void);

void WriteToLCD(const char * str);

#endif /*LCD_H_*/
