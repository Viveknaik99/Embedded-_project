#include"header.h"

#define lcd P2 //lcd data pin is connected to port 2 pin

sbit RS = P3^0; // RS pin connected to P3.0
sbit EN = P3^1; // EN pin connected to P3.1
sbit Led = P1^2;  // P1^2 is connected to an LED


void initlcd() 
{
    Led = 1;  // Turn on an LED at the beginning of the initialization
    cmd_lcd(0x38);
    delay_ms(5);

    cmd_lcd(0x0C);
    delay_ms(5);

    cmd_lcd(0x01);
    delay_ms(5);

    cmd_lcd(0x06);
    delay_ms(5);
    
    Led = 0;  // Turn off the LED at the end of the initialization
}

void cmd_lcd(unsigned char command)
{
    EN = 1;
    RS = 0;
    lcd = command;
    delay_ms(1);
    EN = 0;
    //delay_ms(10);
}

void data_lcd(unsigned char databyte)
{
    EN = 1;
    RS = 1;
    lcd = databyte;
    delay_ms(1);
    EN = 0;
}

void Print_String(unsigned char *message)
{
    while(*message!='\0')
	{
   		data_lcd( *message);
	  	message++;
	}   
}



void delay_ms(unsigned int ms)
{
   unsigned char t1;
   unsigned int t2;

   for(t1=0; t1<ms; t1++)
   {
      for(t2=0; t2<114; t2++);
   }
}

// Function to print an integer on LCD
//void Print_Integer(unsigned int num) 
//{
//
//    if (num < 10) {
//        data_lcd(num + '0');
//    } else {
//        Print_Integer(num / 10);
//        data_lcd((num % 10) + '0');
//    }
//}