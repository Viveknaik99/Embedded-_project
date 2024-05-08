#include <reg51.h>
#include <intrins.h>
#include <stdio.h>



// Function prototypes (replace these with your LCD functions)
void initlcd(void);
void cmd_lcd(unsigned char command);
void data_lcd(unsigned char databyte);
void Print_String(unsigned char *message);
void delay_ms(unsigned int);
void data_lcd(unsigned char);
void Print_String(char *);
void Print_Integer(unsigned int);
void delay(unsigned int);

void Init_Timer0();
unsigned int Measure_Distance();
